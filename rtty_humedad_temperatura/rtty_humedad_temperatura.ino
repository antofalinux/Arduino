///////////////////////////////////////////////////
//    CREATE BY CA1CVI http://www.antofalinux.cl
//    BASED ON THE WORK OF JI3BNB
//    45.45 baud BAUDOT TELEMETRY BEACON 1.5
//    http://k183.bake-neko.net/ji3bnb/page13.html
//    DESIGNED FOR AMATEUR RADIO COMMUNICATION
//    THIS PROGRAM IS IN THE PUBLIC DOMAIN
///////////////////////////////////////////////////

#include <stdio.h>

#define AFSK_OUT 12   //---- AFSK AUDIO OUTPUT
#define FSK_OUT  13   //---- TTL LEVEL OUTPUT
#define MARK     2295
#define SPACE    2125
#define dht_dpin A3
#define led1 10
#define PTT 11


byte temperatura;
byte humedad;


const char ID[] = "CE1RLP ESTACION ORION DE CA1CVI CA1CVI CA1CVI /B ";

boolean d1;
boolean d2;
boolean d3;
boolean d4;
boolean d5;
boolean sSq;
boolean sRd = 1;
boolean space;
boolean fig1;
boolean fig2;
byte    i;
byte    j;
byte    idC;
char    ch;
char    sVal[15];
byte bGlobalErr;
byte dht_dat[5];


void setup()
{
        InitDHT();
        pinMode(FSK_OUT,  OUTPUT);
        pinMode(AFSK_OUT, OUTPUT);
        pinMode(led1, OUTPUT); 
        pinMode(PTT, OUTPUT); 
        digitalWrite(FSK_OUT, HIGH);
        tone(AFSK_OUT, MARK);
        Serial.begin(9600);
        delay(300);
        Serial.println("Humedad y Temperatura");
        delay(700);
     //   delay(2000); //esto es para dar tiempo al controlador
}

void sendFsk()
{
        //--start bit
        digitalWrite(FSK_OUT, LOW);
        tone(AFSK_OUT, SPACE);
        delay(22);
        //--bit1
        if(d1 == 1){
                digitalWrite(FSK_OUT, HIGH);
                tone(AFSK_OUT, MARK);
        }
        else{
                digitalWrite(FSK_OUT, LOW);
                tone(AFSK_OUT, SPACE);
        }
        delay(22);
        //--bit2
        if(d2 == 1){
                digitalWrite(FSK_OUT, HIGH);
                tone(AFSK_OUT, MARK);
        }
        else{
                digitalWrite(FSK_OUT, LOW);
                tone(AFSK_OUT, SPACE);
        }
        delay(22);
        //--bit3
        if(d3 == 1){
                digitalWrite(FSK_OUT, HIGH);
                tone(AFSK_OUT, MARK);
        }
        else{
                digitalWrite(FSK_OUT, LOW);
                tone(AFSK_OUT, SPACE);
        }
        delay(22);
        //--bit4
        if(d4 == 1){
                digitalWrite(FSK_OUT, HIGH);
                tone(AFSK_OUT, MARK);
        }
        else{
                digitalWrite(FSK_OUT, LOW);
                tone(AFSK_OUT, SPACE);
        }
        delay(22);
        //--bit5
        if(d5 == 1){
                digitalWrite(FSK_OUT, HIGH);
                tone(AFSK_OUT, MARK);
        }
        else{
                digitalWrite(FSK_OUT, LOW);
                tone(AFSK_OUT, SPACE);
        }
        delay(22);
        //--stop bit
        digitalWrite(FSK_OUT, HIGH);
        tone(AFSK_OUT, MARK);
        delay(33);
}

void chTable()
{
        if(ch == ' ')
        {
                d1 = 0; d2 = 0; d3 = 1; d4 = 0; d5 = 0;
        }
        else if(ch == 'A'){d1 = 1; d2 = 1; d3 = 0; d4 = 0; d5 = 0; fig2 = 0;}
        else if(ch == 'B'){d1 = 1; d2 = 0; d3 = 0; d4 = 1; d5 = 1; fig2 = 0;}
        else if(ch == 'C'){d1 = 0; d2 = 1; d3 = 1; d4 = 1; d5 = 0; fig2 = 0;}
        else if(ch == 'D'){d1 = 1; d2 = 0; d3 = 0; d4 = 1; d5 = 0; fig2 = 0;}
        else if(ch == 'E'){d1 = 1; d2 = 0; d3 = 0; d4 = 0; d5 = 0; fig2 = 0;}
        else if(ch == 'F'){d1 = 1; d2 = 0; d3 = 1; d4 = 1; d5 = 0; fig2 = 0;}
        else if(ch == 'G'){d1 = 0; d2 = 1; d3 = 0; d4 = 1; d5 = 1; fig2 = 0;}
        else if(ch == 'H'){d1 = 0; d2 = 0; d3 = 1; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == 'I'){d1 = 0; d2 = 1; d3 = 1; d4 = 0; d5 = 0; fig2 = 0;}
        else if(ch == 'J'){d1 = 1; d2 = 1; d3 = 0; d4 = 1; d5 = 0; fig2 = 0;}
        else if(ch == 'K'){d1 = 1; d2 = 1; d3 = 1; d4 = 1; d5 = 0; fig2 = 0;}
        else if(ch == 'L'){d1 = 0; d2 = 1; d3 = 0; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == 'M'){d1 = 0; d2 = 0; d3 = 1; d4 = 1; d5 = 1; fig2 = 0;}
        else if(ch == 'N'){d1 = 0; d2 = 0; d3 = 1; d4 = 1; d5 = 0; fig2 = 0;}
        else if(ch == 'O'){d1 = 0; d2 = 0; d3 = 0; d4 = 1; d5 = 1; fig2 = 0;}
        else if(ch == 'P'){d1 = 0; d2 = 1; d3 = 1; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == 'Q'){d1 = 1; d2 = 1; d3 = 1; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == 'R'){d1 = 0; d2 = 1; d3 = 0; d4 = 1; d5 = 0; fig2 = 0;}
        else if(ch == 'S'){d1 = 1; d2 = 0; d3 = 1; d4 = 0; d5 = 0; fig2 = 0;}
        else if(ch == 'T'){d1 = 0; d2 = 0; d3 = 0; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == 'U'){d1 = 1; d2 = 1; d3 = 1; d4 = 0; d5 = 0; fig2 = 0;}
        else if(ch == 'V'){d1 = 0; d2 = 1; d3 = 1; d4 = 1; d5 = 1; fig2 = 0;}
        else if(ch == 'W'){d1 = 1; d2 = 1; d3 = 0; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == 'X'){d1 = 1; d2 = 0; d3 = 1; d4 = 1; d5 = 1; fig2 = 0;}
        else if(ch == 'Y'){d1 = 1; d2 = 0; d3 = 1; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == 'Z'){d1 = 1; d2 = 0; d3 = 0; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == '0'){d1 = 0; d2 = 1; d3 = 1; d4 = 0; d5 = 1; fig2 = 1;}
        else if(ch == '1'){d1 = 1; d2 = 1; d3 = 1; d4 = 0; d5 = 1; fig2 = 1;}
        else if(ch == '2'){d1 = 1; d2 = 1; d3 = 0; d4 = 0; d5 = 1; fig2 = 1;}
        else if(ch == '3'){d1 = 1; d2 = 0; d3 = 0; d4 = 0; d5 = 0; fig2 = 1;}
        else if(ch == '4'){d1 = 0; d2 = 1; d3 = 0; d4 = 1; d5 = 0; fig2 = 1;}
        else if(ch == '5'){d1 = 0; d2 = 0; d3 = 0; d4 = 0; d5 = 1; fig2 = 1;}
        else if(ch == '6'){d1 = 1; d2 = 0; d3 = 1; d4 = 0; d5 = 1; fig2 = 1;}
        else if(ch == '7'){d1 = 1; d2 = 1; d3 = 1; d4 = 0; d5 = 0; fig2 = 1;}
        else if(ch == '8'){d1 = 0; d2 = 1; d3 = 1; d4 = 0; d5 = 0; fig2 = 1;}
        else if(ch == '9'){d1 = 0; d2 = 0; d3 = 0; d4 = 1; d5 = 1; fig2 = 1;}
        else if(ch == '-'){d1 = 1; d2 = 1; d3 = 0; d4 = 0; d5 = 0; fig2 = 1;}
        else if(ch == '?'){d1 = 1; d2 = 0; d3 = 0; d4 = 1; d5 = 1; fig2 = 1;}
        else if(ch == ':'){d1 = 0; d2 = 1; d3 = 1; d4 = 1; d5 = 0; fig2 = 1;}
        else if(ch == '('){d1 = 1; d2 = 1; d3 = 1; d4 = 1; d5 = 0; fig2 = 1;}
        else if(ch == ')'){d1 = 0; d2 = 1; d3 = 0; d4 = 0; d5 = 1; fig2 = 1;}
        else if(ch == '.'){d1 = 0; d2 = 0; d3 = 1; d4 = 1; d5 = 1; fig2 = 1;}
        else if(ch == ','){d1 = 0; d2 = 0; d3 = 1; d4 = 1; d5 = 0; fig2 = 1;}
        else if(ch == '/'){d1 = 1; d2 = 0; d3 = 1; d4 = 1; d5 = 1; fig2 = 1;}
        else if(ch == '+'){d1 = 1; d2 = 0; d3 = 0; d4 = 0; d5 = 1; fig2 = 1;} //ITA2
        else if(ch == '\0')
        {
                /////
        }
        else
        {
                ch = ' ';
                d1 = 0; d2 = 0; d3 = 1; d4 = 0; d5 = 0;
        } 
}

void loop()
{
        //SEND SENSOR VALUES
        ReadDHT();
       
        if(sSq == 0)
        {
                if( sRd == 1)
                {
                        if(i == 0)
                        {
                                    digitalWrite(led1, HIGH); //LED DEL PTT 
                                    digitalWrite(PTT, HIGH); // ACTIVAR PTT 
                                    
                                  
                                    humedad = dht_dat[0];
                                    temperatura = dht_dat[2];
                    
                                sprintf(sVal, "HUMEDAD: %02d", humedad, 0);
                             //   sprintf(sVal, "HUMEDAD: ", dht_dat[0], DEC);
                                 Serial.println (sVal);
                                 
                            
                        }
                        if(i == 1)
                        {
                                     
                               sprintf(sVal, "HUMEDAD: %02d", humedad, DEC);
                             //   sprintf(sVal, "HUMEDAD: ", dht_dat[0], DEC);
                             //    Serial.println (sVal);
                        //        sprintf(sVal, "TEMPERATURA:" temperatura, 0);
                               
                                dht_dat[0]='0';
                              
                        }
                        if(i == 2)
                        {
                                     
                            //    sprintf(sVal,"TEMPERATURA: %02d",  dht_dat[2], 0);
                                
                                sprintf(sVal, "TEMPERATURA: %02d", temperatura,0);
                                Serial.println (sVal);
                                dht_dat[2]='0';
                           
                        }
                        sRd = 0;
                }

                ch = sVal[j];
             
                if(ch != '\0')
                {
                        chTable();
                        if(fig1 == 0 && fig2 == 1)
                        {
                                d1 = 1; d2 = 1; d3 = 0; d4 = 1; d5 = 1; //FIGURES
                        }
                        else if(fig1 == 1 && fig2 == 0)
                        {
                                d1 = 1; d2 = 1; d3 = 1; d4 = 1; d5 = 1; //LETTERS
                        }
                        else if(space == 1 && fig2 == 1)
                        {
                                d1 = 1; d2 = 1; d3 = 0; d4 = 1; d5 = 1; //FIGURES 
                        }
                        else
                        {
                                j++;
                        }
                        if(fig2 == 0 || fig2 == 1)
                        {
                                space = 0;
                                fig1 = fig2;
                        }
                        sendFsk();
                }
                if(ch == '\0')
                {
                        d1 = 0; d2 = 0; d3 = 1; d4 = 0; d5 = 0; //SPACE
                        space = 1;
                        sendFsk();
                        i++;
                        if(i == 4) //OVERFLOW ERA 4
                        {
                                i = 0;
                                sSq = 1;
                        }
                        j = 0;
                        sRd = 1;
                }
        }
        //SEND ID
        if(sSq == 1)
        {
                if(idC < 3) //se modifica valor de 9 a 2
                {
                        d1 = 0; d2 = 0; d3 = 0; d4 = 1; d5 = 0; //CR
                        sendFsk();
                        d1 = 0; d2 = 1; d3 = 0; d4 = 0; d5 = 0; //LF
                        sendFsk();
                        sSq = 0;
                        j = 0;
                        delay(700);
                        idC++;
                }
                if(idC == 3) //este es el contador que hay que modificar para el numero de veces
                {
                        ch = ID[j];
                        if(ch != '\0')
                        {
                                chTable();
                                if(fig1 == 0 && fig2 == 1)
                                {
                                        d1 = 1; d2 = 1; d3 = 0; d4 = 1; d5 = 1; //FIGURES
                                }
                                else if(fig1 == 1 && fig2 == 0)
                                {
                                        d1 = 1; d2 = 1; d3 = 1; d4 = 1; d5 = 1; //LETTERS
                                }
                                else if(space == 1 && fig2 == 1)
                                {
                                        d1 = 1; d2 = 1; d3 = 0; d4 = 1; d5 = 1; //FIGURES 
                                }
                                else
                                {
                                        j++;
                                }
                                if(fig2 == 0 || fig2 == 1)
                                {
                                        space = 0;
                                        fig1 = fig2;
                                }
                                sendFsk();
                        }
                        if(ch == '\0')
                        {
                                d1 = 0; d2 = 0; d3 = 0; d4 = 1; d5 = 0; //CR
                                sendFsk();
                                d1 = 0; d2 = 1; d3 = 0; d4 = 0; d5 = 0; //LF
                                sendFsk();
                                sSq = 0;
                                j = 0;
                                delay(700);
                                idC = 0;
                        }
                }
        }
        digitalWrite(led1, LOW); //LED DEL PTT
        digitalWrite(PTT, LOW); //ACTIVAR PTT
        delay(5);//ERA 5
        
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

}

