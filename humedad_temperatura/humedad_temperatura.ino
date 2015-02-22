#define dht_dpin A3

byte bGlobalErr;

byte dht_dat[5];

float humedad;  //invento mio para meter valor a variable
  float temperatura; 
  float temperatura1; 

void setup(){

InitDHT();

Serial.begin(9600);

delay(300);

Serial.println("Humedad y Temperatura");

delay(700);

}

 

void loop(){

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

  delay(800);

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


