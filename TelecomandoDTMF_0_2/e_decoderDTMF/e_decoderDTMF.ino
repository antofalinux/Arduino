void rilevaStringaDTMF ()
{  
 comando_bool= false;  //se entra in questa funzione significa che sta ricevendo un carattere dtmf, quindi sta costruendo la stringa... bool è falso fino alla decofica della stringa
 if ( millis()- r1 > (7000) ) { char_DTMF_buffer = "" ;} //azzera la stringa DTMF gia ricevuta se passano più di 7 sec dall'ultima digitazione
 r1 = millis();  // counter utilizzato per azzerare la stringa DTMF dopo un intervallo stabilito se non si è concluso il comando

 // aggiunge il carattere letto al buffer e dopo  pone charDTMF_bool = false;
 if (char_DTMF_buffer.length() <= bufferSize) {char_DTMF_buffer = char_DTMF_buffer + keyDTMF[charDTMF_value]; charDTMF_bool = false;}

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
                String comandi=""; comandi = char_DTMF_buffer.substring(passKey.length(), char_DTMF_buffer.length()-2);  // estrae la sub string contenente i comandi (elimina la password e gli ultimi 2 **

                #if(debug_bool) // DEBUG *********************************
                Serial.print("\n"); Serial.print(comandi);
                #endif    

                int i =0; indiceComando = 0; String comando; // conterrà i comandi e le azioni associate  
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
                    if (indiceComando > dimComando) { indiceComando = dimComando; break;} // esce se raggiunge in num max di comandi inviabili nella stessa stringa
                   comando = comando + comandi.charAt(i); // isola il singolo comando nel buffer che dovrà avere il formato *xx#x
                   i++;
                 }  
              
            #if(debug_bool) // DEBUG *********************************
            for( int i = 1; i <= indiceComando; i++){ Serial.print("\n  "); Serial.print(indirizzo[i]); Serial.print("  "); Serial.print(azione[i]); Serial.print("  "); Serial.print(comandoOK[i]);}
            #endif    
             
             }
                  
           #if(debug_bool) // DEBUG ********************************* 
           else { Serial.print("\n"); Serial.print(" passw NON Trovata!!!"); }
           #endif    
                 
        char_DTMF_buffer = "" ; // azzera il buffer
        }
}

