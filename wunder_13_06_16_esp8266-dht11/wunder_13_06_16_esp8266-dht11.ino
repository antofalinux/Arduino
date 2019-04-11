#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OneWire.h>
#include <DallasTemperature.h> 
#include "DHT.h"
   
#define DHTPIN          2   //Pin to attach the DHT (pinD4 en el node)
#define DHTTYPE DHT11       //type of DTH  
const char* ssid     = "Netwok"; 
const char* password = "*****";
const int sleepTimeS = 60; //18000 for Half hour, 300 for 5 minutes etc.
unsigned int localPort = 2390;      // local port to listen for UDP packets
IPAddress timeServer(200, 54, 149, 19); // ntp.shoa.cl NTP server

//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;
unsigned long segundestotales;
#define ONE_WIRE_BUS 12  // DS18B20 pin
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
SoftwareSerial esp(13,15); // RX, TX into Imp pin 8
float tempa = 0;
float tempb = 0;
float oldTemp;
String data="";
String data1="";
char input;
unsigned char i=0, ok=0;
unsigned char buffer[300];
unsigned long secsincon=0;
unsigned long secssincon=0;
                               
///////////////Weather//////////////////////// 
char server [] = "weatherstation.wunderground.com";  
char WEBPAGE [] = "GET /weatherstation/updateweatherstation.php?";
char ID [] = "IREGINDE61";
char PASSWORD [] = "vIcente2#5";

/////////////IFTTT///////////////////////
//////////////////////////////////////////
DHT dht(DHTPIN, DHTTYPE);               
           


void setup()
{
  Serial.begin(9600);
  esp.begin(9600); // Debug
  Serial.setTimeout(5000); 
  dht.begin();

  delay(100);
  Serial.println();
  Serial.println();
  Serial.println("");
  Serial.println("");
  Serial.println("Inicializando Sistema ");
  Serial.print("Conectando a ");
  Serial.println(ssid);  
  Serial.println("");
  Serial.println("");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");
   
  secsincon=secsincon+1;
  Serial.print(secsincon);
  Serial.println(" Segundos sin coneccion");
    if (secsincon>180){
    Serial.println("6 minutos sin Coneccion, es hora de reiniciar el sistema...");
rst();
}
  }
  
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // Set WiFi mode to station (as opposed to AP or AP_STA)
  WiFi.mode(WIFI_STA);
  Serial.println("Iniciando UDP");
  udp.begin(localPort);
  Serial.print("Puerto Local: ");
  Serial.println(udp.localPort());
  secsincon=0;
}

void loop(){  

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
//       tempc=23;
//       temp=23;
//       tempa=23;

       tempb=tempc;
  float tempf =  (tempc * 9.0)/ 5.0 + 32.0; 
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
 // humidity=44;
  Serial.print(humidity);
  Serial.println(" %");
    esp.println("!");
  Serial.println("!");

double jota=tempc;

//##################
// Control de errores de lectura
if(jota<-10){
jota=0;
secsincon=secsincon+1;
Serial.print(secsincon);
Serial.println(" Lecturas erroneas bajas");
    if (secsincon>180){
    Serial.println("3 minutos con lecturas erroneas, es hora de reiniciar el sistema...");
rst();
}  
}
if(jota>500){
jota=0;  
secsincon=secsincon+1;
Serial.print(secsincon);
Serial.println(" Lecturas erroneas altas");
    if (secsincon>180){
    Serial.println("3 minutos con lecturas erroneas, es hora de reiniciar el sistema...");
rst();
// Control de errores de lectura
}
}

  Serial.println("ENVIANDO DATOS PARA SU CALCULO ");

  delay(1000);
//  dewPoint();
//  windir();

  double dewptf = (dewPoint(tempf, humidity)); 
  Serial.print("Punto de rocio: ");
  Serial.println(dewptf);

//  long ntp = (tempc);
/*  float pressure = myPressure.readPressure();
  Serial.print("Pressure: ");
  Serial.println(pressure);
  float presion=pressure *=0.000295301;
  Serial.print("Presion: ");
  Serial.println(presion);
  
  //check sensor data
  Serial.println("+++++++++++++++++++++++++");
  Serial.print("tempF= ");
  Serial.print(tempf);
  Serial.println(" *F");
  Serial.print("tempC= ");
  Serial.print(tempc);
  Serial.println(" *C");
  Serial.print("dew point= ");
//  Serial.println(dewptf);
  Serial.print("humidity= ");
//  Serial.println(humidity);
 */ 
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
//    client.print(dewptf);
   client.print("&humidity=");
   client.print(humidity);
    client.print(data);
    client.print(data1);
    client.print("&softwaretype=ESP%208266O%20version201606&action=updateraw&realtime=1&rtfreq=2.5");
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
//    Serial.print("&");
    Serial.print(data); 
    Serial.print(data1);
    Serial.print("&tempf=");
    Serial.print(tempf);
    Serial.print("&dewptf=");
    Serial.print(dewptf);
    Serial.print("&humidity=");
    Serial.print(humidity);
    Serial.print("&softwaretype=ESP%208266O%20version1&action=updateraw&realtime=1&rtfreq=2.5");
    Serial.println();    

    ntp();
}
//$&dewpoint=0,00&rainin=0.00&dailyrainin=0.00&pressure=-999.00&batt_lvl=16.11&light_lvl=3.32#    

double dewPoint(double tempf, double humidity) //Calculate dew Point
//void dewPoint()
{
  Serial.println("Calculando punto de rocio...");
  Serial.println("");
  double A0= 373.15/(273.15 + tempf);
  double SUM = -7.90298 * (A0-1);
  SUM += 5.02808 * log10(A0);
  SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
  SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
  SUM += log10(1013.246);
  double VP = pow(10, SUM-3) * humidity;
  double T = log(VP/0.61078);   
  return (241.88 * T) / (17.558-T);

}
/*
void windir()
{
  
//  Serial.print("Temperatura: ");
//  Serial.print(tempc);
//  Serial.println(" C  ");
//  Serial.print("Humedad: ");
//  Serial.println(humidity);
delay(50);

//Si se recibió un dato entra
if (esp.available()>0){
input=esp.read(); //Leo dato
if(input=='$'){
input='&';  
//data="&";
}
if(input!='#'){
  
buffer[i]=input;
data+=input;
//Serial.println(data);
buffer[i+1]='\0';
//Serial.println(data);
i++;
windir();
}else ok=1;
//Si ya llego toda la trama entra aqui
if(ok==1){
//leo el buffer, proceso información y borro el buffer
//Serial.println(i);
//Serial.println(ok);
Serial.print("data1= ");
Serial.println(data);
Serial.print(data.length());
Serial.println(" Caracteres");
ok=0; //bajo bandera
i=0; //borro el contador
data1+=data;
return;
}
}
}
*/

void sleepMode(){
  Serial.print(F("Sleeping..."));
//  ESP.deepSleep(sleepTimeS * 1000000);
}

void ntp()
{

  sendNTPpacket(timeServer); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);
  unsigned long secsSince1900;
  int cb = udp.parsePacket();
  if (!cb) {
    Serial.println("Aun no hay respuesta");
      secssincon=secssincon+10;
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
    Serial.print(horab); // print the hour (86400 equals secs per day)
    Serial.print(':');
    if ( ((epocha % 3600) / 60) < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
     //   Serial.print('0');
        Serial.print(horab);
    }
    int minutosa =((epocha  % 3600) / 60);
    Serial.print(minutosa); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    if ( (epocha % 60) < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
   //   Serial.print('0');
      Serial.print(minutosa);

    }
    int segundosa=(epocha % 60);
                if (segundosa<10 ){
    Serial.print("0"); //imprime un cero si es menor a 10
    }
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
    horab=4; //16 si es de 12 horas y no 24 
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
                if (segundosa<10 ){
    Serial.print("0"); //imprime un cero si es menor a 10
    }
    Serial.println(segundosa);
    Serial.println("");
    Serial.println("");
//############################ 

  Serial.print(secssincon);
  Serial.println(" Segundos sin coneccion");
    if (secssincon>180){
    Serial.println("6 minutos sin Coneccion, es hora de reiniciar el sistema...");
rst();
}
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
  //  if ( ((epoch % 3600) / 60) < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      //  Serial.print('0');

   // }
    int minutos =((epoch  % 3600) / 60);
    if (minutos<10 ){
    Serial.print("0"); //imprime un cero si es menor a 10
    }
    Serial.print(minutos); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    //if ( (epoch % 60) < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
   //   Serial.print('0');
    //  Serial.print(minutos);

  //  }
    int segundos=(epoch % 60);
        if (segundos<10 ){
    Serial.print("0"); //imprime un cero si es menor a 10
    }
    Serial.println(segundos);
   // Serial.println(epoch % 60); // print the second
  
//#############################  
   Serial.print("La Hora en Antofagasta es ");       // UTC -4 SCL time
    secssincon=0;
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
    hora=4; //16 si es de 12 horas y no 24 
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
        if (segundos<10 ){
    Serial.print("0"); //imprime un cero si es menor a 10
    }
    Serial.println(segundos);
    Serial.println("");
    Serial.println("");
    
//############################ 
//esto para generar un reset a la media noche
if(horal=0){
  if(minutos==0){
    Serial.println("media noche, es hora de reiniciar parametros...");
    esp.println("@");
    Serial.println("@");
rst();
  }
}

 //############################ 
  }  
  // wait ten seconds before asking for the time again
  delay(5000);  //5 segundos

  segundestotales =secsSince1900+11; //arreglo para cuando no tiene señal
// return segundestotales;
loop();
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.println("");  
  Serial.println("");
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

void rst()
{
    Serial.println("Reiniciando sistema en 3 Segundos");
    delay(1000);
    Serial.println("Reiniciando sistema en 2 Segundos");
    delay(1000);
    Serial.println("Reiniciando sistema en 1 Segundo");
    delay(1000);
    Serial.println("Reiniciando sistema...");
    ESP.restart();
}


