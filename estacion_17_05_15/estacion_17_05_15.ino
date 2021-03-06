/* 
 Weather Station using the Electric Imp
 By: Nathan Seidle
 SparkFun Electronics
 Date: October 4th, 2013
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 Much of this is based on Mike Grusin's USB Weather Board code.
 
 This code reads all the various sensors (wind speed, direction, rain gauge, humidty, pressure, light, batt_lvl)
 and sends it to the imp, which then forwards that data to an Imp Agent on the cloud that does some processing then
 bounces the weather data to Wunderground.
 
 The Imp Shield has Card Detect tied to pin A0. We use A0 for wind direction. You will need to cut the trace on the Imp shield.
 
 Current:
 130 for 2 seconds while transmitting
 ~30mA during sleep
 
 Todo:
 se resetea todas las noches a las 3 de la mañana
 borra todos los datos a la media noche
 Reset after 45 days to avoid millis roll over problems
 
 What was the wind direction and speed gust for the last 10 minutes?
 Is the 3.3V pin tied on the weather shield or elsewhere?
 */



#define dht_dpin 5
#include <avr/wdt.h> //We need watch dog for this program
//#include <SoftwareSerial.h> //Connection to Imp
#include <Wire.h> //I2C needed for sensors
#include "MPL3115A2.h" //Pressure sensor
#include "HTU21D.h" //Humidity sensor

//configurar wifi
#define SSID "******" // insert your SSID
#define PASS "*****" // insert your password
#define LOCATIONID "IREGINDE61/PASS" // location id
#define DST_IP "23.222.152.140" //api.wunderground.com


//SoftwareSerial imp(8, 9); // RX, TX into Imp pin 7

MPL3115A2 myPressure; //Create an instance of the pressure sensor
HTU21D myHumidity; //Create an instance of the humidity sensor


//Hardware pin definitions
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// digital I/O pins

const byte WSPEED = 3;
const byte RAIN = 2;
const byte STAT1 = 7;


// analog I/O pins
const byte WDIR = A0;
const byte LIGHT = A1;
const byte BATT = A2;
const byte REFERENCE_3V3 = A3;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Global Variables
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
long lastSecond; //The millis counter to see when a second rolls by
byte seconds; //When it hits 60, increase the current minute
byte seconds_2m; //Keeps track of the "wind speed/dir avg" over last 2 minutes array of data
byte minutes; //Keeps track of where we are in various arrays of data
byte minutes_10m; //Keeps track of where we are in wind gust/dir over last 10 minutes array of data
byte temperatura; //originalmente era byte
byte humedad;     //originalmente era byte
byte dht_dat[5];
byte bGlobalErr;

long lastWindCheck = 0;
volatile long lastWindIRQ = 0;
volatile byte windClicks = 0;

//We need to keep track of the following variables:
//Wind speed/dir each update (no storage)
//Wind gust/dir over the day (no storage)
//Wind speed/dir, avg over 2 minutes (store 1 per second)
//Wind gust/dir over last 10 minutes (store 1 per minute)
//Rain over the past hour (store 1 per minute)
//Total rain over date (store one per day)

byte windspdavg[120]; //120 bytes to keep track of 2 minute average
int winddiravg[120]; //120 ints to keep track of 2 minute average
float windgust_10m[10]; //10 floats to keep track of largest gust in the last 10 minutes
int windgustdirection_10m[10]; //10 ints to keep track of 10 minute max
volatile float rainHour[60]; //60 floating numbers to keep track of 60 minutes of rain

//These are all the weather values that wunderground expects:
int winddir; // [0-360 instantaneous wind direction]
float windspeedmph; // [mph instantaneous wind speed]
float windgustmph; // [mph current wind gust, using software specific time period]
int windgustdir; // [0-360 using software specific time period]
float windspdmph_avg2m; // [mph 2 minute average wind speed mph]
int winddir_avg2m; // [0-360 2 minute average wind direction]
float windgustmph_10m; // [mph past 10 minutes wind gust mph ]
int windgustdir_10m; // [0-360 past 10 minutes wind gust direction]
float humidity; // [%]
float tempf; // [temperature F]
float tempP;
float rainin; // [rain inches over the past hour)] -- the accumulated rainfall in the past 60 min
volatile float dailyrainin; // [rain inches so far today in local time]
//float baromin = 30.03;// [barom in] - It's hard to calculate baromin locally, do this in the agent
float pressure;
float presion;
float inhg;
float Td;

//float dewptf; // [dewpoint F] - It's hard to calculate dewpoint locally, do this in the agent

//These are not wunderground values, they are just for us
float batt_lvl = 11.8;
float light_lvl = 0.72;

// volatiles are subject to modification by IRQs
volatile unsigned long raintime, rainlast, raininterval, rain;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//Interrupt routines (these are called by the hardware interrupts, not by the main code)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void rainIRQ()
// Count rain gauge bucket tips as they occur
// Activated by the magnet and reed switch in the rain gauge, attached to input D2
{
  raintime = millis(); // grab current time
  raininterval = raintime - rainlast; // calculate interval between this and last event

    if (raininterval > 10) // ignore switch-bounce glitches less than 10mS after initial edge
  {
    dailyrainin += 0.011; //Each dump is 0.011" of water
    rainHour[minutes] += 0.011; //Increase this minute's amount of rain

    rainlast = raintime; // set up for next event
  }
}

void wspeedIRQ()
// Activated by the magnet in the anemometer (2 ticks per rotation), attached to input D3
{
  if (millis() - lastWindIRQ > 10) // Ignore switch-bounce glitches less than 10ms (142MPH max reading) after the reed switch closes
  {
    lastWindIRQ = millis(); //Grab the current time
    windClicks++; //There is 1.492MPH for each click per second.
  }
}

void setup()
{
  wdt_reset(); //Pet the dog
  wdt_disable(); //We don't want the watchdog during init

  Serial.begin(9600);
  //imp.begin(19200);
    InitDHT();
  pinMode(WSPEED, INPUT_PULLUP); // input from wind meters windspeed sensor
  pinMode(RAIN, INPUT_PULLUP); // input from wind meters rain gauge sensor

  pinMode(WDIR, INPUT);
  pinMode(LIGHT, INPUT);
  pinMode(BATT, INPUT);
  pinMode(REFERENCE_3V3, INPUT);
  
  pinMode(STAT1, OUTPUT);

  midnightReset(); //Reset rain totals

  //Configure the pressure sensor
  myPressure.begin(); // Get sensor online
  myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
  myPressure.setOversampleRate(128); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags 
  myPressure.setModeActive(); // Go to active mode and start measuring!

  //Configure the humidity sensor
 // myHumidity.begin();

  seconds = 0;
  lastSecond = millis();

  // attach external interrupt pins to IRQ functions
  attachInterrupt(0, rainIRQ, FALLING);
  attachInterrupt(1, wspeedIRQ, FALLING);

  // turn on interrupts
  interrupts();

  //Serial.println("Wimp Weather Station online!"); yo lo comente
  reportWeather();

//  wdt_enable(WDTO_1S); //Unleash the beast
}

void loop()
{
  wdt_reset(); //Pet the dog
  
  //Keep track of which minute it is
  if(millis() - lastSecond >= 1000)
  {
    lastSecond += 1000;

    //Take a speed and direction reading every second for 2 minute average
    if(++seconds_2m > 119) seconds_2m = 0;

    //Calc the wind speed and direction every second for 120 second to get 2 minute average
    windspeedmph = get_wind_speed();
    winddir = get_wind_direction();
    windspdavg[seconds_2m] = (int)windspeedmph;
    winddiravg[seconds_2m] = winddir;
    //if(seconds_2m % 10 == 0) displayArrays();

    //Check to see if this is a gust for the minute
    if(windspeedmph > windgust_10m[minutes_10m])
    {
      windgust_10m[minutes_10m] = windspeedmph;
      windgustdirection_10m[minutes_10m] = winddir;
    }

    //Check to see if this is a gust for the day
    //Resets at midnight each night
    if(windspeedmph > windgustmph)
    {
      windgustmph = windspeedmph;
      windgustdir = winddir;
    }


 
    //Blink stat LED briefly to show we are alive
    digitalWrite(STAT1, HIGH);
    //reportWeather(); //Print the current readings. Takes 172ms.
    delay(25);
    digitalWrite(STAT1, LOW);

    //If we roll over 60 seconds then update the arrays for rain and windgust
    if(++seconds > 59)
    {
      seconds = 0;

      if(++minutes > 59) minutes = 0;
      if(++minutes_10m > 9) minutes_10m = 0;

      rainHour[minutes] = 0; //Zero out this minute's rainfall amount
      windgust_10m[minutes_10m] = 0; //Zero out this minute's gust
    }
  }

  //Wait for the imp to ping us with the ! character
  if(Serial.available())
  {
    byte incoming = Serial.read();
    if(incoming == '!')
    {
      reportWeather(); //Send all the current readings out the imp and to its agent for posting to wunderground. Takes 196ms
      //Serial.print("Pinged!");
    }
    else if(incoming == '@') //Special character from Imp indicating midnight local time
    {
      midnightReset(); //Reset a bunch of variables like rain and total rain
      //Serial.print("Midnight reset");
    }
    else if(incoming == '#') //Special character from Imp indicating a hardware reset
    {
      //Serial.print("Watchdog reset");
      delay(5000); //This will cause the system to reset because we don't pet the dog
    }
  }

  delay(100); //Update every 100ms. No need to go any faster.
}

//Prints the various arrays for debugging
void displayArrays()
{
  //Windgusts in this hour
  Serial.println();
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);

  Serial.print("Windgust last 10 minutes:");
  for(int i = 0 ; i < 10 ; i++)
  {
    if(i % 10 == 0) Serial.println();
    Serial.print(" ");
    Serial.print(windgust_10m[i]);
  }

  //Wind speed avg for past 2 minutes
  /*Serial.println();
   Serial.print("Wind 2 min avg:");
   for(int i = 0 ; i < 120 ; i++)
   {
   if(i % 30 == 0) Serial.println();
   Serial.print(" ");
   Serial.print(windspdavg[i]);
   }*/

  //Rain for last hour
  Serial.println();
  Serial.print("Rain hour:");
  for(int i = 0 ; i < 60 ; i++)
  {
    if(i % 30 == 0) Serial.println();
    Serial.print(" ");
    Serial.print(rainHour[i]);
  }


}
//When the imp tells us it's midnight, reset the total amount of rain and gusts
void midnightReset()
{
  dailyrainin = 0; //Reset daily amount of rain

  windgustmph = 0; //Zero out the windgust for the day
  windgustdir = 0; //Zero out the gust direction for the day
  pressure = 0;
  minutes = 0; //Reset minute tracker
  seconds = 0;
  lastSecond = millis(); //Reset variable used to track minutes
}

//Calculates each of the variables that wunderground is expecting
void calcWeather()
{
  //current winddir, current windspeed, windgustmph, and windgustdir are calculated every 100ms throughout the day
//int chk = DHT11.read((DHT11PIN));
  //Calc windspdmph_avg2m
  float temp = 0;
  for(int i = 0 ; i < 120 ; i++)
    temp += windspdavg[i];
  temp /= 120.0;
  windspdmph_avg2m = temp;

  //Calc winddir_avg2m
  temp = 0; //Can't use winddir_avg2m because it's an int
  for(int i = 0 ; i < 120 ; i++)
    temp += winddiravg[i];
  temp /= 120;
  winddir_avg2m = temp;

  //Calc windgustmph_10m
  //Calc windgustdir_10m
  //Find the largest windgust in the last 10 minutes
  windgustmph_10m = 0;
  windgustdir_10m = 0;
  //Step through the 10 minutes  
  for(int i = 0; i < 4 ; i++)
  {
    if(windgust_10m[i] > windgustmph_10m)
    {
      windgustmph_10m = windgust_10m[i];
      windgustdir_10m = windgustdirection_10m[i];
    }
  }

  //Calc humidity
ReadDHT();

      humedad = dht_dat[0];
      temperatura = dht_dat[2];
      humidity = humedad;
//   Serial.print("Humidity (%): ");
 // Serial.println(humedad);

  //humidity = myHumidity.readHumidity();
  //float temp_h = myHumidity.readTemperature();
//  Serial.print(" Temp C:");
//  Serial.println(temperatura);
  //Serial.print(temp_h, 2);
 tempf=1.8 * temperatura + 32;
 
//  Serial.print(" Temp F:");
//  Serial.println(tempf);
  //Calc tempf from pressure sensor
 // tempf = myPressure.readTempF();

  //Serial.print(" TempP:");
  //Serial.print(tempf, 2);

  //Total rainfall for the day is calculated within the interrupt
  //Calculate amount of rainfall for the last 60 minutes
  rainin = 0;  
  for(int i = 0 ; i < 60 ; i++)
    rainin += rainHour[i];

  //Calc pressure
   //esto lo puse para calcular la presion
  float pressure = myPressure.readPressure();
//  Serial.println("Pressure(Pa):");
//  Serial.println(pressure, 2);

  double temperature = tempf;//myPressure.readTempF();
 // Serial.print(" Temp(f):");
 // Serial.print(temperature, 2);

  const int station_elevation_m = 87; //Accurate for the roof on my house
  //1 pascal = 0.01 millibars
 //pressure /=100;
 //Serial.println("Pressure(Pa):");
 // Serial.println(pressure, 2);
 presion=pressure *=0.000295301;  //esto es Barometric
 
//hasta aca fue agregado para la presion
//  pressure = myPressure.readPressure();
  
  //Calc dewptf
 // float humidity=68;
        double a = 17.271;
	double b = 237.7;
	double temppp = (a * temperature) / (b + temperature) + log(humidity*0.01);
	float Tr = (b * temppp) / (a - temppp);
Td=Tr;
 

// Tr = tempf - ((100 - humidity)/5);;
 
  //Calc light level
  light_lvl = get_light_level();

  //Calc battery level
  batt_lvl = get_battery_level();
}

//Returns the voltage of the light sensor based on the 3.3V rail
//This allows us to ignore what VCC might be (an Arduino plugged into USB has VCC of 4.5 to 5.2V)
float get_light_level()
{
  float operatingVoltage = averageAnalogRead(REFERENCE_3V3);

  float lightSensor = averageAnalogRead(LIGHT);
  
  operatingVoltage = 3.3 / operatingVoltage; //The reference voltage is 3.3V
  
  lightSensor *= operatingVoltage;
  
  return(lightSensor);
}

//Returns the voltage of the raw pin based on the 3.3V rail
//This allows us to ignore what VCC might be (an Arduino plugged into USB has VCC of 4.5 to 5.2V)
//Battery level is connected to the RAW pin on Arduino and is fed through two 5% resistors:
//3.9K on the high side (R1), and 1K on the low side (R2)
float get_battery_level()
{
  float operatingVoltage = averageAnalogRead(REFERENCE_3V3);

  float rawVoltage = averageAnalogRead(BATT);
  
  operatingVoltage = 3.30 / operatingVoltage; //The reference voltage is 3.3V
  
  rawVoltage *= operatingVoltage; //Convert the 0 to 1023 int to actual voltage on BATT pin
  
  rawVoltage *= 4.90; //(3.9k+1k)/1k - multiply BATT voltage by the voltage divider to get actual system voltage
  
  return(rawVoltage);
}

//Returns the instataneous wind speed
float get_wind_speed()
{
  float deltaTime = millis() - lastWindCheck; //750ms

  deltaTime /= 1000.0; //Covert to seconds

  float windSpeed = (float)windClicks / deltaTime; //3 / 0.750s = 4

  windClicks = 0; //Reset and start watching for new wind
  lastWindCheck = millis();

  windSpeed *= 1.492; //4 * 1.492 = 5.968MPH

  /* Serial.println();
   Serial.print("Windspeed:");
   Serial.println(windSpeed);*/

  return(windSpeed);
}

int get_wind_direction() 
// read the wind direction sensor, return heading in degrees
{
  unsigned int adc;

  adc = averageAnalogRead(WDIR); // get the current reading from the sensor

  // The following table is ADC readings for the wind direction sensor output, sorted from low to high.
  // Each threshold is the midpoint between adjacent headings. The output is degrees for that ADC reading.
  // Note that these are not in compass degree order! See Weather Meters datasheet for more information.

  if (adc < 380) return (113);
  if (adc < 393) return (68);
  if (adc < 414) return (90);
  if (adc < 456) return (158);
  if (adc < 508) return (135);
  if (adc < 551) return (203);
  if (adc < 615) return (180);
  if (adc < 680) return (23);
  if (adc < 746) return (45);
  if (adc < 801) return (248);
  if (adc < 833) return (225);
  if (adc < 878) return (338);
  if (adc < 913) return (0);
  if (adc < 940) return (293);
  if (adc < 967) return (315);
  if (adc < 990) return (270);
  return (-1); // error, disconnected?
}


//Reports the weather string to the Imp
void reportWeather()
{
  calcWeather(); //Go calc all the various sensors

  /*imp.print("$,winddir=");
  imp.print(winddir);
  imp.print(",windspeedmph=");
  imp.print(windspeedmph, 1);
  imp.print(",windgustmph=");
  imp.print(windgustmph, 1);
  imp.print(",windgustdir=");
  imp.print(windgustdir);
  imp.print(",windspdmph_avg2m=");
  imp.print(windspdmph_avg2m, 1);
  imp.print(",winddir_avg2m=");
  imp.print(winddir_avg2m);
  imp.print(",windgustmph_10m=");
  imp.print(windgustmph_10m, 1);
  imp.print(",windgustdir_10m=");
  imp.print(windgustdir_10m);
  imp.print(",humidity=");
  imp.print(humidity, 1);
  imp.print(",tempf=");
  imp.print(tempf, 1);
  imp.print(",rainin=");
  imp.print(rainin, 2);
  imp.print(",dailyrainin=");
  imp.print(dailyrainin, 2);
  imp.print(","); //Don't print pressure= because the agent will be doing calcs on the number
  imp.print(pressure, 2);
  imp.print(",batt_lvl=");
  imp.print(batt_lvl, 2);
  imp.print(",light_lvl=");
  imp.print(light_lvl, 2);
  imp.print(",");
  imp.println("#,");*/
//float Tr;
  Serial.print("&winddir=");
  Serial.print(winddir);
  Serial.print("&windspeedmph=");
  Serial.print(windspeedmph, 1);
  Serial.print("&windgustmph=");
  Serial.print(windgustmph, 1);
  Serial.print("&windgustdir=");
  Serial.print(windgustdir);
  Serial.print("&windspdmph_avg2m=");
  Serial.print(windspdmph_avg2m, 1);
  Serial.print("&winddir_avg2m=");
  Serial.print(winddir_avg2m);
  Serial.print("&windgustmph_10m=");
  Serial.print(windgustmph_10m, 1);
  Serial.print("&windgustdir_10m=");
  Serial.print(windgustdir_10m);
  Serial.print("&humidity=");
  Serial.print(humidity, 1);
  Serial.print("&tempf=");
  Serial.print(tempf, 1);
  Serial.print("&rainin=");
  Serial.print(rainin, 2);
  Serial.print("&dailyrainin=");
  Serial.print(dailyrainin, 2);
  Serial.print("&baromin="); //Don't print pressure= because the agent will be doing calcs on the number
  Serial.print(presion, 2);
  Serial.print("&batt_lvl=");
  Serial.print(batt_lvl, 2);
  Serial.print("&light_lvl=");
  Serial.print(light_lvl, 2);
  Serial.print("&dewptf=");
  Serial.print(Td);
  Serial.print("&");
  Serial.println("#");
  
  windgustmph = 0; //Zero out the windgust for the day
  windgustdir = 0; //Zero out the gust direction for the day
  
  //Test string
  //Serial.println("$,winddir=270,windspeedmph=0.0,windgustmph=0.0,windgustdir=0,windspdmph_avg2m=0.0,winddir_avg2m=12,windgustmph_10m=0.0,windgustdir_10m=0,humidity=998.0,tempf=-1766.2,rainin=0.00,dailyrainin=0.00,-999.00,batt_lvl=16.11,light_lvl=3.32,#,");
}

//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  
}


void InitDHT(){

   pinMode(dht_dpin,OUTPUT);

   digitalWrite(dht_dpin,HIGH);

}

 

void ReadDHT(){

bGlobalErr=0;

byte dht_in;

byte i;

digitalWrite(dht_dpin,LOW);

delay(20);


digitalWrite(dht_dpin,HIGH);

delayMicroseconds(40);

pinMode(dht_dpin,INPUT);

//delayMicroseconds(40);

dht_in=digitalRead(dht_dpin);

 

if(dht_in){

   bGlobalErr=1;

   return;

   }

delayMicroseconds(80);

dht_in=digitalRead(dht_dpin);

 

if(!dht_in){

   bGlobalErr=2;

   return;

   }

delayMicroseconds(80);

for (i=0; i<5; i++)

   dht_dat[i] = read_dht_dat();

pinMode(dht_dpin,OUTPUT);

digitalWrite(dht_dpin,HIGH);

byte dht_check_sum =

       dht_dat[0]+dht_dat[1]+dht_dat[2]+dht_dat[3];

if(dht_dat[4]!= dht_check_sum)

   {bGlobalErr=3;}

};

 

byte read_dht_dat(){

  byte i = 0;

  byte result=0;

  for(i=0; i< 8; i++){

      while(digitalRead(dht_dpin)==LOW);

      delayMicroseconds(30);

      if (digitalRead(dht_dpin)==HIGH)

     result |=(1<<(7-i));

    while (digitalRead(dht_dpin)==HIGH);

    }

  return result;

}

