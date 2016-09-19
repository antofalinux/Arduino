/*
 Udp NTP Client
 Get the time from a Network Time Protocol (NTP) time server
 Demonstrates use of UDP sendPacket and ReceivePacket
 For more on NTP time servers and the messages needed to communicate with them,
 see http://en.wikipedia.org/wiki/Network_Time_Protocol
 created 4 Sep 2010
 by Michael Margolis
 modified 9 Apr 2012
 by Tom Igoe
 updated for the ESP8266 12 Apr 2015 
 by Ivan Grokhotkov
 This code is in the public domain.
 */

//#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>

char ssid[] = "sanson";  //  your network SSID (name)
char pass[] = "vIcente25";       // your network password
int hora;
int luz=4;
int Hencendido=19; //19
int Hapagado=23; //23

unsigned int localPort = 2390;      // local port to listen for UDP packets

IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(4, 0);
  digitalWrite(5, 0);

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());
}

void loop()
{
  sendNTPpacket(timeServer); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);
  
  int cb = udp.parsePacket();
  if (!cb) {
    Serial.println("no packet yet");
  }
  else {
    Serial.print("packet received, length=");
    Serial.println(cb);
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("Seconds since Jan 1 1900 = " );
    Serial.println(secsSince1900);

    // now convert NTP time into everyday time:
    Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
    Serial.println(epoch);


    // print the hour, minute and second:
    Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
    Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
    Serial.print(':');
    if ( ((epoch % 3600) / 60) < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    if ( (epoch % 60) < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.println(epoch % 60); // print the second
  
Serial.print("The Local time is ");    // UTC es el tiempo universal o GMT
    Serial.print(((epoch   % 86400L) / 3600)-3);  // Horas (86400 segundos por dia)
    hora =(((epoch   % 86400L) / 3600)-3); 
    Serial.print(':');  
    if ( ((epoch % 3600) / 60) < 10 ) {
      // Añadir un 0 en los primeros 9 minutos
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); // Minutos: 
    Serial.print(':'); 
    if ( (epoch % 60) < 10 ) {
      // Añadir un 0 en los primeros 9 minutos
      Serial.print('0');
    }
    Serial.println(epoch %60);               // Segundos
//    Serial.println(" ");
//    Serial.print(hora);
//    Serial.println(" Hrs.");
  }
  delay(10000); 
  Serial.println(" ");
  tiempo();

}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
  
}

void tiempo (){
  
  if (hora>=Hencendido && hora<=Hapagado){
  digitalWrite(4,LOW);
  digitalWrite(5, HIGH);
  Serial.println("Luces Encendidas");

  }
//  if (hora>Hapagado && hora<Hencendido){
  else{
  digitalWrite(4, HIGH); 
  digitalWrite(5, LOW);
  Serial.println("Luces Apagadas");

  }
//  else{
// digitalWrite(luz, LOW); 
//  digitalWrite(3, HIGH);
//  Serial.println("Luces Apagadas contrario");
//   Serial.print(hora);
//    Serial.println(" Hrs.");
//  }
  Serial.print(hora);
   Serial.println(" Hrs Actual.");
  Serial.print(Hencendido);
   Serial.println(" Hrs.Encendido");
  Serial.print(Hapagado);
   Serial.println(" Hrs.Apagado");
    Serial.println("");
}

