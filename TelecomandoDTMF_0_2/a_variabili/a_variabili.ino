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
String passKey = "123";         // password (una qualsiasi combinazione di numeri e/o ABCD# (.. non usare * - asterischi)
const byte dimComando = 4;      // numero massimo di comandi inviabili nella stringa 
byte indirizzo [dimComando+1], azione [dimComando+1]; // generico comando suddiviso in indirizzo ed azIONE
boolean comandoOK [dimComando+1]; // true se la coppia indirizzo ed azione è valida, altrimenti false

byte indiceComando = 0;
boolean comando_bool= false;    // indica la presenza di almeno un comando regolarmente decodificato

#define debug_bool true        // attiva la stampa su serial monitor per il debug


// DTMF variabili globali *******************************************************
const byte dataPin  = A3;   // PIN utilizzati per lo shift register
const byte latchPin = A4;   // 24 uscite indipendenti
const byte clockPin = A5;   //

byte azione1, azione2, azione3; // usate per controllare le azioni sui 16 PIN di comando dello shift register
byte bitStart = 10; // bit della eeprom da cui iniaziare a memorizzare lo stato di funzionamento (azione1, azione2 e azione 3)
