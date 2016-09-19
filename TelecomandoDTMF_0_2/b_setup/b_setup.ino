void setup ()
{
 #if(debug_bool) // DEBUG *********************************
 Serial.begin(4800);
 #endif
 
 DDRC = B00111000; // imposta i PIN della PORT C: A0, A1, A2 INPUT, A3, A4, A5 OUTPUT, A6 e A7 non sono disponibili...

 DDRD = B00000000; // imposta i PIN della PORT D in lettura --- > PD0 - PD7  ....... ARDUINO           PD3            PD4          PD5           PD6          PD7
                                                                                    //MT8870       PIN 15(STD)     PIN 11(Q1)  PIN 12(Q2)    PIN 13(Q3)    PIN 14(Q4)
 attachInterrupt(intPIN, leggiCarattereDTMF, RISING);

 leggiEeprom();
 esegui_azione (azione1, azione2, azione3);



}
