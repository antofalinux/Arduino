

void estraiComandi(int i, String str )
{     Serial.print("\n"); Serial.print(str);
      String str_I, str_A;
      boolean bool_1, bool_2;
      str_I = str.substring(0, str.indexOf("#")); char Chr_I[str_I.length()+1]; str_I.toCharArray(Chr_I, str_I.length()+1) ; indirizzo[i] = atoi(Chr_I);
      str_A = str.substring(str.indexOf("#")+1);  char Chr_A[str_A.length()+1]; str_A.toCharArray(Chr_A, str_A.length()+1) ;    azione[i] = atoi(Chr_A);

      bool_1 = (indirizzo[i] >= 0 &&  indirizzo[i] <= 23) && (azione[i] == 0 || azione[i] == 1); // verifica che indirizzo ed azione siano compresi tra i valori validi
      bool_2 = ((str.indexOf("#") == 1 && str.length() > 2) || (str.indexOf("#") == 2 && str.length() > 3)); // verifica che # sia posizionato bene nella stringa 
 
      if (bool_1 && bool_2) {comando_bool = true; comandoOK [i] = true; } else {comandoOK [i] = false;} // se non sono verificate le condizoini di cui sopra il comando non viene accettato
} 
    
    
void leggiCarattereDTMF()
     {charDTMF_value = (PIND)>>4;   // legge i bit della porta D e shifta a destra di 4 (estrae un valore tra 0 e 15)
      charDTMF_bool = true;}  
