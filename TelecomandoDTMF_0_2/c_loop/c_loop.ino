void loop ()
{
  if (charDTMF_bool) {rilevaStringaDTMF();}

  if (comando_bool) 
    {  
      for( int i = 1; i <= indiceComando; i++)
      {if (comandoOK[i])
          {if (indirizzo[i] >= 0  && indirizzo[i] <= 7 ) { bitWrite (azione1, indirizzo[i]   ,azione[i]); }
           if (indirizzo[i] >= 8  && indirizzo[i] <= 15) { bitWrite (azione2, indirizzo[i]- 8,azione[i]); }
           if (indirizzo[i] >= 16 && indirizzo[i] <= 23) { bitWrite (azione3, indirizzo[i]-16,azione[i]); }}
      }

      comando_bool= false;  
      scriviEeprom(azione1, azione2, azione3);
      esegui_azione (azione1, azione2, azione3);
   }
}
      

