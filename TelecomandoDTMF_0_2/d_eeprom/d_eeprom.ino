


void leggiEeprom()  // legge l'ultimo stato di funzionamento registrato ..
{
   azione1 = EEPROM.read(bitStart+1); // legge i valori memorizzati per azione1
   azione2 = EEPROM.read(bitStart+2); // legge i valori memorizzati per azione2
   azione3 = EEPROM.read(bitStart+3); // legge i valori memorizzati per azione3
}

 
 void scriviEeprom(byte az_1, byte az_2, byte az_3)  // memorizza l'ultimo stato di funzionamento eseguito ..
{
   EEPROM.write (bitStart+1 , az_1);   // scrive i valori memorizzati per azione1
   EEPROM.write (bitStart+2 , az_2);   // scrive i valori memorizzati per azione2
   EEPROM.write (bitStart+3 , az_3);   // scrive i valori memorizzati per azione3
}

 void scriviPassw(String  passw)  // memorizza l'ultimo stato di funzionamento eseguito ..
{
 
}

 void leggiPassw(String  passw)  // memorizza l'ultimo stato di funzionamento eseguito ..
{
 
}
