//todas las salidas por serial fueron comentadas

#include <SPI.h> // Required to use Ethernet
#include <Ethernet.h> // The Ethernet library includes the client
#include <Progmem.h> // Allows us to sacrifice flash for DRAM
#define dht_dpin 5
#include <DS1302RTC.h>
#include <Time.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

char dataserver[] = "data.sparkfun.com";    // name address for data.sparkFun (using DNS)

EthernetClient client;
EthernetServer server(80);
/////////////////
// Phant Stuff //
/////////////////
const String publicKey = "*****";
const String privateKey = "*******";
const byte NUM_FIELDS = 10;
const String fieldNames[NUM_FIELDS] = {"gas", "humedad", "humo", "puerta", "temperatura", "luz", "dia", "hora", "minuto", "segundo"};
String fieldData[NUM_FIELDS];
String data;
byte bGlobalErr;
int lectura=0;
int lectura1=0;
byte dht_dat[5];
const int ledPin =  13; 
int buttonState = 0;         // variable for reading the pushbutton status
int temperatura1; 
int humedad;  //invento mio para meter valor a variable
int temperatura; 
const int luz=2;
int luzstatus;
int rele = 4;
int resetCounter = 0;
long lastConnectionTime = 0; 
DS1302RTC RTC(9, 8, 7);

 
//////////////////////
// Input Pins, Misc //
//////////////////////
//const int triggerPin = A0;
const int lightPin = A1;
const int switchPin = 3;
//int humedad =45;
//int temperatura=22;
int Puerta;
int humo=analogRead(A0);
int alarma=1;



void setup()
{
  Serial.begin(9600);
  pinMode(switchPin, INPUT);  
  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);
  // Setup Input Pins:
//  pinMode(triggerPin, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(lightPin, INPUT_PULLUP);
  pinMode(luz, OUTPUT);
  pinMode(alarma, OUTPUT);
  digitalWrite(alarma, LOW);
  digitalWrite(luz, LOW);  
  luzstatus=0;

  // Set Up Ethernet:
  setupEthernet();
  InitDHT();
//  server.begin();

data = "";
   Serial.println("RTC Sync");
  setSyncProvider(RTC.get);      // the function to get the time from the RTC
  if(timeStatus() == timeSet)
     Serial.println(" Ok!");
  else
    // Serial.println(" FAIL!");
    delay ( 1000 );

}

void loop()
{
  tmElements_t tm;
  ReadDHT();
//float temperatura; //declarola variable
  switch (bGlobalErr){

     case 0:

 temperatura1=(temperatura/10);
 humedad = dht_dat[0];
 temperatura = dht_dat[2];


        break;

     case 1:

        // Serial.println("Error 1: DHT start condition 1 not met.");

        break;

     case 2:

        // Serial.println("Error 2: DHT start condition 2 not met.");

        break;

     case 3:

        // Serial.println("Error 3: DHT checksum error.");

        break;

     default:

        // Serial.println("Error: Unrecognized code encountered.");

        break;

      }

  delay(500); 
  
  //////////////////
//////////////////
////Alarma del relay aca se cambian las horas
/////////////////
  if(hour() >= 19 && hour()< 22)
  {
    
    pinMode(rele, OUTPUT);
    digitalWrite(rele, HIGH);
    digitalWrite(luz, HIGH);  
    luzstatus=1;
}
else
{
    pinMode(rele, OUTPUT);
    digitalWrite(rele, LOW);
    digitalWrite(luz, LOW);  
    luzstatus=0;
}
  
  // If the trigger pin (3) goes low, send the data.
 
 if (digitalRead(switchPin)==HIGH)
 {
    
    digitalWrite(alarma, HIGH);
    digitalWrite(alarma, HIGH);
 }
 else
  {  
    digitalWrite(Puerta, LOW);
    digitalWrite(alarma, LOW);
 }

 if (!digitalRead(lightPin))
 { 
    // Gather data:
    fieldData[0] = String(analogRead(lightPin));
    lectura1= analogRead(lightPin);
    fieldData[1] = String(humedad);
    fieldData[2] = String(analogRead(A0));
    lectura=analogRead(A0);
    fieldData[3] = String(Puerta);
    fieldData[4] = String(temperatura);
    fieldData[5] = String(luzstatus);
    fieldData[6] = String(dayShortStr(weekday()));
    fieldData[7] = String(hour());
    fieldData[8] = String(minute());
    fieldData[9] = String(second());

    // Serial.println("enviado!");
    
 //  data = "gas1=" + fieldData[0] + "&hum1=" + fieldData[1]+ "&humo1=" + fieldData[2]+ "&puert1=" + fieldData[3]+ "&temp1=" + fieldData[4]+ "&luz1=" + fieldData[5]+ "&dia1=" + fieldData[6]+ "&hor1=" + fieldData[7]+ "&min1=" + fieldData[8]+ "&seg1=" + fieldData[9]; 
    
    delay(500);
    postData(); // the postData() function does all the work, 
                // check it out below.
                
                
}

EthernetClient client = server.available();
  if (client) {
    // Serial.println("");
    // Serial.println("Nuevo Cliente");
    // an http request ends with a blank line
   boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
  
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 2"); //Recarrega a pagina a cada 2seg
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          //Configura o texto e imprime o titulo no browser
          client.print("<font color=#FF0000><b><u>");
          client.print("Envio de informacion por la red utilizando Arduino");
          client.print("</u></b></font>");
          client.println("<br />");
          client.println("<br />");
           if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
          //Mostra o estado da porta digital 3
        //  int porta_digital = digitalRead(3);
          client.print("Puerta Principal : ");
          client.print("<b>");
          client.print(buttonState);
          client.println("</b>");
          client.print("  (0 = Cerrada, 1 = Abierta)");
          client.println("<br />");
          client.print("CO2: ");
          client.println("</b>");
          client.print(lectura);
          client.println("<br />");
          client.print("GAS: ");
          client.println("</b>");
          client.print(lectura1);
          client.println("<br />");
          client.print("Temperatura : ");
          client.print("<b>");
          client.print(temperatura,1);
          client.print("<b>");
          client.print(" C");
          client.println("</br>");
          client.print("Humedad : ");
          client.print("<b>");
          client.print(humedad,1);
          client.print("<b>");
          client.print(" %");
          client.println("<br />");
           client.print("Luz : ");
           client.println("</b>");
           client.print(luzstatus);
           client.print("<b>");
          client.print("  (0 = apagada, 1 = Encendida)"); 
          client.println("<br />");
          client.print("Dia : ");
          client.print("<b>");
          client.print(dayShortStr(weekday()));
          client.print("<b>");
          client.print(" ");
          client.print("<b>");
          client.print(day());
          client.print("<b>");
          client.print("/");
          client.print("<b>");
          client.print(month());
          client.print("<b>");
          client.print("/");
          client.print("<b>");
          client.print(year());
          client.print("<br/>");
          client.print(hour());
          client.print("<b>");
          client.print(":");
          client.print("<b>");
          client.print(minute());
          client.print("<b>");
          client.print(":");
          client.print("<b>");
          client.print(second());
          client.println("<br />");
          client.println("</b></html>");
         break;
        }
        if (c == '\n') {
          // you're starting a new line
         currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
   //  close the connection:
    client.stop();
    }

    // Serial.println("Posting!");
    delay(500);
}
void postData()
{
  // Make a TCP connection to remote host
  if (client.connect(dataserver, 80))
  {
    // Post the data! Request should look a little something like:
    // GET /input/publicKey?private_key=privateKey&light=1024&switch=0&name=Jim HTTP/1.1\n
    // Host: data.sparkfun.com\n
    // Connection: close\n
    // \n
    client.print("GET /input/");
    client.print(publicKey);
    client.print("?private_key=");
    client.print(privateKey);
    for (int i=0; i<NUM_FIELDS; i++)
    {
      client.print("&");
      client.print(fieldNames[i]);
      client.print("=");
      client.print(fieldData[i]);
    }
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(dataserver);
    client.println("Conneccion: cerrada");
    client.println();  
  }
  else
  {
    Serial.println("Connection Failed.");   
    Serial.println();
    
    resetCounter++;
    
    if (resetCounter >=5 ) {resetEthernetShield();}

    lastConnectionTime = millis(); 
  }
  
//aca inserte estas lineas


//hasta aca
  // Check for a response from the server, and route it
  // out the serial port.
  while (client.connected())
  {
    if ( client.available() )
    {
      char c = client.read();
      // Serial.print(c);
    }      
  }
  // Serial.println();
  client.stop();
//  dream();
}

void setupEthernet()
{
  // Serial.println("Configurando Ethernet...");
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    // Serial.println(F("Falla en configurar Ethernet usinando DHCP"));
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac);
  }
  // Serial.print("Mi direccion IP es: ");
  // Serial.println(Ethernet.localIP());
  // give the Ethernet shield a second to initialize:
  delay(1000);
}

void resetEthernetShield()
{
  Serial.println("Resetting Ethernet Shield.");   
  Serial.println();
  
  client.stop();
  delay(1000);
  
  Ethernet.begin(mac);
  delay(1000);
}



void InitDHT(){

   pinMode(dht_dpin,OUTPUT);

        digitalWrite(dht_dpin,HIGH);

}

 

void ReadDHT(){

bGlobalErr=0;

byte dht_in;

byte i;

digitalWrite(dht_dpin,LOW);

delay(20);

 

digitalWrite(dht_dpin,HIGH);

delayMicroseconds(40);

pinMode(dht_dpin,INPUT);

//delayMicroseconds(40);

dht_in=digitalRead(dht_dpin);

 

if(dht_in){

   bGlobalErr=1;

   return;

   }

delayMicroseconds(80);

dht_in=digitalRead(dht_dpin);

 

if(!dht_in){

   bGlobalErr=2;

   return;

   }

delayMicroseconds(80);

for (i=0; i<5; i++)

   dht_dat[i] = read_dht_dat();

pinMode(dht_dpin,OUTPUT);

digitalWrite(dht_dpin,HIGH);

byte dht_check_sum =

       dht_dat[0]+dht_dat[1]+dht_dat[2]+dht_dat[3];

if(dht_dat[4]!= dht_check_sum)

   {bGlobalErr=3;}

};

 

byte read_dht_dat(){

  byte i = 0;

  byte result=0;

  for(i=0; i< 8; i++){

      while(digitalRead(dht_dpin)==LOW);

      delayMicroseconds(30);

      if (digitalRead(dht_dpin)==HIGH)

     result |=(1<<(7-i));

    while (digitalRead(dht_dpin)==HIGH);

    }
 
  return result;
float humedad = dht_dat[0];  //invento mio para meter valor a variable
  float temperatura = dht_dat[2];// lo mismo
}

