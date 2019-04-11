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

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

char ssid[] = "ssid";  //  your network SSID (name)
char pass[] = "*****";       // your network password


unsigned int localPort = 2390;      // local port to listen for UDP packets

IPAddress timeServer(200, 54, 149, 19); // ntp.shoa.cl NTP server
//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;


unsigned long segundestotales;


void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println();

  // We start by connecting to a WiFi network
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("");
  
  Serial.println("WiFi conectado");
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());

  Serial.println("Iniciando UDP");
  udp.begin(localPort);
  Serial.print("Puerto Local: ");
  Serial.println(udp.localPort());
  Serial.println("");
  Serial.println("");

}

void loop()
{
  sendNTPpacket(timeServer); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);
  unsigned long secsSince1900;
  
  int cb = udp.parsePacket();
  if (!cb) {
    Serial.println("Aun no hay respuesta");
    Serial.print("Segun yo llevamos ");
    Serial.print(segundestotales);
    Serial.println(" Segundos");

    // now convert NTP time into everyday time:
    Serial.print("Segun yo Tiempo Unix = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYearsa = 2208988800UL;
    // subtract seventy years:
    unsigned long epocha = segundestotales - seventyYearsa;
    // print Unix time:
    Serial.println(epocha);
        // print the hour, minute and second:
    Serial.print("Segun yo La hora UTC es ");       // UTC is the time at Greenwich Meridian (GMT)
    int horab=((epocha  % 86400L) / 3600);
            if (horab<10 ){
    Serial.print("0"); //imprime un cero si es menor a 10
    }
    Serial.print(horab); // print the hour (86400 equals secs per day)
    Serial.print(':');
    if ( ((epocha % 3600) / 60) < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
     //   Serial.print('0');
        Serial.print(horab);
    }
    int minutosa =((epocha  % 3600) / 60);
            if (minutosa<10 ){
    Serial.print("0"); //imprime un cero si es menor a 10
    }
    Serial.print(minutosa); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    if ( (epocha % 60) < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
   //   Serial.print('0');
      Serial.print(minutosa);

    }
    int segundosa=(epocha % 60);
    Serial.println(segundosa);
   // Serial.println(epoch % 60); // print the second
  
//#############################  
   Serial.print("Segun yo La Hora en Antofagasta es ");       // UTC -4 SCL time
    if (horab==0 ){
    horab=24; //12 si es de 12 horas y no 24
    }
    if (horab==1 ){
    horab=25; //13 si es de 12 horas y no 24
    }
    if (horab==2 ){
    horab=26; //14 si es de 12 horas y no 24
    }
    if (horab==3 ){
    horab=27; //15 si es de 12 horas y no 24 
    }
    if (horab==4 ){
    horab=28; //16 si es de 12 horas y no 24 
    }

    
    int horala=(horab-4);
        if (horala<10 ){
    Serial.print("0"); //imprime un cero si es menor a 10
    }
    Serial.print(horala); // print the hour (86400 equals secs per day)
    Serial.print(':');
        if (minutosa<10 ){
    Serial.print("0"); //imprime un cero si es menor a 10
    }
    Serial.print(minutosa); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    Serial.println(segundosa);
    Serial.println("");
    Serial.println("");
//############################ 

    
  }
  else {
    Serial.print("Paquete NTP recibido, largo= ");
    Serial.print(cb);
      Serial.println(" Caracteres");
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    secsSince1900 = highWord << 16 | lowWord;
    Serial.print("Segundos desde el 1 de Enero de 1900 = " );
    segundestotales =secsSince1900;
    Serial.println(secsSince1900);

    // now convert NTP time into everyday time:
    Serial.print("Tiempo Unix = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
    Serial.println(epoch);


    // print the hour, minute and second:
    Serial.print("La hora UTC es ");       // UTC is the time at Greenwich Meridian (GMT)
    int hora=((epoch  % 86400L) / 3600);
    if (hora<10 ){
    Serial.print("0"); //imprime un cero si es menor a 10
    }
    Serial.print(hora); // print the hour (86400 equals secs per day)
    Serial.print(':');
    if ( ((epoch % 3600) / 60) < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
        Serial.print('0');

    }
    int minutos =((epoch  % 3600) / 60);
    if (minutos<10 ){
    Serial.print("0"); //imprime un cero si es menor a 10
    }
    Serial.print(minutos); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    if ( (epoch % 60) < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
      Serial.print(minutos);

    }
    int segundos=(epoch % 60);
    Serial.println(segundos);
   // Serial.println(epoch % 60); // print the second
  
//#############################  
   Serial.print("La Hora en Antofagasta es ");       // UTC -4 SCL time
    if (hora==0 ){
    hora=24; //12 si es de 12 horas y no 24
    }
    if (hora==1 ){
    hora=25; //13 si es de 12 horas y no 24
    }
    if (hora==2 ){
    hora=26; //14 si es de 12 horas y no 24
    }
    if (hora==3 ){
    hora=27; //15 si es de 12 horas y no 24 
    }
    if (hora==4 ){
    hora=28; //16 si es de 12 horas y no 24 
    }

    
    int horal=(hora-4);
     if (horal<10 ){
    Serial.print("0"); //imprime un cero si es menor a 10
    }
    Serial.print(horal); // print the hour (86400 equals secs per day)
    Serial.print(':');
        if (minutos<10 ){
    Serial.print("0"); //imprime un cero si es menor a 10
    }
    Serial.print(minutos); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    Serial.println(segundos);
    Serial.println("");
    Serial.println("");
//############################  
  }  
  // wait ten seconds before asking for the time again
  delay(10000);
  segundestotales =secsSince1900+11; //arreglo para cuando no tiene señal
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.print("Enviando paquete NTP a ");
  Serial.println("ntp.shoa.cl");
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

