#include <FlexiTimer2.h>

int STD = A0;
int Q1 = A1;
int Q2 = A2;
int Q3 = A3;
int Q4 = A4;

int CH1 = 2;
int CH2 = 3;
int CH3 = 4;
int CH4 = 5;

unsigned char Q_dat = 0x00;
unsigned char STDat_cnt = 0x00;
unsigned char Decod_finished = 0x00;

int delay_time = 500;//500 ms

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
    
    pinMode(CH1, OUTPUT);
    pinMode(CH2, OUTPUT);
    pinMode(CH3, OUTPUT);
    pinMode(CH4, OUTPUT);
    
    digitalWrite(CH1, HIGH);
    digitalWrite(CH2, HIGH);
    digitalWrite(CH3, HIGH);
    digitalWrite(CH4, HIGH);
    
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
   
   switch(Q_dat){
    case 1 : Serial.print(" Activate : Channel 1 \n" ); digitalWrite(CH1, LOW);delay(delay_time);digitalWrite(CH1, HIGH); break;
    case 2 : Serial.print(" Activate : Channel 2 \n" ); digitalWrite(CH2, LOW);delay(delay_time);digitalWrite(CH2, HIGH);break;
    case 3 : Serial.print(" Activate : Channel 3 \n" ); digitalWrite(CH3, LOW);delay(delay_time);digitalWrite(CH3, HIGH); break;
    case 4 : Serial.print(" Activate : Channel 4 \n" ); digitalWrite(CH4, LOW); delay(delay_time);digitalWrite(CH4, HIGH);break;
    default : Serial.print("Invalid channel \n" );  break;
  } 
  
 }
 
}
