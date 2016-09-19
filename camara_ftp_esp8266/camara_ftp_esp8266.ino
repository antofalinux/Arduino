/*
 * Wifi Camera ESP8266
 * 
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <string.h>
#include<stdlib.h>

byte incomingbyte;
int a=0x0000,  //Read Starting address     
    j=0,
    k=0,
    count=0,
    sendcount=0;
    
uint8_t MH,ML;
boolean EndFlag=0;

const char *ssid     = "sanson";
const char *password = "vIcente25";

const char* server = "webcam.wunderground.com";


WiFiClient client;
WiFiClient dclient;

char outBuf[128];
char outCount;

int sizeout;


//************************************************SETUP**********************************************//

void setup ( void ) {

  WiFi.begin ( ssid, password );

  
  Serial.begin ( 38400 );
  
  //SendResetCmd();
  //delay(3000);
  
  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );

 Serial.println("\nWiFi Conectada");
  Serial.println(WiFi.localIP());  
  Serial.println();
  }
}


//************************************************LOOP**********************************************//


void loop ( void ) {
   Serial.print("Tratando de conectar a ");
   Serial.print(server);
   Serial.println(" en el puerto 21");
   client.connect(server,21); //esto lo puse yo 
   
   if (client.connect(server,21)) {
    Serial.println(F("Estamos Conectados!!!"));
  
  eRcv();
  Serial.println("USER antofalinuxCAM1");
  client.println("USER antofalinuxCAM1"); //FTP User

  eRcv();
  Serial.println("PASS *************");
  client.println("PASS vIcente25"); //FTP Password
 
  eRcv();
  Serial.println("SYST");
  client.println("SYST");

//  eRcv();
// Serial.println("FEAT");
// client.println("FEAT"); 

  eRcv();
  Serial.println("PWD");
  client.println("PWD"); //Change Directory

  eRcv();
  Serial.println("Type I");
  client.println("Type I");

//  eRcv();
//  Serial.println("PASV");
//  client.println("PASV");
  
//  eRcv();
//  Serial.println("MLSD");
//  client.println("MLSD");
  
  eRcv();
  Serial.println("PASV");
  client.println("PASV");
  eRcv();

  char *tStr = strtok(outBuf,"(,");
  int array_pasv[6];
  for ( int i = 0; i < 6; i++) {
    tStr = strtok(NULL,"(,");
    array_pasv[i] = atoi(tStr);
    if(tStr == NULL)
    {
      Serial.println(F("Bad PASV Answer"));    

    }
  }

  unsigned int hiPort,loPort;

  hiPort = array_pasv[4] << 8;
  loPort = array_pasv[5] & 255;

  Serial.print(F("Data port: "));
  hiPort = hiPort | loPort;
  Serial.println(hiPort);

  dclient.connect(server,hiPort); //esto lo puse yo
//  if (dclient.connect(server,hiPort)) {
    Serial.println(F("Data connected"));
//  } 
//  else {
//    Serial.println(F("Data connection failed"));
//    client.stop();
//  }

  Serial.print("STOR ");
  Serial.println(F("image_1.jpg"));
  client.print("STOR ");
  client.println(F("image_1.jpg"));
  picture_ld();

  if(!eRcv())
  {
    dclient.stop();
  }

Serial.println(F("Writing"));

  byte clientBuf[64];
  int clientCount = 0;
  
  String out = "";
  
 // picture_hd();
    picture_ld();
  
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
      dclient.print(out);
      out = "";
    }
    
  }
  sizeout = out.length();
    if (sizeout > 0)
    {
      dclient.print(out);
      out = "";
    }

  delay(1000);
  
  StopTakePhotoCmd(); //stop this picture so another one can be taken
  EndFlag = 0; //reset flag to allow another picture to be read   

  dclient.stop();
  Serial.println(F("Data disconnected"));

  eRcv();

  client.println("QUIT");

  eRcv();

  client.stop();
  Serial.println(F("Command disconnected"));

  } 
  else {
    Serial.println(F("Command connection failed")); 
  }

delay(1000); //esto era 60000
  
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

}

//*****************************************CAMERA COMMAND**************************************//

//Send Reset command
void SendResetCmd() {
// Serial.write((byte)0x56);
//  Serial.println("\n56002600");
// Serial.write((byte)0x00);
// Serial.write((byte)0x26);
// Serial.write((byte)0x00);
   Serial.print("56");
   Serial.print("00");
   Serial.print("26");
   Serial.println("00");   
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
//  Serial.write((byte)MH);
//  Serial.write((byte)ML);
  Serial.write((byte)0xff);// esto lo puse yo
  Serial.write((byte)0xd8);// esto lo puse yo
    
  
  Serial.write((byte)0x00);
  Serial.write((byte)0x00);
  Serial.write((byte)0xff);// esto lo puse yo
  Serial.write((byte)0xd9);// esto lo puse yo
  Serial.write((byte)0x00);// esto lo puse yo  
  Serial.write((byte)0xff);

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



byte eRcv()
{
  byte respCode;
  byte thisByte;

  while(!client.available()) delay(0);

  respCode = client.peek();

  outCount = 0;

  while(client.available())
  {  
    thisByte = client.read();    
    Serial.write(thisByte);

    if(outCount < 127)
    {
      outBuf[outCount] = thisByte;
      outCount++;      
      outBuf[outCount] = 0;
    }
  }

  if(respCode >= '4')
  {
    efail();
    return 0;  
  }

  return 1;
}


void efail()
{
  byte thisByte = 0;

  client.println(F("QUIT"));

  while(!client.available()) delay(1);

  while(client.available())
  {  
    thisByte = client.read();    
    Serial.write(thisByte);
  }

  client.stop();
  Serial.println(F("Command disconnected"));
}

