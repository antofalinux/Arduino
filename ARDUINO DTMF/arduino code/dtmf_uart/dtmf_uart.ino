#include <FlexiTimer2.h>

int STD = A0;
int Q1 = A1;
int Q2 = A2;
int Q3 = A3;
int Q4 = A4;

unsigned char Q_dat = 0x00;
unsigned char STDat_cnt = 0x00;
unsigned char Decod_finished = 0x00;

//Check once every 5 ms
void dtmf_decode(void)
{
   
   int STD_State = 0;
   int IO_State = 0;
   
    STD_State = digitalRead(STD);
    
    //STD  Rising edge
    if(STD_State) {if(STDat_cnt < 100) STDat_cnt ++;}  else STDat_cnt = 0;

    if(STDat_cnt==3)//Pulse width greater than 15MS
   {
    Q_dat = 0x00;
    
    IO_State = digitalRead(Q1);
    if(IO_State) Q_dat = 0x01;
    
    IO_State = digitalRead(Q2);
    if(IO_State) Q_dat |= 0x02;
    
    IO_State = digitalRead(Q3);
    if(IO_State) Q_dat |= 0x04;
    
    IO_State = digitalRead(Q4);
    if(IO_State) Q_dat |= 0x08;
    
    Decod_finished = 0xff;//Complete the decoding
   
   }

}

void setup()
{
   // initialize the DTMF Decoding module as an output.
    pinMode(STD, INPUT); 
    pinMode(Q1, INPUT);
    pinMode(Q2, INPUT);
    pinMode(Q3, INPUT);
    pinMode(Q4, INPUT);
    
    Serial.begin(9600);
    
   //Enable Timer2
   FlexiTimer2::set(5, 1.0/1000, dtmf_decode); // call every 5 1ms "ticks"
   FlexiTimer2::start();
}

void loop()
{

  //Complete the decoding
 if(Decod_finished)
 {
  Decod_finished = 0;
  
   Serial.print(" Activate : " ); 
   
   switch(Q_dat){
    case 1 : Serial.print("1 \n" );  break;
    case 2 : Serial.print("2 \n" );  break;
    case 3 : Serial.print("3 \n" );  break;
    case 4 : Serial.print("4 \n" );  break;
    case 5 : Serial.print("5 \n" );  break;
    case 6 : Serial.print("6 \n" );  break;
    case 7 : Serial.print("7 \n" );  break;
    case 8 : Serial.print("8 \n" );  break;
    case 9 : Serial.print("9 \n" );  break;
    case 10 : Serial.print("0 \n" );  break;
    case 11 : Serial.print("* \n" );  break;
    case 12 : Serial.print("# \n" );  break;
    case 13 : Serial.print("A \n" );  break;
    case 14 : Serial.print("B \n" );  break;
    case 15 : Serial.print("C \n" );  break;
    default : Serial.print("D \n" );  break;
  } 
  
 }
 
}
