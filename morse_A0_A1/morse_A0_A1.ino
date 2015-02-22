//**************************************************
///////////////////////////////////////////////////
//    CREATE BY CA1CVI http://www.antofalinux.cl
//    DESIGNED FOR AMATEUR RADIO COMMUNICATION
//    THIS PROGRAM IS UNDER BEERWARE LICENSE
//
// date: January 09, 2015 
// license: Beerware. Use, reuse, and modify this code however you see fit.
// If you find it useful, buy me a beer some day!
//
//
//**************************************************
// BASED ON THE WORK OF:
// Morse Code Balloon Beacon
// by Bill Brown WB8ELK <http://www.wb8elk.com>
// 
// Transmits Morse Code for balloon tracking
// by keying the SparkFun 434 MHz transmitter module
//
// Created 29 December 2008
// << -- Keyed CW mode -- >>
//**************************************************
//
// Adaptado y ampliado por EB1HBK y EB1WM, entre Mayo y Junio de 2011, para realizar la baliza
// experimental en 70 MHz "Delcon 70x70" de www.cacharreo.es
//
//****************************************************
//
//  AMPLIACIONES:
//
// Se ha cambiado el pin de CW al dpin 13, para evaluar visualmente la baliza en el LED
// integrado en la placa.
//
// Ademas se utiliza el dpin 12 como salida PTT, que se activa (HIGH) antes del envio del
// codigo morse, el retardo entre el PTT y el CW esta fijado en 125 msg pero puede modificarse
//
// La idea de esto es poner el transmisor en TX hasta que termina de enviarse el codigo morse,
// para que el relÃ© no sufra con las continuas conmutaciones
//
// El dpin 13 controlaria la conmutacion del oscilador y el dpin 12 el cambio a TX
//
// La salida de cada uno de estos pines puede atacar la base de un transistor BC550 a traves de una
// resistencia de 1K2 ohmios, de este modo es el transistor el encargado de la conmutaciÃ³n
//
// Se ha configurado el dpin 10 como salida, para controlar la alimentacion del transmisor por el
// Arduino, pudiendo desconectarla si la tension de la bateria desciende a un valor determinado
//
// La telemetria se ha ampliado a dos valores, tomados de los apin 0 y 1 (entradas analogicas 0 y 1).
// para mostrar respectivamente la temperatura de cuarzo del TX El horno del TXCO) y la temperatura
// exterior ambiente, para lo que se usan dos sensores LM335 polarizados desde +5v
// con dos resistencias de 6k8 ohmios. Si no se desea enviar telemetria es preciso
// comentar las respectivas lineas anteponiendo "//" en cada una de ellas.
// 
// Ademas, se mide la tension de la bateria en el apin2 para enviarla como tercer campo de la telemetria
// este valor de tension solo se envia si el dpin 11 pasa a nivel bajo, lo que significaria un fallo de red
// si el dpin 11 esta en HIGH (hay tension de red) en la telemetria se envia "MAIN"
//

#define dht_dpin A3 //variables dht
#define tone2     800
byte bGlobalErr;
byte dht_dat[5];
byte humedad;
byte temperatura;

int adc0;
int adc1;
int adc2;
int temp0;  // guarda el valor en grados C correspomdiente al sensor adc0
int temp1;  // guarda el valor en grados C correspomdiente al sensor adc1
int vbat;  // guarda el valor en voltios medido en el apin 2
int hot=1;  //variable de inicio, solo es 1 al arrancar el Arduino, y espera 30 segundos al
              // calentamiento del cuarzo, luego pasa a valer siempre 0 con lo que ya no se aguardan los
              // 30 segundos de calentamiento, salvo un reset o que se apague o encienda el Arduino
              
int adclen;
byte morse;
byte cwlen;
byte cw;
//int tone2;
int tonepin = 4;
byte x;

int cwoutPin = 13; // CW TX output pin
int ptt = 12; // PTT activa el modo TX para conectar el transmisor
int red = 11;  // variable que determina si hay tension de red (high) y envia MAIN en la telemetria o la vbat
int onoff = 10;  // este dpin controla el encendido o apagado del transmisor

char asciibuf[5];

// al especificar la longitud de las cadenas hay que incluir espacio para el caracter "nulo" de fin de cadena
//  NOTA**** Las cadenas "callsign" y "locator" deben configurarse con el distintivo y ubicaciÃ³n adecuados

char vvv[6] = {'V','V','V',' ',' '};
char callsign[7] = {'C','A','1','C','V','I',' '};
char locator[9] = {' ','F','G','4','6','S','H',' '};
char pwr[5] = {'2','2','0',' '};
char hum[6] = {'H','U','M',':',' '};
char temp[6] = {'T','E','M',':',' '};
char volt[3] = {'V',':',' '};
char tem[3] = {'C',':',' '};
char temb[10] = {'T','E','M','P','B','A','T',':',' '};
char temt[10] = {'T','E','M','P','R','A','D',':',' '};

// ********************************************************
// ASCII to Morse Code Lookup Table
// ********************************************************

const unsigned char morse_table[63] = { 	// Morse Code Lookup table

	0b00000001,	//;sp - 0x20 
	0b01001010,	//; ! - 0x21
	0b01101101,	//; " - 0x22
	0b01011110,	//; # - 0x23 // Not available in Morse Code - replace with "-"
	0b10110111,	//; $ - 0x24
	0b01011110,	//; % - 0x25 // Not available in Morse Code - replace with "-"
	0b00111101,	//; & - 0x26
	0b01100001,	//; ' - 0x27
	0b00110010,	//; ( - 0x28
	0b01010010,	//; ) - 0x29
	0b01011110,	//; * - 0x2A // Not available in Morse Code - replace with "-"
	0b00110101,	//; + - 0x2B 
	0b01001100,     //; , - 0x2C
	0b01011110,     //; - - 0x2D
	0b01010101,     //; . - 0x2E
	0b00110110,	//; / - 0x2F
	0b00100000,	//; 0 - 0x30
	0b00100001,	//; 1 - 0x31
	0b00100011,	//; 2 - 0x32
	0b00100111,	//; 3 - 0x33
	0b00101111,	//; 4 - 0x34
	0b00111111,	//; 5 - 0x35
	0b00111110,	//; 6 - 0x36
	0b00111100,	//; 7 - 0x37
	0b00111000,	//; 8 - 0x38
	0b00110000,	//; 9 - 0x39
	0b01111000,	//; : - 0x3A
	0b00101010,	//; ; - 0x3B
	0b00110010,	//; < - 0x3C // send ( since no < in Morse
	0b00101110,	//; = - 0x3D 
	0b01010010,	//; > - 0x3E // send ) since no > in Morse
	0b01110011,	//; ? - 0x3F
	0b01101001,	//; @ - 0x40 
	0b00000101,	//; A - 0x41
	0b00011110,	//; B - 0x42
	0b00011010,	//; C - 0x43
	0b00001110,	//; D - 0x44
	0b00000011,	//; E - 0x45
	0b00011011,	//; F - 0x46
	0b00001100,	//; G - 0x47
	0b00011111,	//; H - 0x48
	0b00000111,	//; I - 0x49
	0b00010001,	//; J - 0x4A
	0b00001010,	//; K - 0x4B
	0b00011101,	//; L - 0x4C
	0b00000100,	//; M - 0x4D
	0b00000110,	//; N - 0x4E
	0b00001000,	//; O - 0x4F
	0b00011001,	//; P - 0x50
	0b00010100,	//; Q - 0x51
	0b00001101,	//; R - 0x52
	0b00001111,	//; S - 0x53
	0b00000010,	//; T - 0x54
	0b00001011,	//; U - 0x55
	0b00010111,	//; V - 0x56
	0b00001001,	//; W - 0x57
	0b00010110,	//; X - 0x58
	0b00010010,	//; Y - 0x59
	0b00011100	//; Z - 0x5A
	
};

// END of Morse Table

void setup(){

InitDHT();  
Serial.begin(9600);

delay(300);

Serial.println("Humedad y Temperatura");

delay(100);
  

pinMode(cwoutPin, OUTPUT);      // sets the digital pin as output 

pinMode(ptt, OUTPUT);
  
pinMode(red, INPUT);  //determina el dpin 11 como entrada para detectar tension de red
  
pinMode(onoff, OUTPUT);

//tone (cwoutPin,tone2);

}


void loop(){
  
  
  ReadDHT();
//float temperatura; //declaro la variable
  switch (bGlobalErr){

     case 0:
 humedad = dht_dat[0];
temperatura = dht_dat[2];    
 


 Serial.print("Humedad Actual = ");

 Serial.print(humedad, DEC);
 Serial.print(" %  ");

 Serial.print("temperatura = ");
 Serial.print(temperatura, DEC);
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

  delay(800);


 
  
red = digitalRead (11);  // comprueba el valor del indicador de tension de red
   
adc2 = analogRead(2);  // mide el valor analogico en el apin 2
   
vbat = (adc2*0.02); // Obtiene el valor en voltios de la bateria en el pin 2 despues del divisor 1/4
     
  if(hot == 1){
    
      delay(30000);  // Espera 30 segundos para que la PTC caldee el cuarzo. NOTA: en vez de tiempo podria
                     // configurase el programa para que comience la transmision cuando la temperatura del cuarzo
                     // alcance un eterminado valor, por ejemplo 48 o 50 ÂºC
  
      hot = 0;      // cambia la variable init a valor 0, con lo que se saltarÃ¡ el tiempo de caldeo del
                     // cuarzo en los sucesivos bucles, salvo que se produza un reset
  }
  
  if(red==HIGH){      //comprueba que el pin que monitoriza la tension de red este en valor alto (hay tension de red)
  
  digitalWrite(onoff, HIGH);   // activa el rele de alimentacion del transmisor 
  
  baliza();      // ejecuta la transmision de la baliza
 
  }  // fin del bucle if
  
  else {  
  
    if(vbat>=11){   // si no hay tension de red, verifica que la tension de la bateria sea igual o superior a 11 voltios,
                      // mientras el voltaje de la bateria este por encima, envia la baliza
    baliza(); 
    }
    
    else {
    digitalWrite(onoff, LOW);    // si vbat cae por debajo de 11 voltios (o se mantiene por debajo) desconecta la alimentacion
                                 // del transmisor (solo quedaria alimentado el Arduino ejecutando su programa)
                                 // NOTAS***** 
                                 // 1.- En este punto es bueno incluir una funcion "sleeping" en la cual en Arduino
                                 // permanezca dormido y se despierte a intervalos de tiempo para monitorizar el estado de
                                 // la red y el valor de la bateria (esta puede llevar un cargador solar adicional)
                                 // de este modo, la carga sobre la bateria es mÃ­nima cuando su tension cae por debajo
                                 // del valor critico, reduciendo la posibilidad de inutilizarla.
                                 // 2.- Seria conveniente introducir un valor de histeresis de modo que si la vbat desciende 
                                 // al nivel critico, la baliza no se ponga de nuevo en marcha hasta que la bateria tenga
                                 // un nivel de tension normal (haya adquirido suficiente carga).
    
    
    delay (600000);    // si no hay tension de red (MAIN) y la tension de la bateria (vbat) es menor
                      // a 11 voltios espera 10 minutos antes de comenzar de nuevo el bucle
                      // pero la baliza no se envia de nuevo hasta que haya tension de red, o la tension
                      // de la bateria vuelva a subir.
    }                  
                      
  }
  
} // End of Loop

//------------------------------------------------

// ***********************
// Functions
// ***********************

//*********************
// CW output function *
//*********************
void sendcw(int cwchar)
{
  
 morse = morse_table[cwchar-0x20];
  
  while(1){

    if(cwchar == ' '){ // if SPACE character then delay 500 mSec between words
      delay(500);
      return;
    }
  
    if (morse & 0b00000001){ // compare LSB [ 1=Dit  0=Dah ]
       digitalWrite(cwoutPin, HIGH);
      
   
      delay(100); // dit timing - 100 msec  (tiempo del punto, 100 msg)
      digitalWrite(cwoutPin, LOW);
      delay(100);    
    }
    else{     
      digitalWrite(cwoutPin, HIGH);
    //  tone (cwoutPin,tone2);
      delay(300); // dah timing - 300 msec  (tiempo de la raya, 300 msg)
      digitalWrite(cwoutPin, LOW);
      delay(100);       
    }

    morse = morse >> 1; // shift right to see if Dit or Dah

    if(morse == 1){ // if the value is 1 then end of CW character
      delay(200);
      return;
    }
  } // End of Morse while loop
  
} // End of SENDCW routine
// -------------------------------

// -------------------------------
// ********************************
// **Rutina de envio de la baliza**
// ********************************

void baliza()
{
    // Morse Code repeating sequence main loop

  // ***********************
  // Send Callsign
  // ***********************

  digitalWrite(ptt, HIGH);  //Activa la salida PTT y espera 125 msg antes de enviar CW
  tone (tonepin,tone2);
  delay(125);

    { 
    for(x=0;x<5;x++)sendcw(vvv[x]);


    for(x=0;x<6;x++)sendcw(callsign[x]);


    for(x=0;x<7;x++)sendcw(locator[x]);
    
  
    } 
   
  digitalWrite(cwoutPin, LOW);
  digitalWrite(ptt, LOW);  // Desactiva el PTT
  tone (tonepin,LOW);
 
 
  delay(2000);  // Hace una pausa de 2 segundos
 
  // Activa el PTT y transmite un tono CW contÃ­nuo de 7 segundos
   
  digitalWrite(ptt, HIGH);  //Activa la salida PTT y espera 125 msg antes de enviar CW
  tone (tonepin,tone2);
  delay(125);
  
  digitalWrite(cwoutPin, HIGH);
  delay(7000);
  
  digitalWrite(cwoutPin, LOW);
  digitalWrite(ptt, LOW);
  tone (tonepin,LOW);
 
  delay(1000); // Wait 1 second before sending telemetry

  //***************************************************
  // Read the Temperature Sensor and send the value out  
  //***************************************************

  adc0 = analogRead(0);
 
     temp0 = ((5.0 * adc0 * 100.0)/1024.0)-2;
 //  temp0 = ((adc0*0.488)-273); // Obtiene el valor en grados C para la temperatura medida en el cuarzo con el LM335
 
  itoa(temp0, asciibuf, 10);
    
    if (temp0<0 && temp0>=-10){
    adclen = 2;
    }
    
     if (temp0<-10 && temp0>=-100){
    adclen = 3;
    }
    
    if (temp0<10 && temp0>=0){
    adclen = 1;
    }
    if (temp0<100 && temp0>=10){
    adclen = 2;
    }
    if (temp0<1000 && temp0>=100){
    adclen = 3; 
    }


  digitalWrite(ptt, HIGH);  // Activa la salida PTT y espera 125 msg antes de enviar CW
  tone (tonepin,tone2);
  delay(125);
    for(x=0;x<9;x++)sendcw(temb[x]);
    for (cw=0;cw<adclen;cw++){
    sendcw(asciibuf[cw]);
    }
  for(x=0;x<1;x++)sendcw(tem[x]);    // agregamos la C
  Serial.print("TEMP0 ");  
  Serial.print(temp0);
  Serial.println(" C");
  Serial.print("TEMP0 ");
  Serial.print(asciibuf);
  Serial.println(" C");
  Serial.println();
    
  delay(2000);  // pausa 2 segundos entre temperatura cuarzo y temperatura exterior
  


  adc1 = analogRead(1);
  temp1 = ((5.0 * adc1 * 100.0)/1024.0)-2;
 // temp1 = ((adc1*0.488)-273); // Obtiene el valor en grados C para la temperatura exterior medida con el LM335
 
  itoa(temp1, asciibuf, 10);
 
     if (temp1<0 && temp1>=-10){
    adclen = 2;
    }
    
     if (temp1<-10 && temp1>=-100){
    adclen = 3;
    }
 
    if (temp1<10 && temp1>=0){
    adclen = 1;
    }
    if (temp1<100 && temp1>=10){
    adclen = 2;
    }
    if (temp1<1000 && temp1>=100){
    adclen = 3; 
    }

    for(x=0;x<9;x++)sendcw(temt[x]);
    for (cw=0;cw<adclen;cw++){
    sendcw(asciibuf[cw]);
  
    }
    for(x=0;x<1;x++)sendcw(tem[x]);    // agregamos la C
  
  Serial.print("TEMP1 ");  
  Serial.print(temp1);
  Serial.println(" C");
  Serial.print("TEMP1 ");
  Serial.print(asciibuf);
  Serial.println(" C");
  Serial.println();
    
    
  delay(2000);  // pausa 2 segundos entre temperatura exterior e info bateria (voltios) o red (MAIN)  
  
   
    if (red == HIGH) {     //comprueba si el dpin 11 esta en HIGH, lo que indica que hay tension de red
    
      for(x=0;x<4;x++)sendcw(pwr[x]);    // si hay tension de red envia MAIN en la baliza
      
      Serial.print("Bat ");
      Serial.print(vbat);
      Serial.println(" V");
      Serial.println("220 V");
      Serial.println(callsign);
      Serial.println();


    }
  
    else {      // si no hay tensiÃ³n de red envÃ­a en la baliza la tensiÃ³n de la bateria

    adc2 = analogRead(2); 
 
    vbat = (adc2 * 0.02);
 
    itoa(vbat, asciibuf, 10);
 
      if (vbat<10){
      adclen = 1;
      }
      if (vbat<100 && vbat>=10){
      adclen = 2;
      }


      for (cw=0;cw<adclen;cw++){
      sendcw(asciibuf[cw]); 
    //  for(x=0;x<1;x++)sendcw(volt[x]);  
      }
      
        
    Serial.print("Bat ");
    Serial.print(vbat);
    Serial.println(" V");
    Serial.print(vbat);
    Serial.println(" V");
    Serial.println(callsign);

    }
   
   for(x=0;x<1;x++)sendcw(volt[x]);
      delay (1000);
        itoa(humedad, asciibuf, 10);
        for(x=0;x<4;x++)sendcw(hum[x]);
        for (cw=0;cw<2;cw++)sendcw(asciibuf[cw]);
        delay (1000);
        itoa(temperatura, asciibuf, 10);
        for(x=0;x<4;x++)sendcw(temp[x]);
        for (cw=0;cw<2;cw++)sendcw(asciibuf[cw]); 
    
  Serial.println("Fin de secuencia");
  Serial.println();

  digitalWrite(cwoutPin, LOW);
  digitalWrite(ptt, LOW);  // Desactiva el PTT
  tone (tonepin,LOW);
  
  delay(2000);  // Hace una pausa de 2 segundos
 
  // Activa el PTT y transmite un tono CW contÃ­nuo de 13 segundos
   
  digitalWrite(ptt, HIGH);  //Activa la salida PTT y espera 125 msg antes de enviar CW
  tone (tonepin,tone2);
  delay(125);
  
  digitalWrite(cwoutPin, HIGH);
  delay(13000);
  
  digitalWrite(cwoutPin, LOW);
  digitalWrite(ptt, LOW);
  tone (tonepin,LOW);
  

  
  delay(3000); // pausa de 5 segundos despues de cada transmision
}

// fin del envio de la baliza

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
//float humedad = dht_dat[0];  //invento mio para meter valor a variable
//  float temperatura = dht_dat[2];// lo mismo
}
  
  //HASTA ACA PARA LEER EL DHT.

