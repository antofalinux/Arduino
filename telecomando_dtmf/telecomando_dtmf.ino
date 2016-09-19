#include <EEPROM.h> //needed to save settings in EEPROM

// DTMF variabili globali *******************************************************
int intPIN = 1;                 //interrupt 1 ---> pin digitale 3
char keyDTMF[] = {'D', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#', 'A', 'B', 'C' };
char charDTMF_value = 0;        // valore letto quando si verifica l'interrupt
boolean charDTMF_bool = false;  // indica che è stato decodificato (se true) un carattere
unsigned long r1;               // counter utilizzato per azzerare la stringa DTMF dopo un intervallo stabilito se non si è concluso il comando
boolean passBool;               // indica che è stata riconosciuta la password e la fine della stringa comando che deve finire con "**" (2 asterischi)
String char_DTMF_buffer;        // stringa BUFFER dove vengono osizionati i caratteri decodificati ....
const int bufferSize = 25;      // dimensione del buffer su cui vengono inviati i caratteri decodificati (da dimensionanrsi in funzione del numero max di comandi che si intende inviare|ricevere
String passKey = "0000";         // password (una qualsiasi combinazione di numeri e/o ABCD# (.. non usare * - asterischi)
const byte dimComando = 4;      // numero massimo di comandi inviabili nella stringa 
byte indirizzo [dimComando+1], azione [dimComando+1]; // generico comando suddiviso in indirizzo ed azIONE
boolean comandoOK [dimComando+1]; // true se la coppia indirizzo ed azione è valida, altrimenti false

byte indiceComando = 0;
boolean comando_bool= false;    // indica la presenza di almeno un comando regolarmente decodificato

#define debug_bool true        // attiva la stampa su serial monitor per il debug



int comando_1 = 8;
int comando_2 = 9;
int comando_3 = 10;
int comando_4 = 12;  
int comando_5 = 2;  //non usabili
int comando_6 = 1;
int comando_tono = 11;  //PWM
int comando_ptt = 13;

byte azione1, azione2, azione3; // usate per controllare le azioni sui 16 PIN di comando dello shift register
byte bitStart = 10; // bit della eeprom da cui iniaziare a memorizzare lo stato di funzionamento (azione1, azione2 e azione 3)

void(* Riavvia)(void) = 0;

void setup ()
{
  pinMode(comando_1,OUTPUT);
  digitalWrite(comando_1,LOW);
  pinMode(comando_2,OUTPUT);
  digitalWrite(comando_2,LOW);
  pinMode(comando_3,OUTPUT);
  digitalWrite(comando_3,LOW);
  pinMode(comando_4,OUTPUT);
  digitalWrite(comando_4,LOW);
  pinMode(comando_5,OUTPUT);
  digitalWrite(comando_5,LOW);
  pinMode(comando_6,OUTPUT);
  digitalWrite(comando_6,LOW);
  pinMode(comando_tono,OUTPUT);
  digitalWrite(comando_tono,LOW);
  pinMode(comando_ptt,OUTPUT);
  digitalWrite(comando_ptt,LOW);
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);
  pinMode(A3, OUTPUT);
  digitalWrite(A3, LOW);
  pinMode(A4, OUTPUT);
  digitalWrite(A4, LOW);
  pinMode(A5, OUTPUT);
  digitalWrite(A5, LOW);
  
   #if(debug_bool) // DEBUG *********************************
Serial.begin(4800);
 #endif
 
 //DDRC = B00111000; // imposta i PIN della PORT C: A0, A1, A2 INPUT, A3, A4, A5 OUTPUT, A6 e A7 non sono disponibili...

 DDRD = B00000000; // imposta i PIN della PORT D in lettura --- > PD0 - PD7  ....... ARDUINO           PD3            PD4          PD5           PD6          PD7
                                                                                    //MT8870       PIN 15(STD)     PIN 11(Q1)  PIN 12(Q2)    PIN 13(Q3)    PIN 14(Q4)
 attachInterrupt(intPIN, leggiCarattereDTMF, RISING);

 //leggiEeprom();
 //esegui_azione (azione1, azione2, azione3);



}

void loop ()
{
  if (charDTMF_bool) {rilevaStringaDTMF();}

  if (comando_bool) 
    {  
      for( int i = 1; i <= indiceComando; i++)
      {
        if (comandoOK[i]==true)
      
          { digitalWrite(comando_ptt,HIGH);
    delay(200);
      digitalWrite(comando_tono,HIGH); 
delay(100); 
digitalWrite(comando_tono,LOW);
delay(200);
digitalWrite(comando_ptt,LOW);
            Serial.print("COMANDO OK!");
          if (indirizzo[i] >= 0  && indirizzo[i] <= 7 ) { bitWrite (azione1, indirizzo[i]   ,azione[i]); }
           if (indirizzo[i] >= 8  && indirizzo[i] <= 12) { bitWrite (azione2, indirizzo[i]- 8,azione[i]); }
           //if (indirizzo[i] >= 16 && indirizzo[i] <= 23) { bitWrite (azione3, indirizzo[i]-16,azione[i]); }
         }
         
         
      
      
      }
      
      

      comando_bool= false;  
      //scriviEeprom(azione1, azione2, azione3);
     // esegui_azione (azione1, azione2, azione3);
   }
   
   
   
}
      


/*
void leggiEeprom()  // legge l'ultimo stato di funzionamento registrato ..
{
   azione1 = EEPROM.read(bitStart+1); // legge i valori memorizzati per azione1
   azione2 = EEPROM.read(bitStart+2); // legge i valori memorizzati per azione2
   azione3 = EEPROM.read(bitStart+3); // legge i valori memorizzati per azione3
}*/

 /*
 void scriviEeprom(byte az_1, byte az_2, byte az_3)  // memorizza l'ultimo stato di funzionamento eseguito ..
{
   EEPROM.write (bitStart+1 , az_1);   // scrive i valori memorizzati per azione1
   EEPROM.write (bitStart+2 , az_2);   // scrive i valori memorizzati per azione2
   EEPROM.write (bitStart+3 , az_3);   // scrive i valori memorizzati per azione3
}*/

 void scriviPassw(String  passw)  // memorizza l'ultimo stato di funzionamento eseguito ..
{
 
}

 void leggiPassw(String  passw)  // memorizza l'ultimo stato di funzionamento eseguito ..
{
 
}



void rilevaStringaDTMF ()
{  
 comando_bool= false;  //se entra in questa funzione significa che sta ricevendo un carattere dtmf, quindi sta costruendo la stringa... bool è falso fino alla decofica della stringa
 if ( millis()- r1 > (7000) ) { char_DTMF_buffer = "" ;} //azzera la stringa DTMF gia ricevuta se passano più di 7 sec dall'ultima digitazione
 r1 = millis();  // counter utilizzato per azzerare la stringa DTMF dopo un intervallo stabilito se non si è concluso il comando

 // aggiunge il carattere letto al buffer e dopo  pone charDTMF_bool = false;
 if (char_DTMF_buffer.length() <= bufferSize) {
 char_DTMF_buffer = char_DTMF_buffer + keyDTMF[charDTMF_value]; 
 charDTMF_bool = false;
 }

      #if(debug_bool) // DEBUG *********************************
      Serial.print("\n"); Serial.print(char_DTMF_buffer);
      #endif    
   
      // chiude la costruzione della stringa DTMF se ultimata con due ** o se raggiunge la lung. massima stabilita
      if ((char_DTMF_buffer.substring(char_DTMF_buffer.length()-2, char_DTMF_buffer.length()) == "**") || (char_DTMF_buffer.length() == bufferSize))
         {
          
          // cerca la password nei primi passKey.length() caratteri
           passBool = (char_DTMF_buffer.substring(0, passKey.length()) == passKey); 
 
           if (passBool)
              { 
               #if(debug_bool) // DEBUG *********************************
               Serial.print("\n"); Serial.print(" passw Trovata!!!");
               #endif    

                // stringa DTMF depurata da password e ultimi due **
                String comandi=""; 
                comandi = char_DTMF_buffer.substring(passKey.length(), char_DTMF_buffer.length()-2);  // estrae la sub string contenente i comandi (elimina la password e gli ultimi 2 **

                #if(debug_bool) // DEBUG *********************************
                Serial.print("\n"); Serial.print(comandi);
                #endif    

                int i =0;
                indiceComando = 0; 
                String comando; // conterrà i comandi e le azioni associate  
                while (i <= comandi.length()) // scansiona il buffer fintanto che non è arrivato alla fine 
                 { 
                   if ( comandi.charAt(i) == '*') // incrementa il contatore dei comandi se trova un asterisco ... quindi legge i comandi
                      { estraiComandi(indiceComando, comando); // estrae i comandi in Indirizzo ed Azione in decimale
                        comando ="";
                        indiceComando++; i++; // incrementa il contatore e 'fa sparire' gli *
                      }  
                   if ( i >= comandi.length()) // legge i comandi se arriva a fine buffer
                      { estraiComandi(indiceComando, comando); // estrae i comandi in Indirizzo ed Azione in decimale
                        comando = "";
                      }  
                    if (indiceComando > dimComando) { 
                    indiceComando = dimComando; 
                  break;
                } // esce se raggiunge in num max di comandi inviabili nella stessa stringa
                   comando = comando + comandi.charAt(i); // isola il singolo comando nel buffer che dovrà avere il formato *xx#x
                   i++;
                 }  
              
            #if(debug_bool) // DEBUG *********************************
            for( int i = 1; i <= indiceComando; i++){
            Serial.print("\n  ");
          Serial.print(indirizzo[i]); 
        Serial.print("  "); 
      Serial.print(azione[i]); 
    Serial.print("  "); 
  Serial.print(comandoOK[i]);
            }
            #endif    
             
             }
                  
           #if(debug_bool) // DEBUG ********************************* 
           else { 
             Serial.print("\n"); 
             Serial.print(" passw NON Trovata!!!");
          digitalWrite(comando_tono,HIGH); 
          delay(1000); 
          digitalWrite(comando_tono,LOW); 
         }
           #endif    
                 
        char_DTMF_buffer = "" ; // azzera il buffer
        }
}



void estraiComandi(int i, String str )
{     
  Serial.print("\n"); 
      Serial.print(str);
      String str_I, str_A;
      boolean bool_1, bool_2 ;
      
      str_I = str.substring(0, str.indexOf("#")); 
      char Chr_I[str_I.length()+1]; 
      str_I.toCharArray(Chr_I, str_I.length()+1) ; 
      indirizzo[i] = atoi(Chr_I);
      str_A = str.substring(str.indexOf("#")+1);  
      char Chr_A[str_A.length()+1]; 
      str_A.toCharArray(Chr_A, str_A.length()+1) ;    
      azione[i] = atoi(Chr_A);

      bool_1 = (indirizzo[i] >= 0 &&  indirizzo[i] <= 13) && (azione[i] == 0 || azione[i] == 1 || azione[i] == 3); // verifica che indirizzo ed azione siano compresi tra i valori validi
      bool_2 = ((str.indexOf("#") == 1 && str.length() > 2) || (str.indexOf("#") == 2 && str.length() > 3)); // verifica che # sia posizionato bene nella stringa 

   
      if (bool_1 && bool_2) {
      comando_bool = true;  
      
    comandoOK [i] = true; 
    
}

else {
  
comandoOK [i] = false;
//Serial.print("false");

} // se non sono verificate le condizoini di cui sopra il comando non viene accettato

/*int k=0;
char j[4];
str_I.toCharArray(j, 5);
for(k=0; k<1; k++) {
    Serial.println(j[k]);
    int a = int(j[k]);
    if( (a>57 && a<65) || a>68) {
       Serial.println("comando sbagliato");
       digitalWrite(comando_tono,HIGH); 
delay(1000); 
digitalWrite(comando_tono,LOW);
      }
}
 */
       
       //pippo(str_I, str_A);            
       if (str_I=="0") {
         passKey = str_A;
       }
       if (str_I=="13" && str_A=="0" ) {
         
         Riavvia();
       }
         
         
         
      if (str_I=="1" && str_A=="1") {
        digitalWrite(comando_1,HIGH);
        }
      
     if (str_I=="1" && str_A=="0") {
        digitalWrite(comando_1, LOW);
      }
      
      if (str_I=="1" && str_A=="3") {
        if(digitalRead(comando_1)==HIGH) {
          digitalWrite(comando_tono,HIGH); 
          delay(100); 
          digitalWrite(comando_tono,LOW);
        }
        if(digitalRead(comando_1)==LOW) {
          digitalWrite(comando_tono,HIGH); 
          delay(1000); 
          digitalWrite(comando_tono,LOW);
        }
        
          
      }
      
      if (str_I=="2" && str_A=="1") {
        digitalWrite(comando_2,HIGH);
      }
      
     if (str_I=="2" && str_A=="0") {
        digitalWrite(comando_2, LOW);
      }
      
      if (str_I=="2" && str_A=="3") {
        if(digitalRead(comando_2)==HIGH) {
          digitalWrite(comando_tono,HIGH); 
          delay(100); 
          digitalWrite(comando_tono,LOW);
        }
        if(digitalRead(comando_2)==LOW) {
          digitalWrite(comando_tono,HIGH); 
          delay(1000); 
          digitalWrite(comando_tono,LOW);
        }
        
          
      }
      
      if (str_I=="3" && str_A=="1") {
        digitalWrite(comando_3,HIGH);
      }
      
     if (str_I=="3" && str_A=="0") {
        digitalWrite(comando_3, LOW);
      }
      
      if (str_I=="3" && str_A=="3") {
        if(digitalRead(comando_3)==HIGH) {
          digitalWrite(comando_tono,HIGH); 
          delay(100); 
          digitalWrite(comando_tono,LOW);
        }
        if(digitalRead(comando_3)==LOW) {
          digitalWrite(comando_tono,HIGH); 
          delay(1000); 
          digitalWrite(comando_tono,LOW);
        }
        
          
      }    
      
      
     if (str_I=="4" && str_A=="1") {
        digitalWrite(comando_4,HIGH);
      }
      
      if (str_I=="4" && str_A=="0") {
        digitalWrite(comando_4, LOW);
      }
      
      if (str_I=="4" && str_A=="3") {
        if(digitalRead(comando_4)==HIGH) {
          digitalWrite(comando_tono,HIGH); 
          delay(100); 
          digitalWrite(comando_tono,LOW);
        }
        if(digitalRead(comando_4)==LOW) {
          digitalWrite(comando_tono,HIGH); 
          delay(1000); 
          digitalWrite(comando_tono,LOW);
        }
        
          
      }
      
      
     
      
      if (str_I=="5" && str_A=="1") {
        digitalWrite(14,HIGH);
        
      }
      
      if (str_I=="5" && str_A=="0") {
        digitalWrite(A0, LOW);
      }
      
      if (str_I=="5" && str_A=="3") {
        if(digitalRead(A0)==HIGH) {
          digitalWrite(comando_tono,HIGH); 
          delay(100); 
          digitalWrite(comando_tono,LOW);
        }
        if(digitalRead(A0)==LOW) {
          digitalWrite(comando_tono,HIGH); 
          delay(1000); 
          digitalWrite(comando_tono,LOW);
        }
        
          
      }
      
      
     if (str_I=="6" && str_A=="1") {
        digitalWrite(A1,HIGH);
      }
      
      if (str_I=="6" && str_A=="0") {
        digitalWrite(A1, LOW);
      }
      
      if (str_I=="6" && str_A=="3") {
        if(digitalRead(A1)==HIGH) {
          digitalWrite(comando_tono,HIGH); 
          delay(100); 
          digitalWrite(comando_tono,LOW);
        }
        if(digitalRead(A1)==LOW) {
          digitalWrite(comando_tono,HIGH); 
          delay(1000); 
          digitalWrite(comando_tono,LOW);
        }
        
          
      }
      
      if (str_I=="7" && str_A=="1") {
        digitalWrite(A2,HIGH);
      }
      
      if (str_I=="7" && str_A=="0") {
        digitalWrite(A2, LOW);
      }
      
      if (str_I=="7" && str_A=="3") {
        if(digitalRead(A2)==HIGH) {
          digitalWrite(comando_tono,HIGH); 
          delay(100); 
          digitalWrite(comando_tono,LOW);
        }
        if(digitalRead(A2)==LOW) {
          digitalWrite(comando_tono,HIGH); 
          delay(1000); 
          digitalWrite(comando_tono,LOW);
        }
        
          
      }
      
      if (str_I=="8" && str_A=="1") {
        digitalWrite(A3,HIGH);
      }
      
      if (str_I=="8" && str_A=="0") {
        digitalWrite(A3, LOW);
      }
      
      if (str_I=="8" && str_A=="3") {
        if(digitalRead(A3)==HIGH) {
          digitalWrite(comando_tono,HIGH); 
          delay(100); 
          digitalWrite(comando_tono,LOW);
        }
        if(digitalRead(A3)==LOW) {
          digitalWrite(comando_tono,HIGH); 
          delay(1000); 
          digitalWrite(comando_tono,LOW);
        }
        
          
      }
      
     if (str_I=="9" && str_A=="1") {
        digitalWrite(A4,HIGH);
      }
      
      if (str_I=="9" && str_A=="0") {
        digitalWrite(A4, LOW);
      }
      
      if (str_I=="9" && str_A=="3") {
        if(digitalRead(A4)==HIGH) {
          digitalWrite(comando_tono,HIGH); 
          delay(100); 
          digitalWrite(comando_tono,LOW);
        }
        if(digitalRead(A4)==LOW) {
          digitalWrite(comando_tono,HIGH); 
          delay(1000); 
          digitalWrite(comando_tono,LOW);
        }
        
          
      }
      
      if (str_I=="10" && str_A=="1") {
        digitalWrite(A5,HIGH);
      }
      
      if (str_I=="10" && str_A=="0") {
        digitalWrite(A5, LOW);
      }
      
      if (str_I=="10" && str_A=="3") {
        if(digitalRead(A5)==HIGH) {
          digitalWrite(comando_tono,HIGH); 
          delay(100); 
          digitalWrite(comando_tono,LOW);
        }
        if(digitalRead(A5)==LOW) {
          digitalWrite(comando_tono,HIGH); 
          delay(1000); 
          digitalWrite(comando_tono,LOW);
        }
       
          }
          /*if (str_I!="1"){
          if (str_I!="2"){
            Serial.println(">=3");*/
          }
        //  }
        
        
          
      
             
//} 
    
    
 void leggiCarattereDTMF()
     {charDTMF_value = (PIND)>>4;   // legge i bit della porta D e shifta a destra di 4 (estrae un valore tra 0 e 15)
      charDTMF_bool = true;}  
      
      
   /*   void esegui_azione(byte az_1, byte az_2, byte az_3)
{
  // digitalWrite(pin, HIGH);
  // Serial.println("ciao");
   //digitalWrite(latchPin, LOW);
   //shiftOut(dataPin, clockPin, MSBFIRST, az_3);   // shiftOut(dataPin, clockPin, MSBFIRST, value); secondo blocco di 8 comandi
   //shiftOut(dataPin, clockPin, MSBFIRST, az_2);   // shiftOut(dataPin, clockPin, MSBFIRST, value); secondo blocco di 8 comandi
   //shiftOut(dataPin, clockPin, MSBFIRST, az_1);   // shiftOut(dataPin, clockPin, MSBFIRST, value); primo blocco di 8 comandi
   //digitalWrite(latchPin, HIGH);
}
      */
      

