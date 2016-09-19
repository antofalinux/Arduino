#include <OneWire.h>
#include <DallasTemperature.h>
//#include <SoftwareSerial.h>

//period between posts, set at 60 seconds
#define DELAY_PERIOD 60000

//pin for the DS18B20 temperature module
#define TEMPERATURE_PIN 3

// Important!! We use pin 13 for enable esp8266  
#define WIFI_ENABLE_PIN 13

#define SSID "sanson"
#define PASS "vIcente25"
#define PUBLIC_KEY "ppppppppp"
#define PRIVATE_KEY "kkkkkkkkk"

#define DEBUG 0


OneWire oneWire(TEMPERATURE_PIN);
DallasTemperature sensors(&oneWire);

// use http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html 
// to find the address of your DS18B20, it will be different then this
DeviceAddress thermometer = { 0x28, 0xFF, 0xED, 0xC9, 0x81, 0x15, 0x02, 0xB2 };

char serialbuffer[100];//serial buffer for request command
long nextTime;//next time in millis that the temperature read will fire
int wifiConnected = 0;

//SoftwareSerial Serial1(11, 12); // rx, tx

void setup()
{
Serial1.begin(9600);//connection to ESP8266
Serial.begin(9600); //serial debug

if(DEBUG) {
while(!Serial);
}

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    delay(1000);//delay

    //set mode needed for new boards
    Serial1.println("AT+RST");
    delay(3000);//delay after mode change       
    Serial1.println("AT+CWMODE=1");
    delay(300);
    Serial1.println("AT+RST");
    delay(500);

    sensors.begin();

    nextTime = millis();//reset the timer
}

boolean connectWifi() {     
 String cmd="AT+CWJAP=\"";
 cmd+=SSID;
 cmd+="\",\"";
 cmd+=PASS;
 cmd+="\"";
 Serial.println(cmd);
 Serial1.println(cmd);
           
 for(int i = 0; i < 20; i++) {
   Serial.print(".");
   if(Serial1.find("OK"))
   {
     wifiConnected = 1;
     break;
   }
   
   delay(50);
 }
 
 Serial.println(
   wifiConnected ? 
   "OK, Connected to WiFi." :
   "Can not connect to the WiFi."
 );
 
 return wifiConnected;
}

void loop()
{

    if(!wifiConnected) {
      Serial1.println("AT");
      delay(1000);
      if(Serial1.find("OK")){
        Serial.println("Module Test: OK");
        connectWifi();
      } 
    }

    if(!wifiConnected) {
      delay(500);
      return;
    }

    //output everything from ESP8266 to the Arduino Micro Serial output
    while (Serial1.available() > 0) {
      Serial.write(Serial1.read());
    }

    //to send commands to the ESP8266 from serial monitor (ex. check IP addr)
    if (Serial.available() > 0) {
       //read from serial monitor until terminating character
       int len = Serial.readBytesUntil('\n', serialbuffer, sizeof(serialbuffer));

       //trim buffer to length of the actual message
       String message = String(serialbuffer).substring(0,len-1);
       
       Serial.println("message: " + message);

       //check to see if the incoming serial message is an AT command
       if(message.substring(0,2)=="AT"){
         //make command request
         Serial.println("COMMAND REQUEST");
         Serial1.println(message); 
       }//if not AT command, ignore
    }

    //wait for timer to expire
    if(nextTime<millis()){
      Serial.print("timer reset: ");
      Serial.println(nextTime);

      //reset timer
      nextTime = millis() + DELAY_PERIOD;
      
      //get temp
      sensors.requestTemperatures();
      //send temp
      SendTempData(sensors.getTempC(thermometer));

    }
}


//web request needs to be sent without the http for now, https still needs some working
void SendTempData(float temperature){
 char temp[10];

 Serial.print("temp: ");     
 Serial.println(temperature);

 dtostrf(temperature,1,2,temp);

 //create start command
 String startcommand = "AT+CIPSTART=\"TCP\",\"data.sparkfun.com\", 80";
 
 Serial1.println(startcommand);
 Serial.println(startcommand);
 
 //test for a start error
 if(Serial1.find("Error")){
   Serial.println("error on start");
   return;
 }
 
 //create the request command
 String sendcommand = "GET /input/"; 
 sendcommand.concat(PUBLIC_KEY);
 sendcommand.concat("?private_key=");
 sendcommand.concat(PRIVATE_KEY);
 sendcommand.concat("&temp=");
 sendcommand.concat(String(temp));
 //sendcommand.concat("\r\n");
 //sendcommand.concat(" HTTP/1.0\r\n\r\n");
 sendcommand.concat(" HTTP/1.1\n");
 sendcommand.concat("Host: data.sparkfun.com\n");
 sendcommand.concat("Connection: close\n\n");
 
 Serial.println(sendcommand);
 
 
 //send to ESP8266
 Serial1.print("AT+CIPSEND=");
 Serial1.println(sendcommand.length());
 
 //display command in serial monitor
 Serial.print("AT+CIPSEND=");
 Serial.println(sendcommand.length());
 
 if(Serial1.find(">"))
 {
   Serial.println(">");
 }else
 {
   //Serial1.println("AT+CIPCLOSE");
   Serial.println("connect timeout");
   delay(1000);
   return;
 }
 
 //Serial.print("Debug:");
 //Serial.print(sendcommand);
 Serial1.print(sendcommand);
 delay(1000);
 Serial1.println("AT+CIPCLOSE");
}


