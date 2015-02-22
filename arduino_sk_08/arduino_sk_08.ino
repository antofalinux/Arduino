//45.45baud BAUDOT TELEMETRY BEACON 1.4

#include <stdio.h>

#define AFSK_OUT 12   //---- AFSK AUDIO OUTPUT
#define FSK_OUT  13   //---- TTL LEVEL OUTPUT
#define MARK     2295
#define SPACE    2125

const char ID[] = "DE CA1CVI CA1CVI CA1CVI /B ";

boolean d1;
boolean d2;
boolean d3;
boolean d4;
boolean d5;
boolean sSq;
boolean fig1;
boolean fig2;
boolean sRd    = 1;
byte    i;
byte    j;
byte    idC;
char    ch;
char    sVal[9];

void setup()
{
        pinMode(FSK_OUT,  OUTPUT);
        pinMode(AFSK_OUT, OUTPUT);
        digitalWrite(FSK_OUT, HIGH);
        tone(AFSK_OUT, MARK);
        delay(700);
}

void sendFsk()
{
        //--start bit
        digitalWrite(FSK_OUT, LOW);
        tone(AFSK_OUT, SPACE);
        delay(22);
        //--bit1
        if(d1 == 1){
                digitalWrite(FSK_OUT, HIGH);
                tone(AFSK_OUT, MARK);
        }
        else{
                digitalWrite(FSK_OUT, LOW);
                tone(AFSK_OUT, SPACE);
        }
        delay(22);
        //--bit2
        if(d2 == 1){
                digitalWrite(FSK_OUT, HIGH);
                tone(AFSK_OUT, MARK);
        }
        else{
                digitalWrite(FSK_OUT, LOW);
                tone(AFSK_OUT, SPACE);
        }
        delay(22);
        //--bit3
        if(d3 == 1){
                digitalWrite(FSK_OUT, HIGH);
                tone(AFSK_OUT, MARK);
        }
        else{
                digitalWrite(FSK_OUT, LOW);
                tone(AFSK_OUT, SPACE);
        }
        delay(22);
        //--bit4
        if(d4 == 1){
                digitalWrite(FSK_OUT, HIGH);
                tone(AFSK_OUT, MARK);
        }
        else{
                digitalWrite(FSK_OUT, LOW);
                tone(AFSK_OUT, SPACE);
        }
        delay(22);
        //--bit5
        if(d5 == 1){
                digitalWrite(FSK_OUT, HIGH);
                tone(AFSK_OUT, MARK);
        }
        else{
                digitalWrite(FSK_OUT, LOW);
                tone(AFSK_OUT, SPACE);
        }
        delay(22);
        //--stop bit
        digitalWrite(FSK_OUT, HIGH);
        tone(AFSK_OUT, MARK);
        delay(33);
}

void chTable()
{
        if(ch == ' ')
        {
                d1 = 0; d2 = 0; d3 = 1; d4 = 0; d5 = 0;
        }
        else if(ch == 'A'){d1 = 1; d2 = 1; d3 = 0; d4 = 0; d5 = 0; fig2 = 0;}
        else if(ch == 'B'){d1 = 1; d2 = 0; d3 = 0; d4 = 1; d5 = 1; fig2 = 0;}
        else if(ch == 'C'){d1 = 0; d2 = 1; d3 = 1; d4 = 1; d5 = 0; fig2 = 0;}
        else if(ch == 'D'){d1 = 1; d2 = 0; d3 = 0; d4 = 1; d5 = 0; fig2 = 0;}
        else if(ch == 'E'){d1 = 1; d2 = 0; d3 = 0; d4 = 0; d5 = 0; fig2 = 0;}
        else if(ch == 'F'){d1 = 1; d2 = 0; d3 = 1; d4 = 1; d5 = 0; fig2 = 0;}
        else if(ch == 'G'){d1 = 0; d2 = 1; d3 = 0; d4 = 1; d5 = 1; fig2 = 0;}
        else if(ch == 'H'){d1 = 0; d2 = 0; d3 = 1; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == 'I'){d1 = 0; d2 = 1; d3 = 1; d4 = 0; d5 = 0; fig2 = 0;}
        else if(ch == 'J'){d1 = 1; d2 = 1; d3 = 0; d4 = 1; d5 = 0; fig2 = 0;}
        else if(ch == 'K'){d1 = 1; d2 = 1; d3 = 1; d4 = 1; d5 = 0; fig2 = 0;}
        else if(ch == 'L'){d1 = 0; d2 = 1; d3 = 0; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == 'M'){d1 = 0; d2 = 0; d3 = 1; d4 = 1; d5 = 1; fig2 = 0;}
        else if(ch == 'N'){d1 = 0; d2 = 0; d3 = 1; d4 = 1; d5 = 0; fig2 = 0;}
        else if(ch == 'O'){d1 = 0; d2 = 0; d3 = 0; d4 = 1; d5 = 1; fig2 = 0;}
        else if(ch == 'P'){d1 = 0; d2 = 1; d3 = 1; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == 'Q'){d1 = 1; d2 = 1; d3 = 1; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == 'R'){d1 = 0; d2 = 1; d3 = 0; d4 = 1; d5 = 0; fig2 = 0;}
        else if(ch == 'S'){d1 = 1; d2 = 0; d3 = 1; d4 = 0; d5 = 0; fig2 = 0;}
        else if(ch == 'T'){d1 = 0; d2 = 0; d3 = 0; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == 'U'){d1 = 1; d2 = 1; d3 = 1; d4 = 0; d5 = 0; fig2 = 0;}
        else if(ch == 'V'){d1 = 0; d2 = 1; d3 = 1; d4 = 1; d5 = 1; fig2 = 0;}
        else if(ch == 'W'){d1 = 1; d2 = 1; d3 = 0; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == 'X'){d1 = 1; d2 = 0; d3 = 1; d4 = 1; d5 = 1; fig2 = 0;}
        else if(ch == 'Y'){d1 = 1; d2 = 0; d3 = 1; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == 'Z'){d1 = 1; d2 = 0; d3 = 0; d4 = 0; d5 = 1; fig2 = 0;}
        else if(ch == '0'){d1 = 0; d2 = 1; d3 = 1; d4 = 0; d5 = 1; fig2 = 1;}
        else if(ch == '1'){d1 = 1; d2 = 1; d3 = 1; d4 = 0; d5 = 1; fig2 = 1;}
        else if(ch == '2'){d1 = 1; d2 = 1; d3 = 0; d4 = 0; d5 = 1; fig2 = 1;}
        else if(ch == '3'){d1 = 1; d2 = 0; d3 = 0; d4 = 0; d5 = 0; fig2 = 1;}
        else if(ch == '4'){d1 = 0; d2 = 1; d3 = 0; d4 = 1; d5 = 0; fig2 = 1;}
        else if(ch == '5'){d1 = 0; d2 = 0; d3 = 0; d4 = 0; d5 = 1; fig2 = 1;}
        else if(ch == '6'){d1 = 1; d2 = 0; d3 = 1; d4 = 0; d5 = 1; fig2 = 1;}
        else if(ch == '7'){d1 = 1; d2 = 1; d3 = 1; d4 = 0; d5 = 0; fig2 = 1;}
        else if(ch == '8'){d1 = 0; d2 = 1; d3 = 1; d4 = 0; d5 = 0; fig2 = 1;}
        else if(ch == '9'){d1 = 0; d2 = 0; d3 = 0; d4 = 1; d5 = 1; fig2 = 1;}
        else if(ch == '-'){d1 = 1; d2 = 1; d3 = 0; d4 = 0; d5 = 0; fig2 = 1;}
        else if(ch == '?'){d1 = 1; d2 = 0; d3 = 0; d4 = 1; d5 = 1; fig2 = 1;}
        else if(ch == ':'){d1 = 0; d2 = 1; d3 = 1; d4 = 1; d5 = 0; fig2 = 1;}
        else if(ch == '('){d1 = 1; d2 = 1; d3 = 1; d4 = 1; d5 = 0; fig2 = 1;}
        else if(ch == ')'){d1 = 0; d2 = 1; d3 = 0; d4 = 0; d5 = 1; fig2 = 1;}
        else if(ch == '.'){d1 = 0; d2 = 0; d3 = 1; d4 = 1; d5 = 1; fig2 = 1;}
        else if(ch == ','){d1 = 0; d2 = 0; d3 = 1; d4 = 1; d5 = 0; fig2 = 1;}
        else if(ch == '/'){d1 = 1; d2 = 0; d3 = 1; d4 = 1; d5 = 1; fig2 = 1;}
        else if(ch == '+'){d1 = 1; d2 = 0; d3 = 0; d4 = 0; d5 = 1; fig2 = 1;} //ITA2
        else if(ch == '\0')
        {
                /////
        }
        else
        {
                ch = ' ';
                d1 = 0; d2 = 0; d3 = 1; d4 = 0; d5 = 0;
        } 
}

void loop()
{
        //SEND SENSOR VALUES
        if(sSq == 0)
        {
                if( sRd == 1)
                {
                        if(i == 0)
                        {
                                sprintf(sVal, "A0: %04d", analogRead(0));
                        }
                        if(i == 1)
                        {
                                sprintf(sVal, "A1: %04d", analogRead(1));
                        }
                        if(i == 2)
                        {
                                sprintf(sVal, "A2: %04d", analogRead(2));
                        }
                        if(i == 3)
                        {
                                sprintf(sVal, "A3: %04d", analogRead(3));
                        }
                        sRd = 0;
                }
                ch = sVal[j];
                chTable();
                if(ch != '\0')
                {
                        if(fig1 == 0 && fig2 == 1)
                        {
                                d1 = 1; d2 = 1; d3 = 0; d4 = 1; d5 = 1; //FIGURES
                        }
                        else if(fig1 == 1 && fig2 == 0)
                        {
                                d1 = 1; d2 = 1; d3 = 1; d4 = 1; d5 = 1; //LETTERS
                        }
                        else
                        {
                                j++;
                        }
                        fig1 = fig2;
                        sendFsk();
                }
                if(ch == '\0')
                {
                        d1 = 0; d2 = 0; d3 = 1; d4 = 0; d5 = 0; //SPACE
                        sendFsk();
                        i++;
                        if(i == 4) //OVERFLOW
                        {
                                i = 0;
                                sSq = 1;
                        }
                        j = 0;
                        sRd = 1;
                }
        }
        //SEND ID
        if(sSq == 1)
        {
                if(idC < 9)
                {
                        d1 = 0; d2 = 0; d3 = 0; d4 = 1; d5 = 0; //CR
                        sendFsk();
                        d1 = 0; d2 = 1; d3 = 0; d4 = 0; d5 = 0; //LF
                        sendFsk();
                        sSq = 0;
                        j = 0;
                        delay(700);
                        idC++;
                }
                if(idC == 9)
                {
                        ch = ID[j];
                        chTable();
                        if(ch != '\0')
                        {
                                if(fig1 == 0 && fig2 == 1)
                                {
                                        d1 = 1; d2 = 1; d3 = 0; d4 = 1; d5 = 1; //FIGURES
                                }
                                else if(fig1 == 1 && fig2 == 0)
                                {
                                        d1 = 1; d2 = 1; d3 = 1; d4 = 1; d5 = 1; //LETTERS
                                }
                                else
                                {
                                        j++;
                                }
                                fig1 = fig2;
                                sendFsk();
                        }
                        if(ch == '\0')
                        {
                                d1 = 0; d2 = 0; d3 = 0; d4 = 1; d5 = 0; //CR
                                sendFsk();
                                d1 = 0; d2 = 1; d3 = 0; d4 = 0; d5 = 0; //LF
                                sendFsk();
                                sSq = 0;
                                j = 0;
                                delay(700);
                                idC = 0;
                        }
                }
        }
        delay(5);
}
