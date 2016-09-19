//Programa : Arduino Ethernet Shield W5100 e HC-SR04
//Alteracoes e adaptacoes : FILIPEFLOP
//
//Baseado no programa exemplo de
//by David A. Mellis e Tom Igoe
 
//#include <Ultrasonic.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <DHT.h>

//Define os parametros para o sensor ultrasonico HC-SR04
#define trigPin  6 //Porta ligada ao pino Trigger do sensor
#define echoPin  7 //Porta ligada ao pino Echo do sensor
#define dht_dpin 5
//Inicializa o sensor ultrasonico
//Ultrasonic ultrasonic(PINO_TRIGGER, PINO_ECHO);
 
byte bGlobalErr;
int lectura=0;
int lectura1=0;
byte dht_dat[5];

float humedad;  //invento mio para meter valor a variable
  float temperatura; 
  float temperatura1;  
 
 
//Definicoes de IP, mascara de rede e gateway
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,158);          //Define o endereco IP
IPAddress gateway(192,168,1,1);     //Define o gateway
IPAddress subnet(255, 255, 255, 0); //Define a máscara de rede
 
//Inicializa o servidor web na porta 80
EthernetServer server(80);
 
void setup()
{
  
 InitDHT(); 
  //Inicializa la interface de red
  Serial.begin (9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}
 
void loop() {
  
  long duration, distance;
  lectura=analogRead(A0);
    lectura1=analogRead(A1);
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  delay(1000);
  //Aguarda conexao do browser
  EthernetClient client = server.available();
  if (client) {
    Serial.println("");
    Serial.println("Nuevo Cliente");
    // an http request ends with a blank line
   boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
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
          //Mostra o estado da porta digital 3
          int porta_digital = digitalRead(3);
          client.print("Puerta Principal : ");
          client.print("<b>");
          client.print(porta_digital);
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
          //Mostra as informacoes lidas pelo sensor ultrasonico
          client.print("Sensor Ultrasonico : ");
          client.print("<b>");
          client.print(distance);
       //   Serial.println(distance);
          client.print(" cm");
          client.println("</br>");
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
    
 ReadDHT();
//float temperatura; //declarola variable
  switch (bGlobalErr){

     case 0:
     
 


 Serial.print("Humedad Actual = ");

 Serial.print(dht_dat[0], DEC);


 //Serial.print(".");

 //Serial.print(dht_dat[1], DEC);

 Serial.print(" %  ");

 Serial.print("temperatura = ");
 temperatura1=(temperatura/10);
 humedad = dht_dat[0];
 temperatura = dht_dat[2];
 Serial.print(dht_dat[2], DEC);
 Serial.println(" C  ");
 Serial.println ("");
  Serial.print("Humedad Actual 1 = ");
 Serial.print(humedad, 0);
 Serial.print(" %  ");
 Serial.print("temperatura 1 = ");
 Serial.print(temperatura, 0);
 
 //Serial.print (temperatura1,DEC); //imprimo la variable
 //Serial.print (temperatura,DEC); //imprimo la variable
 //Serial.print(".");

// Serial.print(dht_dat[3], DEC);

 Serial.println(" C  ");

        break;

     case 1:

        Serial.println("Error 1: DHT start condition 1 not met.");

        break;

     case 2:

        Serial.println("Error 2: DHT start condition 2 not met.");

        break;

     case 3:

        Serial.println("Error 3: DHT checksum error.");

        break;

     default:

        Serial.println("Error: Unrecognized code encountered.");

        break;

      }

  delay(100);
   
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

