/**************************
* Motor Controller
* Sebastian Alpuy - Santiago Reyes
* Montevideo - Uruguay
* March 2014
**************************/

#include <Wire.h> // For I2C

#define VERSION "0.1"
#define DEVICE_ID 1

/*************************Arduino pins****************************/
#define SA0_PIN			4
#define MOTOR_STAND_BY  20
#define PWMA			10
#define AIN1			9
#define AIN2			6
#define POTE			19
#define TEMP			18
#define ENCODER			16
#define ENCODER_EN		21
/*****************************************************************/


/*************************Defines MMA8452*************************/
#define MMA8452_ADDRESS 0x1D  // 0x1D if SA0 high, 0x1C if low

//Define registers of MMA8452
#define OUT_X_MSB 0x01
#define XYZ_DATA_CFG  0x0E
#define WHO_AM_I   0x0D
#define CTRL_REG1  0x2A

#define GSCALE 2 // Set full scale range to +/-2, 4, or 8g.
/*****************************************************************/

/************************ States definitions *********************/
#define S_STAND_BY		0x00
#define S_MOTOR_ON		0x55
/*****************************************************************/

#define PARAM_ON_TIME 5
#define PARAM_STAND_BY_TIME 5

#define S_STAND_BY  0
#define S_MOTOR_ON  1

#define ACCEL_DATA    3

#define MAX_MOTOR_SPEED 65535
#define MIN_MOTOR_SPEED 0
#define MAX_ACCEL_VAL 1500
#define MAX_POT_VAL	65535
#define MIN_POT_VAL	0
#define MAX_TEMP_VAL	65535
#define MIN_TEMP_VAL	0

#define MOTOR_SPEED 128

/* Error codes */
#define ER_MAX_MOTOR_SPEED	0x0001
#define ER_MIN_MOTOR_SPEED	0x0002
#define ER_MAX_ACCEL		0x0004
#define ER_MAX_POT			0x0008
#define ER_MIN_POT			0x0010
#define ER_MAX_TEMP			0x0020
#define ER_MIN_TEMP			0x0040

unsigned int currentTime, lastEventTime;
unsigned char actualState;
int accelVal[ACCEL_DATA];
unsigned int motorSpeed;
unsigned int potVal;
unsigned int tempVal;
unsigned int errorCode;

void setup(){	
	// Pin SA0 high
	pinMode(SA0_PIN,OUTPUT);
	digitalWrite(SA0_PIN,HIGH);

    // Init Motor pins
	pinMode(ENCODER_EN, OUTPUT);
    pinMode(MOTOR_STAND_BY, OUTPUT);
	pinMode(PWMA, OUTPUT);
	pinMode(AIN1, OUTPUT);
	pinMode(AIN2, OUTPUT);
	motorStop();
	
	// Init serial port
	Serial.begin(57600);
	Serial.println("Controlador de Motor");	
	Serial.print("Version: ");	
	Serial.println(VERSION);	
	
	// Join I2C bus as master
	Wire.begin(); 
	
	// Init accel
	initMMA8452(); 
	
	currentTime = 0;
	lastEventTime = 0;
	actualState = S_MOTOR_ON;
	errorCode = 0;
	
	rampUp(MOTOR_SPEED,1);
}

void rampUp(int speed, int d){
	int sp = 16;
	int jp = 1;
	motorCounterClockwise(sp);
	delay(500);
	while ( sp <= speed ) {
		motorCounterClockwise(sp);
		delay(d);
		sp = sp + jp;
	}
}


void loop(){	

	SendSensorValues();
	SendErrors();
	
	switch ( actualState ){
		case S_STAND_BY:
			if (( currentTime - lastEventTime ) >= PARAM_STAND_BY_TIME ) {
				lastEventTime = currentTime;
				actualState = S_MOTOR_ON;
				rampUp(MOTOR_SPEED,1);
			}
		break;
		case S_MOTOR_ON:
			if (( currentTime - lastEventTime ) >= PARAM_ON_TIME ){
				lastEventTime = currentTime;
				actualState = S_STAND_BY;
				motorStop();
			} else {
				GetSensorsValues();
				ProcessValues();
			}
		break;
		default:
		break;                                                                                  
	}
	delay(1000);
	++currentTime;
}

void GetSensorsValues(void){
  motorSpeed = 60000 / getMotorSpeed1();
  readAccelData(accelVal);
  potVal = readPotentiometerValue();
  tempVal = readTemperatureValue();
}

void SendSensorValues(void){
  Serial.println("Id del dispositivo");
  Serial.println(DEVICE_ID);
  
  Serial.println("Velocidad del motor (rpm): ");
  Serial.println(motorSpeed);
  
  Serial.println("Aceleracion: ");
  Serial.println(accelVal[0]);
  Serial.println(accelVal[1]);
  Serial.println(accelVal[2]);
  
  Serial.println("Potenciometro: ");
  Serial.println(potVal);
  
  Serial.println("Temperatura: ");
  Serial.println(tempVal);
}

void SendErrors(void){
  Serial.println("Codigo de error: ");
  Serial.println(errorCode);
  Serial.println();
  Serial.println();
  errorCode = 0;
}

void ProcessValues(void){

	if ( motorSpeed > MAX_MOTOR_SPEED ){
		//Alarma velocidad maxima
		errorCode |= ER_MAX_MOTOR_SPEED;
	}
  
	if ( motorSpeed < MIN_MOTOR_SPEED ){
		//Alarma velocidad 
		errorCode |= ER_MIN_MOTOR_SPEED;
	}
  
	if ( accelVal[0] > MAX_ACCEL_VAL || accelVal[1] > MAX_ACCEL_VAL || accelVal[2] > MAX_ACCEL_VAL ||
		 accelVal[0] < -MAX_ACCEL_VAL || accelVal[1] < -MAX_ACCEL_VAL || accelVal[2] < -MAX_ACCEL_VAL ){
		//Alarma accel maxima
		errorCode |= ER_MAX_ACCEL;
	}
  
	if ( potVal > MAX_POT_VAL ){
		//Alarma pot maximo
		errorCode |= ER_MAX_POT;
	}
	
	if ( potVal < MIN_POT_VAL ){
		//Alarma pot minimo
		errorCode |= ER_MIN_POT;
	}	

	if ( tempVal > MAX_TEMP_VAL ){
		//Alarma temp max
		errorCode |= ER_MAX_TEMP;
	}
  
	if ( tempVal < MIN_TEMP_VAL ){
		//Alarma temp min
		errorCode |= ER_MIN_TEMP;
	} 
}

/********************Accelerometer*********************/
void readAccelData(int *destination)
{
  byte rawData[6];  // x/y/z accel register data stored here

  readRegisters(OUT_X_MSB, 6, rawData);  // Read the six raw data registers into data array

  // Loop to calculate 12-bit ADC and g value for each axis
  for(int i = 0; i < 3 ; i++)
  {
    int gCount = (rawData[i*2] << 8) | rawData[(i*2)+1];  //Combine the two 8 bit registers into one 12-bit number
    gCount >>= 4; //The registers are left align, here we right align the 12-bit integer

    // If the number is negative, we have to make it so manually (no 12-bit data type)
    if (rawData[i*2] > 0x7F)
    {  
      gCount = ~gCount + 1;
      gCount *= -1;  // Transform into negative 2's complement #
    }

    destination[i] = gCount; //Record this gCount into the 3 int array
  }
}

// Initialize the MMA8452 registers 
// See the many application notes for more info on setting all of these registers:
// http://www.freescale.com/webapp/sps/site/prod_summary.jsp?code=MMA8452Q
void initMMA8452()
{
  byte c = readRegister(WHO_AM_I);  // Read WHO_AM_I register
  if (c == 0x2A) // WHO_AM_I should always be 0x2A
  {  
    Serial.println("MMA8452Q is online...");
  }
  else
  {
    Serial.print("Could not connect to MMA8452Q: 0x");
    Serial.println(c, HEX);
	
    while(1) ; // Loop forever if communication doesn't happen
  }

  MMA8452Standby();  // Must be in standby to change registers

  // Set up the full scale range to 2, 4, or 8g.
  byte fsr = GSCALE;
  if(fsr > 8) fsr = 8; //Easy error check
  fsr >>= 2; // Neat trick, see page 22. 00 = 2G, 01 = 4A, 10 = 8G
  writeRegister(XYZ_DATA_CFG, fsr);

  //The default data rate is 800Hz and we don't modify it in this example code

  MMA8452Active();  // Set to active to start reading
}

// Sets the MMA8452 to standby mode. It must be in standby to change most register settings
void MMA8452Standby()
{
  byte c = readRegister(CTRL_REG1);
  writeRegister(CTRL_REG1, c & ~(0x01)); //Clear the active bit to go into standby
}

// Sets the MMA8452 to active mode. Needs to be in this mode to output data
void MMA8452Active()
{
  byte c = readRegister(CTRL_REG1);
  writeRegister(CTRL_REG1, c | 0x01); //Set the active bit to begin detection
}

// Read bytesToRead sequentially, starting at addressToRead into the dest byte array
void readRegisters(byte addressToRead, int bytesToRead, byte * dest)
{
  unsigned int read_timeout = 0;
  Wire.beginTransmission(MMA8452_ADDRESS);
  Wire.write(addressToRead);
  Wire.endTransmission(false); //endTransmission but keep the connection active

  Wire.requestFrom(MMA8452_ADDRESS, bytesToRead); //Ask for bytes, once done, bus is released by default

      read_timeout = millis() + 50;
//TODO: overflow	  
  while(Wire.available() < bytesToRead && millis() < read_timeout); //Hang out until we get the # of bytes we expect 

  for(int x = 0 ; x < bytesToRead ; x++)
    dest[x] = Wire.read();    
}

// Read a single byte from addressToRead and return it as a byte
byte readRegister(byte addressToRead)
{
  Wire.beginTransmission(MMA8452_ADDRESS);
  Wire.write(addressToRead);
  Wire.endTransmission(false); //endTransmission but keep the connection active

  Wire.requestFrom(MMA8452_ADDRESS, 1); //Ask for 1 byte, once done, bus is released by default

//TODO: overflow	  	
  while(!Wire.available()) ; //Wait for the data to come back
  return Wire.read(); //Return this one byte
}

// Writes a single byte (dataToWrite) into addressToWrite
void writeRegister(byte addressToWrite, byte dataToWrite)
{
  Wire.beginTransmission(MMA8452_ADDRESS);
  Wire.write(addressToWrite);
  Wire.write(dataToWrite);
  Wire.endTransmission(); //Stop transmitting
}

/********************Motor control*********************/
void motorClockwise(unsigned char speed){
	digitalWrite(MOTOR_STAND_BY, HIGH); //disable standby
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, speed);
}

void motorCounterClockwise(unsigned char speed){
	digitalWrite(MOTOR_STAND_BY, HIGH); //disable standby
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, speed);
}

void motorStop(void){
	motorCounterClockwise(16);
	delay(100);
	digitalWrite(MOTOR_STAND_BY, LOW); //enable standby
}

unsigned char readEncoderAux(){
	unsigned char i;
	unsigned char counter = 0;
	for( i = 0; i < 100; i++ ){
		counter += digitalRead(ENCODER);
	}
	if (counter > 80){
		return 1;
	} else if ( counter < 20 ) {
		return 0;
	} else {
		return 255;
	}
}

unsigned char readEncoder(){
	unsigned char encValue;
	do{
		encValue = readEncoderAux();
	}while(encValue == 255);
	return encValue;
}

unsigned int getMotorSpeed(){
	unsigned int t0;
	digitalWrite(ENCODER_EN,HIGH);
	delay(20);
	if( readEncoder() ){
		while(!readEncoder());
		t0 = millis();
		while(readEncoder());
		digitalWrite(ENCODER_EN,LOW);
		return (millis() - t0);
	} else {
		while(readEncoder());
		t0 = millis();
		while(!readEncoder());
		digitalWrite(ENCODER_EN,LOW);
		return (millis() - t0);
	}
}

unsigned int getMotorSpeed1(){
	unsigned int t0;
	digitalWrite(ENCODER_EN,HIGH);
	delay(20);
	if( readEncoder() ){
		while(readEncoder());
		// Empieza el 0
		t0 = millis();
		while(!readEncoder());
		while(readEncoder());
		// Empieza otro 0
		digitalWrite(ENCODER_EN,LOW);
		return (millis() - t0);
	} else {
		while(!readEncoder());
		while(readEncoder());
		// Empieza el 0
		t0 = millis();
		while(!readEncoder());
		while(readEncoder());
		// Empieza otro 0
		digitalWrite(ENCODER_EN,LOW);
		return (millis() - t0);
	}
}

/********************Potentiometer read*********************/
unsigned int readPotentiometerValue(void){
	return analogRead(POTE);
}

/********************Temperature read*********************/
unsigned int readTemperatureValue(void){
	return analogRead(TEMP);
}
