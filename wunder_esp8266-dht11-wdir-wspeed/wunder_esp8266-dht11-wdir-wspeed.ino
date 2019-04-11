#include <ESP8266WiFi.h>
#include <Wire.h> //I2C needed for sensors
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"    
#define DHTPIN          2   //Pin to attach the DHT (pinD4 en el node)
#define DHTTYPE DHT11       //type of DTH  
const char* ssid     = "Netwok"; 
const char* password = "*****";
const int sleepTimeS = 60; //18000 for Half hour, 300 for 5 minutes etc.
#define ONE_WIRE_BUS 12  // DS18B20 pin
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
const byte WDIR = A0;
const byte WSPEED = 14;
float tempa = 0;
float tempb = 0;
float oldTemp;
                               
///////////////Weather//////////////////////// 
char server [] = "weatherstation.wunderground.com";  
char WEBPAGE [] = "GET /weatherstation/updateweatherstation.php?";
char ID [] = "IREGINDE61";
char PASSWORD [] = "vIcente25";


/////////////IFTTT///////////////////////
//////////////////////////////////////////
DHT dht(DHTPIN, DHTTYPE);               
           


void setup()
{
  Serial.begin(9600);
  dht.begin();
  Wire.begin(4, 5);  //sda scl
  pinMode(WDIR, INPUT);

  pinMode(WSPEED, INPUT_PULLUP); // input from wind meters windspeed sensor
  //Configure the pressure sensor
/*  myPressure.begin(); // Get sensor online
  myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
  myPressure.setOversampleRate(128); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags 
  myPressure.setModeActive(); // Go to active mode and start measuring!
*/

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
  // Set WiFi mode to station (as opposed to AP or AP_STA)
  WiFi.mode(WIFI_STA);
}

void loop(){  
  //Check battery
//  int level = analogRead(A0);
//  level = map(level, 0, 1024, 0, 100);
//  if(level<50)
//  { 
//   mandarNot(); //Send IFTT
//   Serial.println("Low batter");
//   delay(500);
//  }
  //Get sensor data
     Serial.println("Leyendo sensor");
  float temp;
  float tempc = dht.readTemperature(); 
       Serial.println("Sensor leido");
       
      if (tempa==0) { 
    tempa = tempc;
  }
        if ((tempc-tempa)>3) {
       tempc=temp;    
    loop();
  }
          if (tempc>tempa) {
    tempa= tempc;
  }



    DS18B20.requestTemperatures(); 
    temp = DS18B20.getTempCByIndex(0);
    Serial.print("Temperature: ");
    Serial.println(temp);

  
  if (temp != oldTemp)
  {
    oldTemp = temp;
  }

       Serial.print("Temperatura: ");
       Serial.print(tempc);
       Serial.print(" C  ");
       tempb=tempc;
  float tempf =  (temp * 9.0)/ 5.0 + 32.0; 
         Serial.print(tempf);
       Serial.println(" F");
       Serial.print("Temperatura MAX: ");
       Serial.print(tempa);
       Serial.println(" C  ");
       Serial.print("Temperatura DS18B20: ");
       Serial.print(temp);
       Serial.println(" C  ");
  float humidity = dht.readHumidity(); 
  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.println(" %");
  double dewptf = (dewPoint(tempc, dht.readHumidity())); 
    Serial.print("Punto de rocio: ");
  Serial.println(dewptf);
//  float pressure = myPressure.readPressure();
//  Serial.print("Pressure: ");
//  Serial.println(pressure);
//  float presion=pressure *=0.000295301;
//  Serial.print("Presion: ");
//  Serial.println(presion);
  //check sensor data
  Serial.println("+++++++++++++++++++++++++");
  Serial.print("tempF= ");
  Serial.print(tempf);
  Serial.println(" *F");
  Serial.print("tempC= ");
  Serial.print(tempc);
  Serial.println(" *C");
  Serial.print("dew point= ");
  Serial.println(dewptf);
  Serial.print("humidity= ");
  Serial.println(humidity);
  
  //Send data to Weather Underground
  Serial.print("connecting to ");
  Serial.println(server);
  WiFiClient client;
  if (!client.connect(server, 80)) {
    Serial.println("Conection Fail");
    return;
  }
    client.print(WEBPAGE); 
    client.print("ID=");
    client.print(ID);
    client.print("&PASSWORD=");
    client.print(PASSWORD);
    client.print("&dateutc=");
    client.print("now");    
    client.print("&tempf=");
    client.print(tempf);
//    client.print("&dewptf=");
//    client.print(dewptf);
    client.print("&humidity=");
    client.print(humidity);
    client.print("&softwaretype=ESP%208266O%20version1&action=updateraw&realtime=1&rtfreq=2.5");
    client.println();
    delay(500); 
      while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
    Serial.println(server);
    Serial.print(WEBPAGE); 
    Serial.print("ID=");
    Serial.print(ID);
    Serial.print("&PASSWORD=");
    Serial.print(PASSWORD);
    Serial.print("&dateutc=");
    Serial.print("now");    
    Serial.print("&tempf=");
    Serial.print(tempf);
    Serial.print("&dewptf=");
    Serial.print(dewptf);
    Serial.print("&humidity=");
    Serial.print(humidity);
    Serial.print("&softwaretype=ESP%208266O%20version1&action=updateraw&realtime=1&rtfreq=2.5");
    Serial.println();
//    sleepMode();    

}


double dewPoint(double tempc, double humidity) //Calculate dew Point
{
  double AA= 17.271;
  double Ab= 237.7;
  

  Serial.print("Temperatura: ");
  Serial.print(tempc);
  Serial.println(" C  ");
  Serial.print("Humedad: ");
  Serial.println(humidity);

  double Ac= 0.01;
  //log(humidity*0.01);
    Serial.print("Ac ");
  Serial.println(Ac);
  double SUM = (AA * tempc) / (Ab + tempc) + Ac;
    Serial.println("SUM ");  
    Serial.println(SUM);
  double VP = (Ab * SUM) / (AA - SUM);
  Serial.print("VP ");
    Serial.println(VP);
  double BB= VP;
  Serial.print("BB ");
      Serial.println(BB);    
  return BB;
}


void sleepMode(){
  Serial.print(F("Sleeping..."));
//  ESP.deepSleep(sleepTimeS * 1000000);
}

