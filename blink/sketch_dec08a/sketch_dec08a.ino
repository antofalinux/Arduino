/*
 * Wifi Camera Bot ESP8266
 * 
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <string.h>
#include<stdlib.h>
#include <Servo.h>
 
Servo servo1;
Servo servo2;

//Ajust to find value to stop rotation of Continuous Servo
int servo1_zero=78;
int servo2_zero=78;

//Ajust for speed of Continuous Servo on clockwise rotation, decrease for speed up
int servo1_clock=68;
int servo2_clock=68;

//Ajust for speed of Continuous Servo on counter clockwise rotation, increase for speed up
int servo1_counterclock=88;
int servo2_counterclock=88;

byte incomingbyte;
int a=0x0000,  //Read Starting address     
    j=0,
    k=0,
    count=0,
    sendcount=0;
uint8_t MH,ML;
boolean EndFlag=0;

int sizeout;

//Change for your Wifi Network
const char *ssid     = "sanson";
const char *password = "vIcente25";
MDNSResponder mdns;

ESP8266WebServer server ( 80 );

//const int led = 13;

//************************************************SETUP**********************************************//

void setup ( void ) {
  
  WiFi.begin ( ssid, password );

  //Change for your Wifi Network
  //static ip, gateway, netmask
  WiFi.config(IPAddress(10,0,1,70), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
  
  Serial.begin ( 115200 );
  
  SendResetCmd();
  delay(1000);
  
  //ChangeSizeSmall();
  ChangeSizeMedium();
  ChangeSizeBig();
  delay(1000);
  
  SendResetCmd();
  delay(1000);
  
  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
  }



  if ( mdns.begin ( "esp8266", WiFi.localIP() ) ) {
    //Serial.println ( "MDNS responder started" );
  }

  server.on ( "/", handleRoot );
  server.on ( "/picture.jpg", picture );
  server.on ( "/picturepage.htm", picturepage );
  server.on ( "/picture_ld.htm", picture_ld );
  server.on ( "/picture_md.htm", picture_md );
  server.on ( "/picture_hd.htm", picture_hd );
  server.on ( "/command.htm", command );
  server.on ( "/go.htm", go );
  server.on ( "/back.htm", back );
  server.on ( "/left.htm", left );
  server.on ( "/right.htm", right );
  server.on ( "/stop.htm", Stop );
  server.on ( "/inline", []() {
    server.send ( 200, "text/plain", "this works as well" );
  } );
  server.onNotFound ( handleRoot );
  server.begin();
  //Serial.println ( "HTTP server started" );


 
  delay(500);
  servo_turnon();
  servo1.write(servo1_zero); 
  servo2.write(servo2_zero);
  delay(500); 
  //servo_turnoff();

}


//************************************************LOOP**********************************************//


void loop ( void ) {
  mdns.update();
  server.handleClient();
}

//*****************************************WEBSERVER HANDLE*****************************************//

void handleRoot() {
  //digitalWrite ( led, 1 );
  char temp[800];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  snprintf ( temp, 800,

"<html>\
  <head>\
    <title>ESP8266 Camera Bot</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body><center>\
    <h1>IP Camera Robot with an ESP8266 and serial JPEG camera!</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <iframe src='/picturepage.htm' width='640' height='480' scrolling='no'></iframe>\
    <p>Select Resolution:</p>\
    <input type='button' onclick=\"location.href='/picture_ld.htm'\" value='160x120' />\
    <input type='button' onclick=\"location.href='/picture_md.htm'\" value='320x240' />\
    <input type='button' onclick=\"location.href='/picture_hd.htm'\" value='640x480' />\
    <p>Commands:</p>\
    <iframe src='/command.htm' width='160' height='100' scrolling='no'></iframe>\
  </center></body>\
</html>",

    hr, min % 60, sec % 60
  );
  server.send ( 200, "text/html", temp );
}


void picturepage() {
  //digitalWrite ( led, 1 );
  char temp[500];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

String out = "";
out =+ "<html>\
  <head>\
    <title>Camera ESP8266 Cam</title>\
  </head>\
  <body style=\"margin:0;padding:0\">\
    <a HREF=\"/picturepage.htm\"><img width=100% height=100% src=\"/picture.jpg\" /><a/>\
  </body>\
</html>";
  server.send ( 200, "text/html", out );
}


//*****************************************CAMERA SNAPSHOOT**************************************//

void picture() {
  
  WiFiClient client = server.client();
  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: image/jpeg"));
  client.println(F(""));
 
  String out = "";
  
  SendTakePhotoCmd();
  delay(100);

while(Serial.available()>0) {
    incomingbyte=Serial.read();
  }
  byte b[32];
      
  while(!EndFlag) {  
    j=0;
    k=0;
    count=0;
    sendcount=0;
    SendReadDataCmd();
           
    delay(35); //try going up
    while(Serial.available()>0) {
      incomingbyte=Serial.read();
      k++;
      if((k>5)&&(j<32)&&(!EndFlag)) {
        b[j]=incomingbyte;
        out += (char)incomingbyte;
        if((b[j-1]==0xFF)&&(b[j]==0xD9))
        EndFlag=1;                           
        j++;
        count++;
      }
    }
    sizeout = out.length();
    if (sizeout >= 2048)
    {
      client.print(out);
      out = "";
    }
    
  }
  sizeout = out.length();
    if (sizeout > 0)
    {
      client.print(out);
      out = "";
    }
  delay(3000);
  
  StopTakePhotoCmd(); //stop this picture so another one can be taken
  EndFlag = 0; //reset flag to allow another picture to be read   
  


}



void picture_ld() {

  SendResetCmd();
  delay(1000);
  
  ChangeSizeSmall();
  //ChangeSizeMedium();
  //ChangeSizeBig();
  delay(1000);
  
  SendResetCmd();
  delay(1000);
 
  handleRoot();
}

void picture_md() {

  SendResetCmd();
  delay(1000);
  
  //ChangeSizeSmall();
  ChangeSizeMedium();
  //ChangeSizeBig();
  delay(1000);
  
  SendResetCmd();
  delay(1000);
 
  handleRoot();
}

void picture_hd() {

  SendResetCmd();
  delay(1000);
  
  //ChangeSizeSmall();
  //ChangeSizeMedium();
  ChangeSizeBig();
  delay(1000);
  
  SendResetCmd();
  delay(1000);
 
  handleRoot();
}

//*****************************************CAMERA COMMAND**************************************//

//Send Reset command
void SendResetCmd() {
  Serial.write((byte)0x56);
  Serial.write((byte)0x00);
  Serial.write((byte)0x26);
  Serial.write((byte)0x00);   
}

//Send take picture command
void SendTakePhotoCmd() {
  Serial.write((byte)0x56);
  Serial.write((byte)0x00);
  Serial.write((byte)0x36);
  Serial.write((byte)0x01);
  Serial.write((byte)0x00);
    
  a = 0x0000; //reset so that another picture can taken
}

void FrameSize() {
  Serial.write((byte)0x56);
  Serial.write((byte)0x00);
  Serial.write((byte)0x34);
  Serial.write((byte)0x01);
  Serial.write((byte)0x00);  
}

//Read data
void SendReadDataCmd() {
  MH=a/0x100;
  ML=a%0x100;
      
  Serial.write((byte)0x56);
  Serial.write((byte)0x00);
  Serial.write((byte)0x32);
  Serial.write((byte)0x0c);
  Serial.write((byte)0x00);
  Serial.write((byte)0x0a);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)MH);
  Serial.write((byte)ML);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0x20);
  Serial.write((byte)0x00);
  Serial.write((byte)0x0a);

  a+=0x20; 
}

void StopTakePhotoCmd() {
  Serial.write((byte)0x56);
  Serial.write((byte)0x00);
  Serial.write((byte)0x36);
  Serial.write((byte)0x01);
  Serial.write((byte)0x03);        
}

void ChangeSizeSmall() {
    Serial.write((byte)0x56);
    Serial.write((byte)0x00);
    Serial.write((byte)0x31);
    Serial.write((byte)0x05);
    Serial.write((byte)0x04);
    Serial.write((byte)0x01);
    Serial.write((byte)0x00);
    Serial.write((byte)0x19);
    Serial.write((byte)0x22);      
}

void ChangeSizeMedium()
{
    Serial.write((byte)0x56);
    Serial.write((byte)0x00);
    Serial.write((byte)0x31);
    Serial.write((byte)0x05);
    Serial.write((byte)0x04);
    Serial.write((byte)0x01);
    Serial.write((byte)0x00);
    Serial.write((byte)0x19);
    Serial.write((byte)0x11);      
}

void ChangeSizeBig()
{
    Serial.write((byte)0x56);
    Serial.write((byte)0x00);
    Serial.write((byte)0x31);
    Serial.write((byte)0x05);
    Serial.write((byte)0x04);
    Serial.write((byte)0x01);
    Serial.write((byte)0x00);
    Serial.write((byte)0x19);
    Serial.write((byte)0x00);      
}

//*****************************************SERVO COMMAND**************************************//

void go() {
  
  servo_go();
  command();        
}

void back() {
  
  servo_back(); 
  command();    
}

void left() {
  
  servo_left();  
  command();  
}

void right() {
  
  servo_right();
  command();   
}

void Stop() {
  
  servo_stop();
  command();   
}

void servo_go() {

  //servo_turnon();
  servo1.write(servo1_counterclock); 
  servo2.write(servo1_clock);
}

void servo_back() {

  //servo_turnon();
  servo1.write(servo1_clock); 
  servo2.write(servo1_counterclock);
}

void servo_stop() {
  
  servo1.write(servo1_zero); 
  servo2.write(servo2_zero);
  //servo_turnoff();
}

void servo_left() {

  //servo_turnon();
  servo1.write(servo1_clock); 
  servo2.write(servo1_clock);
  delay(300);
  servo1.write(servo1_zero); 
  servo2.write(servo2_zero);
  //servo_turnoff();
}

void servo_right() {

  //servo_turnon();
  servo1.write(servo1_counterclock); 
  servo2.write(servo1_counterclock);
  delay(300);
  servo1.write(servo1_zero); 
  servo2.write(servo2_zero);
  //servo_turnoff();
}

void servo_turnon() {
 
  servo1.attach(0);
  servo2.attach(2);
}

void servo_turnoff() {
  
  servo1.detach();
  servo2.detach();
}

//*****************************************HANDLE COMMAND**************************************//

void command() {
  
String out = "";
out =+ "<html>\
        <head>\
          <title>ESP8266 Command</title>\
          <style>\
           body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
          </style>\
        </head>\
        <body>\
          <table>\
          <tr><th></th><th><input type='button' onclick=\"location.href='/go.htm'\" value='Go' /></th><th></th></tr>\
          <tr><th><input type='button' onclick=\"location.href='/left.htm'\" value='Left' /></th><th><input type='button' onclick=\"location.href='/stop.htm'\" value='Stop' /></th><th><input type='button' onclick=\"location.href='/right.htm'\" value='Right' /></th></tr>\
          <tr><th></th><th><input type='button' onclick=\"location.href='/back.htm'\" value='Back' /></th><th></th></tr>\
          </table>\
        </body>\
        </html>";


  server.send ( 200, "text/html", out );

}


