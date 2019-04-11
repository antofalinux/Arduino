
#include <ESP8266WiFi.h>
#include "DHT.h"    
#define DHTPIN          2   //Pin to attach the DHT
#define DHTTYPE DHT11       //type of DTH  
const char* ssid     = "Netwok"; 
const char* password = "*****";
const int sleepTimeS = 10; //18000 for Half hour, 300 for 5 minutes etc.
                               
///////////////Weather//////////////////////// 
char server [] = "weatherstation.wunderground.com";  
char WEBPAGE [] = "GET /weatherstation/updateweatherstation.php?";
char ID [] = "IREGINDE61";
char PASSWORD [] = "YourPasswordOfWunderground";


/////////////IFTTT///////////////////////
const char* host = "maker.ifttt.com";//dont change
const String IFTTT_Event = "YourEventName"; 
const int puertoHost = 80;
const String Maker_Key = "YourMakerKey";
String conexionIF = "POST /trigger/"+IFTTT_Event+"/with/key/"+Maker_Key +" HTTP/1.1\r\n" +
                    "Host: " + host + "\r\n" + 
                    "Content-Type: application/x-www-form-urlencoded\r\n\r\n";
//////////////////////////////////////////
DHT dht(DHTPIN, DHTTYPE);               
           


void setup()
{
  Serial.begin(9600);

  dht.begin();
  delay(1000);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void loop(){  
  //Check battery
  int level = analogRead(A0);
  level = map(level, 0, 1024, 0, 100);
  if(level<50)
  { 
//   mandarNot(); //Send IFTT
   Serial.print("Low battery= ");
   Serial.println(level);
   delay(500);
  }
  //Get sensor data
  float tempc = dht.readTemperature(); 
  tempc=23;
  float tempf =  (tempc * 9.0)/ 5.0 + 32.0; 
  float humidity = dht.readHumidity(); 
  humidity= 44;
  float dewptf = (dewPoint(tempf, humidity)); 
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
    client.print("&dewptf=");
    client.print(dewptf);
    client.print("&humidity=");
    client.print(humidity);
    client.print("&softwaretype=ESP%208266O%20version1&action=updateraw&realtime=1&rtfreq=2.5");
    client.println();
    delay(500); //2500
//    sleepMode();    

}


double dewPoint(double tempf, double humidity) //Calculate dew Point
{
  Serial.println("Calculando punto de rocio");

Serial.println("Plan B");
  Serial.println(humidity);
       double a = 17.271;
       double b = 237.7;
      double temppp = (a * tempf) / (b + tempf) + log(humidity*0.01);
      float Tr = (b * temppp) / (a - temppp);
    float Td=Tr;
    Tr = tempf - ((100 - humidity)/5);
    Serial.println(temppp);
  Serial.print("Punto de rocio= ");
  Serial.println(Tr);
  Serial.println("");
  Serial.println("Ahora de verdad...");
  double A0= 373.15/(273.15 + tempf);
  Serial.print("A0= 373.15/273.15+ tempf= ");
  Serial.println(A0);
  double SUM = -7.90298 * (A0-1);
  Serial.print("A0-1 *-7.90298= ");
  Serial.println(SUM);
  SUM += 5.02808 * log10(A0);
  Serial.print("Log(A0) *5.02808= ");
  Serial.println(SUM);
  SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
  Serial.println(SUM);
  SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
  Serial.println(SUM);
  SUM += log10(1013.246);
    Serial.print("Log(1013.246)= ");
  Serial.println(SUM);
  double VP = pow(10, SUM-3) * humidity;
  Serial.print("VP= ");
  Serial.println(VP);
  double T = log(VP/0.61078);   
  Serial.print("T= ");
  Serial.println(T);
  Serial.print("Punto de Rocio 2= ");
  Serial.println((241.88 * T) / (17.558-T));
  return (241.88 * T) / (17.558-T);
  Serial.println(VP);
  Serial.println(T);
  //Calc dewptf
  
    
}

