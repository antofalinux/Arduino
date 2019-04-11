//Programa : Arduino Ethernet Shield W5100 e HC-SR04
//Alteracoes e adaptacoes : FILIPEFLOP
//
//Baseado no programa exemplo de
//by David A. Mellis e Tom Igoe
 
//#include <Ultrasonic.h>
#include <SPI.h>
#include <Ethernet.h>
//#include <EthernetUdp.h>

#define dht_dpin 5
//Inicializa o sensor ultrasonico
//Ultrasonic ultrasonic(PINO_TRIGGER, PINO_ECHO);
 
byte bGlobalErr;
int lectura=0;
int lectura1=0;
byte dht_dat[5];
const int buttonPin=3;
const int ledPin =  13; 
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

const int humedad = dht_dat[0];  //invento mio para meter valor a variable
const int temperatura = dht_dat[2];// lo mismo

//const int humedad;  //invento mio para meter valor a variable
//const int temperatura; 
double temperatura1; 
 // long secsSince1900;
 // long epoch =0;
 // long hora;
 
 
//Definicoes de IP, mascara de rede e gateway
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,158);          //Define o endereco IP
IPAddress gateway(192,168,1,1);     //Define o gateway
IPAddress subnet(255, 255, 255, 0); //Define a máscara de rede
 
//Inicializa o servidor web na porta 80
EthernetServer server(80);
//NTP
//unsigned int localPort = 8080;            //  Puerto local para escuchar UDP
char dataserver[] = "data.sparkfun.com";    // name address for data.sparkFun (using DNS)
//IPAddress timeServer(193,92,150,3);       // time.nist.gov NTP server (fallback)
//IPAddress timeServer(130,206,3,166);    // Red Iris Bilbao
//IPAddress timeServer(130,206,206,248);  // Red Iris Madrid
const int NTP_PACKET_SIZE= 48;   // La hora son los primeros 48 bytes del mensaje
byte packetBuffer[ NTP_PACKET_SIZE];  // buffer para los paquetes

//EthernetUDP Udp;       // Una instancia de UDP para enviar y recibir mensajes 
EthernetClient client;

/////////////////
// Phant Stuff //
/////////////////
const String publicKey = "********";
const String privateKey = "*******";
const byte NUM_FIELDS = 5;
const String fieldNames[NUM_FIELDS] = {"gas", "humedad", "humo", "puerta", "temperatura"};
String fieldData[NUM_FIELDS];
 
void setup()
{
 pinMode(buttonPin, INPUT);  

  //Inicializa la interface de red
  Serial.begin (9600);

  // while (!Serial) {
  //  ; // wait for serial port to connect. Needed for Leonardo only
 // }
   Ethernet.begin(mac);
 // Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
//  Udp.begin(localPort);
}
 
void loop() {
  
//  sendNTPpacket(timeServer);           // Enviar una peticion
const int lectura=analogRead(A0);
  lectura1=analogRead(A1);
  buttonState = digitalRead(buttonPin);
 // epoch =0;
 // hora=0;
  delay(1000);

//unsigned long epoch = hora;
 //delay(100);  
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

    Serial.println("Posting!");
    postData(); // the postData() function does all the work, 
                // check it out below. 
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
    client.println("Connection: close");
    client.println();
  }
  else
  {
    Serial.println(F("Connection failed"));
  } 

  // Check for a response from the server, and route it
  // out the serial port.
  while (client.connected())
  {
    if ( client.available() )
    {
      char c = client.read();
      Serial.print(c);
    }      
  }
  Serial.println();
  client.stop();
}

