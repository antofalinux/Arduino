#include <ESP8266WiFi.h>
#include <Wire.h> //I2C needed for sensors  
#include <SoftwareSerial.h>
SoftwareSerial swSer(14, 12, false, 256);
#include "DHT.h"  
#define DHTPIN          2   //Pin to attach the DHT (pinD4 en el node)
#define DHTTYPE DHT11       //type of DTH  
const char* ssid     = "Netwok"; 
const char* password = "*****";
const int sleepTimeS = 60; //18000 for Half hour, 300 for 5 minutes etc.
const byte WDIR = A0;
const byte WSPEED = 14;
  ///////////////Weather//////////////////////// 
char server [] = "weatherstation.wunderground.com";  
char WEBPAGE [] = "GET /weatherstation/updateweatherstation.php?";
char ID [] = "IREGINDE61";
char PASSWORD [] = "vIcente25";
float tempa = 0;

DHT dht(DHTPIN, DHTTYPE);               

void setup() {
  // put your setup code here, to run once:
 delay(100);
  Serial.println();
  Serial.println();
  Serial.println("Inicializando Sistema ");
  Serial.print("Conectando a ");
  Serial.println(ssid);  
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
    
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.begin(9600);
  swSer.begin(9600);
    
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // Set WiFi mode to station (as opposed to AP or AP_STA)

}

void loop() {
  // put your main code here, to run repeatedly:

  dht.begin();
Serial.println("Leyendo sensor");

  float tempc = dht.readTemperature(); 
       Serial.println("Sensor leido");
        if (tempa==0) { 
    tempa = tempc;
  }
        if ((tempc-tempa)>3) { 
    loop();
  }
          if (tempc>tempa) {
    tempa= tempc;
  }

       Serial.print("Temperatura: ");
       Serial.print(tempc);
       Serial.print(" C  ");
  float tempf =  (tempc * 9.0)/ 5.0 + 32.0; 
         Serial.print(tempf);
       Serial.println(" F");   
      Serial.print("Temperatura MAX: ");
       Serial.print(tempa);
       Serial.print(" C  ");    
  float humidity = dht.readHumidity(); 
  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.println(" %");
  double dewptf = (dewPoint(tempc, dht.readHumidity())); 
    Serial.print("Punto de rocio: ");
  Serial.println(dewptf);

}

double dewPoint(double tempc, double humidity) //Calculate dew Point
{
  
}

