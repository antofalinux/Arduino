/*
 Udp NTP Client
 
 Consigue la hora de un servidor NTP en internet
 Muestra el uso de UDP para envio y recepcion de paquetes
 
 Para ver los mensajes NTP y la forma de comunicarse, ver
 http://en.wikipedia.org/wiki/Network_Time_Protocol
 
 created 4 Sep 2010 , by Michael Margolis
 modified 17 Sep 2010 by Tom Igoe
 
 This code is in the public domain.

 */

#include <SPI.h>		 
#include <Ethernet.h>
#include <EthernetUdp.h>


byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
unsigned int localPort = 8080;			//  Puerto local para escuchar UDP
IPAddress timeServer(193,92,150,3); 		// time.nist.gov NTP server (fallback)
//IPAddress timeServer(130,206,3,166);          // Red Iris Bilbao
//IPAddress timeServer(130,206,206,248);          // Red Iris Madrid

const int NTP_PACKET_SIZE= 48; 				// La hora son los primeros 48 bytes del mensaje
byte packetBuffer[ NTP_PACKET_SIZE]; 			// buffer para los paquetes 

EthernetUDP Udp;                // Una instancia de UDP para enviar y recibir mensajes

void setup() 
{	Serial.begin(9600);
        Udp.begin(localPort);	
	if (Ethernet.begin(mac) == 0) 
            {   Serial.println("Fallo al configurar por DHCP");
		while(true);
	     }
	
}

void loop()
{
        Serial.println(timeServer);	
	sendNTPpacket(timeServer); 	// Enviar unaa peticion al servidor NTP

	delay(1000);	                // Damos tiempo a la respuesta
	if ( Udp.parsePacket() ) {  
                Serial.println("Hemos recibido un paquete");
		Udp.read(packetBuffer,NTP_PACKET_SIZE);	 // Leemos el paquete
		
		// La hora empieza en el byte 40 de la respuesta y es de 4 bytes o 2 words
		// Hay que extraer ambas word:
		
		unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
		unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);  
		// combine the four bytes (two words) into a long integer
		// this is NTP time (seconds since Jan 1 1900):
		unsigned long secsSince1900 = highWord << 16 | lowWord;	 
		Serial.print("Segundos desde 1 Enero de 1900 = " );
		Serial.println(secsSince1900);				 
		
		// Ahora a convertir el tiempo NTP en tiempo Uxix:
		Serial.print("Unix time = ");
		// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
		const unsigned long seventyYears = 2208988800UL;	 
		// subtract seventy years:
		unsigned long epoch = secsSince1900 - seventyYears;	 
		// print Unix time:
		Serial.println(epoch);		
		
		Serial.print("The UTC time is ");		// UTC es el tiempo universal o GMT
		Serial.print((epoch	 % 86400L) / 3600); 	// Horas (86400 segundos por dia)
		Serial.print(':');	
		if ( ((epoch % 3600) / 60) < 10 ) {
			// Añadir un 0 en los primeros 9 minutos
			Serial.print('0');
		}
		Serial.print((epoch	 % 3600) / 60); // Minutos: 
		Serial.print(':'); 
		if ( (epoch % 60) < 10 ) {
			// Añadir un 0 en los primeros 9 minutos
			Serial.print('0');
		}
		Serial.println(epoch %60);               // Segundos

Serial.print("The Local time is ");		// UTC es el tiempo universal o GMT
		Serial.print(((epoch	 % 86400L) / 3600)-3); 	// Horas (86400 segundos por dia)
		Serial.print(':');	
		if ( ((epoch % 3600) / 60) < 10 ) {
			// Añadir un 0 en los primeros 9 minutos
			Serial.print('0');
		}
		Serial.print((epoch	 % 3600) / 60); // Minutos: 
		Serial.print(':'); 
		if ( (epoch % 60) < 10 ) {
			// Añadir un 0 en los primeros 9 minutos
			Serial.print('0');
		}
		Serial.println(epoch %60);               // Segundos
	}
	delay(10000); 
	Serial.println(" ");

}

unsigned long sendNTPpacket(IPAddress& address)
{
	// set all bytes in the buffer to 0
	memset(packetBuffer, 0, NTP_PACKET_SIZE); 
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	packetBuffer[0] = 0b11100011;	  // LI, Version, Mode
	packetBuffer[1] = 0;	   // Stratum, or type of clock
	packetBuffer[2] = 6;	   // Polling Interval
	packetBuffer[3] = 0xEC;  // Peer Clock Precision
	// 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer[12]	= 49; 
	packetBuffer[13]	= 0x4E;
	packetBuffer[14]	= 49;
	packetBuffer[15]	= 52;
	
	// all NTP fields have been given values, now
	// you can send a packet requesting a timestamp: 
	
	Udp.beginPacket(address, 123); //NTP requests are to port 123
	Udp.write(packetBuffer,NTP_PACKET_SIZE);
	Udp.endPacket(); 
}

