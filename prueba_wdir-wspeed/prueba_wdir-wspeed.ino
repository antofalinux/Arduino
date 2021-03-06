#include <ESP8266WiFi.h>
#include <Wire.h> //I2C needed for sensors
const char* ssid     = "Netwok"; 
const char* password = "*****";
const int vane = A0;
const byte anemometer = 14;
unsigned int counter = 0;
unsigned int RPM = 0;
unsigned int winddir = 0.0;
const unsigned long period = 2500;
const float pi = 3.14159265;
const int radio = 30; //diametro del anemometro

float windspeedmph =0/ 0.445;
float windgustmph =0;
//Global Variables
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
byte minutes_10m; //Keeps track of where we are in wind gust/dir over last 10 minutes array of data

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


void setup()
{
  Serial.begin(9600);
  Wire.begin(4, 5);
pinMode(14, INPUT_PULLUP);
 delay(100);
  Serial.println();
  Serial.println();
  Serial.println("Inicializando Sistema ");
  Serial.print("Conectando a ");
  Serial.println(ssid);  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
}


void loop()
{
windvelocity();
displaywind();
}

//Wind Speed Trigger/timer

void windvelocity()
{
  windspeedmph =0;
  counter = 0;
  attachInterrupt(0, addcount, RISING);
  unsigned long millis();
  long starTime = millis();
  while(millis() < starTime + period) {
}
 detachInterrupt(0);
}
//RPM calc needed for wind speed calc
void RPMcalc(){
  RPM=((counter*4)*60)/(period/1000); // Calculate revolutions per minute (RPM)
  Serial.print("RPM ");
Serial.println(RPM);
}
void WindSpeed(){
  windspeedmph = ((2 * pi * radio * RPM)/60) / 1000;
  Serial.print("Velocidad ");
Serial.println(windspeedmph);
}
void addcount(){
  counter++;
}

//obtenemos voltaje por la direccion
void Heading(){
  
  float windDir =(analogRead(A0)* 5.00 / 1023.0); //wind direction
  
  if ((windDir > 4.94)||(windDir < 0.01))

    (winddir = 0.0);// North
    
  if ((windDir >= 0.02)&&(windDir < 0.30))

    (winddir = 22.5);//NNE

  if ((windDir >= 0.31)&&(windDir < 0.72))

    (winddir = 45.0);//NE

  if ((windDir >= 0.72)&&(windDir < 0.99))

    (winddir= 67.5);//ENE

  if ((windDir >= 1.00)&&(windDir < 1.25))

    (winddir = 90.0);//E

  if ((windDir >= 1.26)&&(windDir < 1.52))

    (winddir= 112.5);//ESE

  if ((windDir >= 1.53)&&(windDir < 1.91))

    (winddir= 135.0);//SE

  if ((windDir >= 1.92)&&(windDir < 2.40))

    (winddir = 157.5);//SSE

  if ((windDir >= 2.41)&&(windDir < 2.73))

    (winddir = 180.0);//S

  if ((windDir >= 2.74)&&(windDir < 2.96))

    (winddir = 202.5);//SSW

  if ((windDir >= 2.97)&&(windDir < 3.37))

    (winddir = 225.0);//SW

  if ((windDir >= 3.38)&&(windDir < 3.55))

    (winddir = 247.5);//WSW

  if ((windDir >= 3.56)&&(windDir < 3.85))

    (winddir = 270.0);//W

  if ((windDir >= 4.13)&&(windDir < 4.06))

    (winddir = 292.5);//WNW

  if ((windDir >= 4.07)&&(windDir < 4.32))

  (winddir = 315.0);//NW

  if ((windDir >= 4.33)&&(windDir < 4.93))

    (winddir = 337.5);//NNW
    Serial.print("Direccion ");
Serial.println(winddir);
Serial.println(windDir);
}



//mostrar resultados
void displaywind()
{
Serial.print("RPM ");
Serial.println(RPM);
Serial.print("Velocidad ");
Serial.println(windspeedmph);
Serial.print("Direccion ");
Serial.println(winddir);
}


