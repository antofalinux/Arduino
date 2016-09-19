
int intPIN = 1; //interrupt 0 ---> pin digital 2


// DTMF variables globales *******************************************************
char keyDTMF[] = {'D', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#', 'A', 'B', 'C' };
char charDTMF_value = 0;        // valor letto cuando se verifica la interrupcion
boolean charDTMF_bool = false;  // indica que estado decodificado (es true) un caracter


// BUFFER contiene el string recibido DTMF ****************************************************
String char_DTMF_buffer;    // stringa BUFFER dove vengono osizionati i caratteri decodificati ....
const int bufferSize = 25;  // dimensione del buffer su cui vengono inviati i caratteri decodificati (da dimensionanrsi in funzione del numero max di comandi che si intende inviare|ricevere

String passKey = "123";     // password (una qualsiasi combinazione di numeri e/o ABCD# (.. non usare * - asterischi)
boolean passBool;           // indica che è stata riconosciuta la password e la fine della stringa comando che deve finire con "**" (2 asterischi)
//ojo la passord es 123 recuerden eso
unsigned long r1;  // counter utilizzato per azzerare la stringa DTMF dopo un intervallo stabilito se non si è concluso il comando

boolean debug_bool=true; 

// COMANDI ******************************************************************
const byte dimComando = 3; // numero massimo di comandi inviabili nella stringa 
String comando [dimComando+1]; // estrae i comandi e le azioni associate      
String comando_azione;
byte  indiceComando = 0; // conta i comandi decodificati nella stringa DTMF


void setup ()
{
DDRD = B00000000; // imposta i PIN della PORT D in lettura --- > PD0 - PD7
attachInterrupt(intPIN, leggiCarattereDTMF, RISING);
if (debug_bool) {Serial.begin(4800);} // prova stampa su seriale
}

void loop ()
{

if (charDTMF_bool) {rilevaStringaDTMF();}

}


void rilevaStringaDTMF ()
{ 
if ( millis()- r1 > (7000) ) { char_DTMF_buffer = "" ; } //azzera la stringa DTMF gia ricevuta se passano più di 7 sec dall'ultima digitazione
r1 = millis();  // counter utilizzato per azzerare la stringa DTMF dopo un intervallo stabilito se non si è concluso il comando

// dopo aver letto il carattere pone charDTMF_bool = false;
if (char_DTMF_buffer.length() <= bufferSize) {char_DTMF_buffer = char_DTMF_buffer + keyDTMF[charDTMF_value]; charDTMF_bool = false;}

     // Stampa sulla seriale, per fare il debug, la lunghezza del buffer, il valore ricevuto, il codice corrispondente, ed il buffer fin lì memorizzato ..
     if (debug_bool) {stampaBuffer ( char_DTMF_buffer.length(), charDTMF_value, keyDTMF[charDTMF_value], char_DTMF_buffer);}
   
     // chiude la costruzione della stringa DTMF se ultimata con due ** o se raggiunge la lung. massima stabilita
     if ((char_DTMF_buffer.substring(char_DTMF_buffer.length()-2, char_DTMF_buffer.length()) == "**") || (char_DTMF_buffer.length() == bufferSize))
        { 
         // cerca la password nei primi passKey.length() caratteri
          passBool = (char_DTMF_buffer.substring(0, passKey.length()) == passKey); 

          if (passBool)
             { 
               if (debug_bool) {stampaComandi(" password Encontrada!!!");} // stampa la stringa sulla seriale per fare il debug

               // stringa DTMF depurata da password e ultimi due **
               String comandi=""; comandi = char_DTMF_buffer.substring(passKey.length(), char_DTMF_buffer.length()-2);  // estrae la sub string contenente i comandi (elimina la password e gli ultimi 2 **

               eliminaComandi();   // elimina i comandi decodificati in precedenza 
               if (debug_bool) {stampaComandi(comandi);} // stampa la stringa sulla seriale per fare il debug

               int i =0;
               while (i <= comandi.length()) // scansiona il buffer fintanto che non è arrivato alla fine 
                { 
                  if ( comandi.charAt(i) == '*'){indiceComando++; i++;}  // icrementa il contatore e 'fa sparire' gli *
                  if (indiceComando > dimComando) {indiceComando = dimComando; break;}
                  comando[indiceComando] = comando [indiceComando] + comandi.charAt(i)+ "\0";
                  i++;
                }  
             if (debug_bool) { for( int i = 1; i <= indiceComando; i++){stampaComando(i, comando[i]); }} // stampa sulla seriale gli indirizzi e le azioni , per fare il debug
            }
          else {if (debug_bool) { stampaComandi(" password NO Encontrada!!!");} } // stampa sulla seriale  per fare il debug

       char_DTMF_buffer = "" ; // azzera il buffer
       }
}



void stampaComandi(String str)
{ Serial.print ("\n comando: ");Serial.print (str);}

void stampaComando(int k, String str1 )
{ Serial.print ("\n direccion:"); Serial.print (k);Serial.print ("       :"); Serial.print (str1);}

void stampaBuffer(byte indice, byte value, char key, String buffer)
{ Serial.print ("\n indice:"); Serial.print (indice); Serial.print ("   valor:"); Serial.print (value); Serial.print ("   Key:"); Serial.print (key); Serial.print ("   buffer:"); Serial.print (buffer); }

void eliminaComandi()
{ for( int i = 1; i <= dimComando; i++){ Serial.print ("\n cancelar:"); Serial.print (i);comando[i]="" ;}  indiceComando=0;}

void leggiCarattereDTMF()
{charDTMF_value = (PIND & B11110000)>>4;   // legge i bit della porta D effetua il bitwise AND con 11110000 e shifta a destra di 4 (estrae un valore tra 0 e 15)
charDTMF_bool = true;}                     //
