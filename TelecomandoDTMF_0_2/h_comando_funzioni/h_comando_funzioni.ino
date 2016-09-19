void esegui_azione(byte az_1, byte az_2, byte az_3)
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, az_3);   // shiftOut(dataPin, clockPin, MSBFIRST, value); secondo blocco di 8 comandi
   shiftOut(dataPin, clockPin, MSBFIRST, az_2);   // shiftOut(dataPin, clockPin, MSBFIRST, value); secondo blocco di 8 comandi
   shiftOut(dataPin, clockPin, MSBFIRST, az_1);   // shiftOut(dataPin, clockPin, MSBFIRST, value); primo blocco di 8 comandi
   digitalWrite(latchPin, HIGH);
}
