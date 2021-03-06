//**************************************************
///////////////////////////////////////////////////
//    MODIFICATE BY CA1CVI http://www.antofalinux.cl
//    DESIGNED FOR AMATEUR RADIO COMMUNICATION
//    THIS PROGRAM IS UNDER BEERWARE LICENSE
//
// date: February 04, 2015 
// license: Beerware. Use, reuse, and modify this code however you see fit.
// If you find it useful, buy me a beer some day!
// Utilice, reutilize y modifica el código, sin embargo le parezca.
// Si le resulta útil, cómpreme una cerveza algún día!
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
//
// Adaptado y ampliado por EB1HBK y EB1WM, entre Mayo y Junio de 2011, para realizar la baliza
// experimental en 70 MHz "Delcon 70x70" de www.cacharreo.es
//
// << -- Keyed CW mode -- >>
//**************************************************

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
// para que el rele no sufra con las continuas conmutaciones
//
// El dpin 13 controlaria la conmutacion del oscilador y el dpin 12 el cambio a TX
//
// La salida de cada uno de estos pines puede atacar la base de un transistor BC550 a traves de una
// resistencia de 1K2 ohmios, de este modo es el transistor el encargado de la conmutacion
//
// Se ha configurado el dpin 10 como salida, para controlar la alimentacion del transmisor por el
// Arduino, pudiendo desconectarla si la tension de la bateria desciende a un valor determinado
//
// Ademas, se mide la tension de la bateria en el apin2 para enviarla como campo de la telemetria
// este valor de tension solo se envia si el dpin 11 pasa a nivel bajo, lo que significaria un fallo de red
// si el dpin 11 esta en HIGH (hay tension de red) en la telemetria no se envia.
// Se utiliza un tone en el pin 4 para generar un tono de 700 Hz que se puede modificar, de esta manera
// se puede utilizar la linea de fonia hacia el link para enviar la telemetria, vieron que soy un genio!!!


#define tone2     700
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
char callsign[12] = {'R','L','P',' ','T','A','L','T','A','L',' '};
char locator[9] = {' ','F','G','4','5','V','J',' '};
char pwr[4] = {'O','N',' '};
char volt[4] = {'V',':',' '};


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

 
Serial.begin(9600);

delay(300);

Serial.println("Telemetria RPT Taltal");

delay(100);
  

pinMode(cwoutPin, OUTPUT);      // sets the digital pin as output 

pinMode(ptt, OUTPUT);
  
pinMode(red, INPUT);  //determina el dpin 11 como entrada para detectar tension de red
  
pinMode(onoff, OUTPUT);

//tone (cwoutPin,tone2);

}


void loop(){
   
  
red = digitalRead (11);  // comprueba el valor del indicador de tension de red
   
adc2 = analogRead(2);  // mide el valor analogico en el apin 2
   
vbat = (adc2*0.02); // Obtiene el valor en voltios de la bateria en el pin 2 despues del divisor 1/4
     
  if(hot == 1){
    
      Serial.println("Calentando Cuarzo 30 Seg."); 
      delay(30000);  // Espera 30 segundos para que la PTC caldee el cuarzo. NOTA: en vez de tiempo podria
                     // configurase el programa para que comience la transmision cuando la temperatura del cuarzo
                     // alcance un eterminado valor, por ejemplo 48 o 50 ÂºC
                    
      hot = 0;      // cambia la variable init a valor 0, con lo que se saltarÃ¡ el tiempo de caldeo del
                     // cuarzo en los sucesivos bucles, salvo que se produza un reset
  }
  
  if(red==HIGH){      //comprueba que el pin que monitoriza la tension de red este en valor alto (hay tension de red)
  Serial.println("ENERGIZADO");
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
    
    Serial.println("DURMIENDO POR 6 MIN");
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
  Serial.println("Se Activa PTT");
    { 
    Serial.println("Enviando VVV");
    for(x=0;x<5;x++)sendcw(vvv[x]);
    Serial.println("VVV ENVIADO");
    
    Serial.println("Enviando CallSing");
    for(x=0;x<11;x++)sendcw(callsign[x]);
    Serial.println("CALLSING ENVIADO");
    
    Serial.println("Enviando Locator");
    for(x=0;x<8;x++)sendcw(locator[x]);
    Serial.println("Locator ENVIADO");
    Serial.println(" ");
 
    } 
   
  digitalWrite(cwoutPin, LOW);
  digitalWrite(ptt, LOW);  // Desactiva el PTT
  Serial.println("Desactivo PTT");
  tone (tonepin,LOW);
  Serial.println("Desactivo Tono");
 
  Serial.println("ESPERAMOS 2 SEG.");
  delay(2000);  // Hace una pausa de 2 segundos
 
  // Activa el PTT y transmite un tono CW contÃ­nuo de 7 segundos
  
  Serial.println("Se Activa PTT"); 
  digitalWrite(ptt, HIGH);  //Activa la salida PTT y espera 125 msg antes de enviar CW
  Serial.println("Activo Tono");
  tone (tonepin,tone2);
  delay(125);
  
  Serial.println("ENVIAMOS PULSO POR 5 SEG.");
  digitalWrite(cwoutPin, HIGH);
  delay(5000);
  
  Serial.println(" ");
  Serial.println("Desactivo PULSO");
  digitalWrite(cwoutPin, LOW);
  Serial.println("Desactivo PTT");
  digitalWrite(ptt, LOW);
  Serial.println("Desactivo TONO");
  tone (tonepin,LOW);
 
  delay(1000); // Wait 1 second before sending telemetry

  //***************************************************
  // Read the Temperature Sensor and send the value out  
  //***************************************************
  
 // delay(2000);  // pausa 2 segundos entre temperatura exterior e info bateria (voltios) o red (MAIN)  
  
   
    if (red == HIGH) {     //comprueba si el dpin 11 esta en HIGH, lo que indica que hay tension de red
    Serial.println("ENERGIZADO");
    
      for(x=0;x<3;x++)sendcw(pwr[x]);    // si hay tension de red envia MAIN en la baliza
      
      Serial.print("Bat ");
      Serial.print(vbat);
      Serial.println(" V");
      Serial.println("220 V");
      Serial.println(callsign);
      Serial.println();


    }
  
    else {      // si no hay tensiÃ³n de red envÃ­a en la baliza la tensiÃ³n de la bateria

    adc2 = analogRead(2); 
   Serial.println("DESENERGIZADO");
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
  delay(5000);
  
  digitalWrite(cwoutPin, LOW);
  digitalWrite(ptt, LOW);
  tone (tonepin,LOW);
  

  
  delay(3000); // pausa de 5 segundos despues de cada transmision
  
}

// fin del envio de la baliza

