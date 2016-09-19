////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//   JI3BNB RTTY ENCODER for ARDUINO UNO <WORD-MODE-INPUT VERSION>
//   2014.09.15 v4.0
//   DESIGNED FOR AMATEUR RADIO COMMUNICATION
//   REALTIME KEYBOARD INPUT, 5BIT-BAUDOT-CODE, 45.45baud
//   LCD 20x4 (UC-204)
//   SCHEMATIC http://k183.bake-neko.net/ji3bnb/page13.html
//   ** THIS PROGRAM IS IN THE PUBLIC DOMAIN **
//
////////////////////////////////////////////////////////////////////////////////
                                        ////////////////////////////////////////


////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//                   -- BASIC SET UP AND PIN ASSIGNMENTS --
//
////////////////////////////////////////////////////////////////////////////////
                                        ////////////////////////////////////////
     #include <TimerOne.h>
     #include <Wire.h>

//   ** NEED TO DOWNLOAD & INSTALL "TimerOne" LIBRARY **
//   http://playground.arduino.cc/code/timer1

     #define MARK  218   // 218 = (500000 / 2295 Hz)
     #define SPACE 235   // 235 = (500000 / 2125 Hz)

////////////////////////////////////////////////////////////////////////////////
     #include <FlexiTimer2.h>

//   ** NEED TO DOWNLOAD & INSTALL "FlexiTimer2" LIBRARY **
//   http://playground.arduino.cc/Main/FlexiTimer2

////////////////////////////////////////////////////////////////////////////////
     #include <PS2Keyboard.h>

//   ** NEED TO DOWNLOAD & INSTALL "PS2Keyboard" LIBRARY **
//   http://playground.arduino.cc/Main/PS2Keyboard

     PS2Keyboard keyboard;
     const int  DataPin = 2; //IO2 = "DATA"  PIN
     const int  IRQpin  = 3; //IO3 = "CLOCK" PIN (!!DO NOT CAHNGE THIS)

     const boolean jp106 = 0;
//   SELECT 0: ENGLISH  KEYBOARD
//   SELECT 1: JAPANESE KEYBOARD “ú–{ŒêƒL[ƒ{[ƒh

////////////////////////////////////////////////////////////////////////////////
//   #include <LiquidCrystal.h>
     #include <LiquidCrystal_I2C.h>

//   20x4 LCD DISPLAY (HITACHI HD44780 INTERFACE)

//   LiquidCrystal lcd(4,5,6,7,8,9,10);
     LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

//   D10 : D7
//   D9  : D6
//   D8  : D5
//   D7  : D4
//   D6  : EN
//   D5  : R/W
//   D4  : RS

////////////////////////////////////////////////////////////////////////////////
//   YOU CAN ASSIGN 10CH MESSAGES TO EACH NUMBER KEY

     const char  m1[]  = "\rCQ CQ CQ DE CA1CVI CA1CVI CA1CVI PSE K ";
     const char  m2[]  = "\rQRZ? SRI PSE AGN DE CA1CVI K ";
     const char  m3[]  = "\rTNX FER CALL ";
     const char  m4[]  = "\rUR RST 599 599 599 ";
     const char  m5[]  = "\rQTH FG46SH CITY ANTOFAGASTA COUNTRY CHILE ";
     const char  m6[]  = "\rOP CARLOS CARLOS CARLOS ";
     const char  m7[]  = "\rMY TX 100W YAESU 857D / ANT ATAS 120A ";
     const char  m8[]  = "\rMY QSL CARD SURE VIA BURO ";
     const char  m9[]  = "\rTKS FB QSO HPE CU AGN ";
     const char  m0[]  = "\rTU GL SK.. ";
     const char* ms[]  = {m0, m1, m2, m3, m4, m5, m6, m7, m8, m9};

////////////////////////////////////////////////////////////////////////////////
//   D12 : ENCODER OUTPUT (AFSK AUDIO)

////////////////////////////////////////////////////////////////////////////////
//   D13 : ENCODER OUTPUT (0/5V TTL LEVEL)

////////////////////////////////////////////////////////////////////////////////
//   A0(=D14) : [Esc] Key INDICATOR LED

//   THIS INDICATOR MEANS "NOW IN <10CH MESSAGE MODE>"

////////////////////////////////////////////////////////////////////////////////
//   "BAUDOT" CODE HAS SOME TYPES OF VARIATION

     const boolean  usFig  = 1;
//   SELECT 0: "TONO THETA-5000E" COMPATIBLE (ALSO USED IN "MixW" SOFTWARE)
//   SELECT 1: "Fldigi" SOFTWARE COMPATIBLE (=USTTY, POPULARLY USED)

////////////////////////////////////////////////////////////////////////////////
//   DIDDLE ENABLE AND INTERVAL PERIOD

     const int  ddItv   = 250; //INTERVAL (ms)
     boolean    ddl     = 1;   //ENABLE AT START UP

////////////////////////////////////////////////////////////////////////////////
//   SPECIAL KEYS

//   [Esc]        :  GO INTO OR GO OUT OF <10CH MESSAGE MODE>
//   [UP ARROW]   :  DIDDLE ON
//   [DOWN ARROW] :  DIDDLE OFF


////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//                  -- GLOBAL VARIABLES, FLAGS, COUNTERS etc --
//
////////////////////////////////////////////////////////////////////////////////
                                        ////////////////////////////////////////
boolean  space;
boolean  shift;
boolean  crLf;
boolean  snd;
boolean  fig_1;
int      fig_2;
int      ddCnt;
byte     ti;
byte     x;
byte     y;
byte     x4 = 1;
char     ch;
char     ch2;
uint8_t  baudot;
uint8_t  baudot_;


////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//                               -- setup() --
//
////////////////////////////////////////////////////////////////////////////////
                                        ////////////////////////////////////////
void setup()
{
        keyboard.begin(DataPin, IRQpin);
        lcd.begin(20, 4);
        pinMode(12, OUTPUT);
        pinMode(13, OUTPUT);
        pinMode(14, OUTPUT);
        digitalWrite(13, 1);
        
        Timer1.initialize();
        Timer1.attachInterrupt(timer1_interrupt, MARK);
        
        FlexiTimer2::set(1, timer2_interrupt);
        FlexiTimer2::start();
        
        lcd.cursor();
        lcd.setCursor(0, 3);
        lcd.print(">4.0 READY");  //OPENING MESSAGE
        lcd.setCursor(0, 0);
        delay(1000);
        
        lcd.clear();
        lcd.setCursor(0, 3);
        lcd.print('>');
        lcd.setCursor(0, 0);
}


////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//                           -- timer_interrupt --
//
////////////////////////////////////////////////////////////////////////////////
                                        ////////////////////////////////////////
//AFSK TONE GENERATOR
void timer1_interrupt(void)
{
        static boolean toggle;
        
        toggle = toggle ^ 1;
        digitalWrite(12, toggle);
}

//5BIT BAUDOT GENERATOR
void timer2_interrupt(void)
{
        static boolean bit1;
        static boolean bit2;
        static boolean bit3;
        static boolean bit4;
        static boolean bit5;
        
        if(ddCnt < 2000)
        {
                ddCnt++;
        }
        if(snd == 1)
        {
                if(ti == 0){
                        digitalWrite(13, 0);
                        Timer1.setPeriod(SPACE);
                        
                        bit1 = baudot & B00001;
                        bit2 = baudot & B00010;
                        bit3 = baudot & B00100;
                        bit4 = baudot & B01000;
                        bit5 = baudot & B10000;
                }
                else if(ti == 22){
                        digitalWrite(13, bit1);
                        if(bit1){Timer1.setPeriod(MARK);}
                            else{Timer1.setPeriod(SPACE);}
                }
                else if(ti == 44){
                        digitalWrite(13, bit2);
                        if(bit2){Timer1.setPeriod(MARK);}
                            else{Timer1.setPeriod(SPACE);}
                }
                else if(ti == 66){
                        digitalWrite(13, bit3);
                        if(bit3){Timer1.setPeriod(MARK);}
                            else{Timer1.setPeriod(SPACE);}
                }
                else if(ti == 88){
                        digitalWrite(13, bit4);
                        if(bit4){Timer1.setPeriod(MARK);}
                            else{Timer1.setPeriod(SPACE);}
                }
                else if(ti == 110){
                        digitalWrite(13, bit5);
                        if(bit5){Timer1.setPeriod(MARK);}
                            else{Timer1.setPeriod(SPACE);}
                }
                else if(ti == 132){
                        digitalWrite(13, 1);
                        Timer1.setPeriod(MARK);
                }
                else if(ti == 165){
                        snd = 0;
                }
                ti++;
        }
}


////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//                        -- OTHER FUNCTIONS etc --
//
////////////////////////////////////////////////////////////////////////////////
                                        ////////////////////////////////////////
//LINE1-3
void lcdChU()
{
        static char dBuf[41];
        int         i;
        
        lcd.print(ch);
        if(y == 1){dBuf[     x] = ch;}
        if(y == 2){dBuf[20 + x] = ch;}
        x++;
        if(x == 20 && y == 0){x = 0, y = 1;}
        if(x == 20 && y == 1){x = 0, y = 2;}
        if(x == 20 && y == 2)
        {
                 lcd.setCursor(0, 0); for(i = 0; i < 20; i++){lcd.print(dBuf[     i]);}
                 lcd.setCursor(0, 1); for(i = 0; i < 20; i++){lcd.print(dBuf[20 + i]);}
                 lcd.setCursor(0, 2); for(i = 0; i < 20; i++){lcd.print(' ');}
                 x = 0, y = 2;
                 for(i = 0; i < 20; i++){dBuf[i] = dBuf[20 + i];}
        }  
        lcd.setCursor(x, y);
}

void lcdCrLf()
{
        byte rest = (20 - x);
        ch = ' ';
        for(int i = 0; i < rest; i++) //FILL THE LINE WITH SPACES, INSTEAD OF CR&LF
        {
                lcdChU();
        }
}

//LINE4
void lcdChL()
{
        lcd.setCursor(x4, 3);
        lcd.print(ch2);
        x4++;
        lcd.setCursor(x, y); 
}

//LOOKUP TABLE
void chTableT()
{
        if(usFig == 1) //"Fldigi" SOFTWARE COMPATIBLE
        {
                fig_2 = -1;
                if(ch == ' ')
                {
                      baudot = B00100; //SPACE
                      space = 1;
                }
                else if(ch == 'A'){baudot = B00011; fig_2 = 0;}
                else if(ch == 'B'){baudot = B11001; fig_2 = 0;}
                else if(ch == 'C'){baudot = B01110; fig_2 = 0;}
                else if(ch == 'D'){baudot = B01001; fig_2 = 0;}
                else if(ch == 'E'){baudot = B00001; fig_2 = 0;}
                else if(ch == 'F'){baudot = B01101; fig_2 = 0;}
                else if(ch == 'G'){baudot = B11010; fig_2 = 0;}
                else if(ch == 'H'){baudot = B10100; fig_2 = 0;}
                else if(ch == 'I'){baudot = B00110; fig_2 = 0;}
                else if(ch == 'J'){baudot = B01011; fig_2 = 0;}
                else if(ch == 'K'){baudot = B01111; fig_2 = 0;}
                else if(ch == 'L'){baudot = B10010; fig_2 = 0;}
                else if(ch == 'M'){baudot = B11100; fig_2 = 0;}
                else if(ch == 'N'){baudot = B01100; fig_2 = 0;}
                else if(ch == 'O'){baudot = B11000; fig_2 = 0;}
                else if(ch == 'P'){baudot = B10110; fig_2 = 0;}
                else if(ch == 'Q'){baudot = B10111; fig_2 = 0;}
                else if(ch == 'R'){baudot = B01010; fig_2 = 0;}
                else if(ch == 'S'){baudot = B00101; fig_2 = 0;}
                else if(ch == 'T'){baudot = B10000; fig_2 = 0;}
                else if(ch == 'U'){baudot = B00111; fig_2 = 0;}
                else if(ch == 'V'){baudot = B11110; fig_2 = 0;}
                else if(ch == 'W'){baudot = B10011; fig_2 = 0;}
                else if(ch == 'X'){baudot = B11101; fig_2 = 0;}
                else if(ch == 'Y'){baudot = B10101; fig_2 = 0;}
                else if(ch == 'Z'){baudot = B10001; fig_2 = 0;}
                
                else if(ch == '0'){baudot = B10110; fig_2 = 1;}
                else if(ch == '1'){baudot = B10111; fig_2 = 1;}
                else if(ch == '2'){baudot = B10011; fig_2 = 1;}
                else if(ch == '3'){baudot = B00001; fig_2 = 1;}
                else if(ch == '4'){baudot = B01010; fig_2 = 1;}
                else if(ch == '5'){baudot = B10000; fig_2 = 1;}
                else if(ch == '6'){baudot = B10101; fig_2 = 1;}
                else if(ch == '7'){baudot = B00111; fig_2 = 1;}
                else if(ch == '8'){baudot = B00110; fig_2 = 1;}
                else if(ch == '9'){baudot = B11000; fig_2 = 1;}
                else if(ch == '-'){baudot = B00011; fig_2 = 1;}
                else if(ch == '?'){baudot = B11001; fig_2 = 1;}
                else if(ch == ':'){baudot = B01110; fig_2 = 1;}
                else if(ch == '('){baudot = B01111; fig_2 = 1;}
                else if(ch == ')'){baudot = B10010; fig_2 = 1;}
                else if(ch == '.'){baudot = B11100; fig_2 = 1;}
                else if(ch == ','){baudot = B01100; fig_2 = 1;}
                else if(ch == '/'){baudot = B11101; fig_2 = 1;}
                
                //"Fldigi" SOFTWARE COMPATIBLE
                else if(ch == '$' ){baudot = B01001; fig_2 = 1;}
                else if(ch == '\''){baudot = B01011; fig_2 = 1;}
                else if(ch == '!' ){baudot = B01101; fig_2 = 1;}
                else if(ch == '"' ){baudot = B10001; fig_2 = 1;}
                else if(ch == '#' ){baudot = B10100; fig_2 = 1;}
                else if(ch == '&' ){baudot = B11010; fig_2 = 1;}
                else if(ch == ';' ){baudot = B11110; fig_2 = 1;}
                else if(ch == '\r')
                {
                        baudot = B01000; //CR
                        crLf = 1;
                }
                else if(ch == PS2_ESC)
                {
                        //////
                }
                else
                {
                        ch = ' ';
                        baudot = B00100; //SPACE
                        space = 1;
                }
        }
        else if(usFig == 0) //"TONO THETA-5000E" COMPATIBLE
        {
                fig_2 = -1;
                if(ch == ' ')
                {
                      baudot = B00100; //SPACE
                      space = 1;
                }
                else if(ch == 'A'){baudot = B00011; fig_2 = 0;}
                else if(ch == 'B'){baudot = B11001; fig_2 = 0;}
                else if(ch == 'C'){baudot = B01110; fig_2 = 0;}
                else if(ch == 'D'){baudot = B01001; fig_2 = 0;}
                else if(ch == 'E'){baudot = B00001; fig_2 = 0;}
                else if(ch == 'F'){baudot = B01101; fig_2 = 0;}
                else if(ch == 'G'){baudot = B11010; fig_2 = 0;}
                else if(ch == 'H'){baudot = B10100; fig_2 = 0;}
                else if(ch == 'I'){baudot = B00110; fig_2 = 0;}
                else if(ch == 'J'){baudot = B01011; fig_2 = 0;}
                else if(ch == 'K'){baudot = B01111; fig_2 = 0;}
                else if(ch == 'L'){baudot = B10010; fig_2 = 0;}
                else if(ch == 'M'){baudot = B11100; fig_2 = 0;}
                else if(ch == 'N'){baudot = B01100; fig_2 = 0;}
                else if(ch == 'O'){baudot = B11000; fig_2 = 0;}
                else if(ch == 'P'){baudot = B10110; fig_2 = 0;}
                else if(ch == 'Q'){baudot = B10111; fig_2 = 0;}
                else if(ch == 'R'){baudot = B01010; fig_2 = 0;}
                else if(ch == 'S'){baudot = B00101; fig_2 = 0;}
                else if(ch == 'T'){baudot = B10000; fig_2 = 0;}
                else if(ch == 'U'){baudot = B00111; fig_2 = 0;}
                else if(ch == 'V'){baudot = B11110; fig_2 = 0;}
                else if(ch == 'W'){baudot = B10011; fig_2 = 0;}
                else if(ch == 'X'){baudot = B11101; fig_2 = 0;}
                else if(ch == 'Y'){baudot = B10101; fig_2 = 0;}
                else if(ch == 'Z'){baudot = B10001; fig_2 = 0;}
                
                else if(ch == '0'){baudot = B10110; fig_2 = 1;}
                else if(ch == '1'){baudot = B10111; fig_2 = 1;}
                else if(ch == '2'){baudot = B10011; fig_2 = 1;}
                else if(ch == '3'){baudot = B00001; fig_2 = 1;}
                else if(ch == '4'){baudot = B01010; fig_2 = 1;}
                else if(ch == '5'){baudot = B10000; fig_2 = 1;}
                else if(ch == '6'){baudot = B10101; fig_2 = 1;}
                else if(ch == '7'){baudot = B00111; fig_2 = 1;}
                else if(ch == '8'){baudot = B00110; fig_2 = 1;}
                else if(ch == '9'){baudot = B11000; fig_2 = 1;}
                else if(ch == '-'){baudot = B00011; fig_2 = 1;}
                else if(ch == '?'){baudot = B11001; fig_2 = 1;}
                else if(ch == ':'){baudot = B01110; fig_2 = 1;}
                else if(ch == '('){baudot = B01111; fig_2 = 1;}
                else if(ch == ')'){baudot = B10010; fig_2 = 1;}
                else if(ch == '.'){baudot = B11100; fig_2 = 1;}
                else if(ch == ','){baudot = B01100; fig_2 = 1;}
                else if(ch == '/'){baudot = B11101; fig_2 = 1;}
                
                //"TONO THETA-5000E" COMPATIBLE
                else if(ch == '\''){baudot = B00101; fig_2 = 1;}
                else if(ch == '$' ){baudot = B01001; fig_2 = 1;}
                else if(ch == '!' ){baudot = B01101; fig_2 = 1;}
                else if(ch == '+' ){baudot = B10001; fig_2 = 1;}
                else if(ch == '#' ){baudot = B10100; fig_2 = 1;}
                else if(ch == '&' ){baudot = B11010; fig_2 = 1;}
                else if(ch == '=' ){baudot = B11110; fig_2 = 1;}
                else if(ch == '\r')
                {
                        baudot = B01000; //CR
                        crLf = 1;
                }
                else if(ch == PS2_ESC)
                {
                        //////
                }
                else
                {
                        ch = ' ';
                        baudot = B00100; //SPACE
                        space = 1;
                }
        }
}

void chConvt()
{
        if(jp106 == 1) //JP106 KEYBOARD
        {
                     if(ch2 == '@' ){ch2 = '"' ;}
                else if(ch2 == '^' ){ch2 = '&' ;}
                else if(ch2 == '&' ){ch2 = '\'';}
                else if(ch2 == '*' ){ch2 = '(' ;}
                else if(ch2 == '(' ){ch2 = ')' ;}
                else if(ch2 == ')' ){ch2 = '~' ;}
                else if(ch2 == '_' ){ch2 = '=' ;}
                else if(ch2 == '=' ){ch2 = '^' ;}
                else if(ch2 == '+' ){ch2 = '\0';}
                else if(ch2 == '[' ){ch2 = '@' ;}
                else if(ch2 == '{' ){ch2 = '`' ;}
                else if(ch2 == ']' ){ch2 = '[' ;}
                else if(ch2 == '}' ){ch2 = '{' ;}
                else if(ch2 == ':' ){ch2 = '+' ;}
                else if(ch2 == '\''){ch2 = ':' ;}
                else if(ch2 == '"' ){ch2 = '*' ;}
                else if(ch2 == '\\'){ch2 = ']' ;}
                else if(ch2 == '|' ){ch2 = '}' ;}
        }
        if(usFig == 1) //"Fldigi" SOFTWARE COMPATIBLE
        {
                if(ch2 >= 97 && ch2 <= 122) //CONVERT LOWER CASE TO UPPER CASE
                {
                        ch2 = ch2 - 32;
                }
                else if(ch2 == PS2_TAB       ){ch2 = '\0';} //IGNORE THESE KEYS
                else if(ch2 == PS2_PAGEUP    ){ch2 = '\0';}
                else if(ch2 == PS2_PAGEDOWN  ){ch2 = '\0';}
                else if(ch2 == PS2_LEFTARROW ){ch2 = '\0';}
                else if(ch2 == PS2_RIGHTARROW){ch2 = '\0';}
                else if(ch2 == '%'           ){ch2 = '\0';}
                else if(ch2 == '='           ){ch2 = '\0';}
                else if(ch2 == '^'           ){ch2 = '\0';}
                else if(ch2 == '~'           ){ch2 = '\0';}
                else if(ch2 == '|'           ){ch2 = '\0';}
                else if(ch2 == '@'           ){ch2 = '\0';}
                else if(ch2 == '`'           ){ch2 = '\0';}
                else if(ch2 == '['           ){ch2 = '\0';}
                else if(ch2 == '{'           ){ch2 = '\0';}
                else if(ch2 == '+'           ){ch2 = '\0';}
                else if(ch2 == '*'           ){ch2 = '\0';}
                else if(ch2 == ']'           ){ch2 = '\0';}
                else if(ch2 == '}'           ){ch2 = '\0';}
                else if(ch2 == '<'           ){ch2 = '\0';}
                else if(ch2 == '>'           ){ch2 = '\0';}
                else if(ch2 == '\\'          ){ch2 = '\0';}
                else if(ch2 == '_'           ){ch2 = '\0';}
        }
        else if(usFig == 0) //"TONO THETA-5000E" COMPATIBLE
        {
                if(ch2 >= 97 && ch2 <= 122) //CONVERT LOWER CASE TO UPPER CASE
                {
                        ch2 = ch2 - 32;
                }
                else if(ch2 == PS2_TAB       ){ch2 = '\0';} //IGNORE THESE KEYS
                else if(ch2 == PS2_PAGEUP    ){ch2 = '\0';}
                else if(ch2 == PS2_PAGEDOWN  ){ch2 = '\0';}
                else if(ch2 == PS2_LEFTARROW ){ch2 = '\0';}
                else if(ch2 == PS2_RIGHTARROW){ch2 = '\0';}
                else if(ch2 == '"'           ){ch2 = '\0';}
                else if(ch2 == '%'           ){ch2 = '\0';}
                else if(ch2 == '^'           ){ch2 = '\0';}
                else if(ch2 == '~'           ){ch2 = '\0';}
                else if(ch2 == '|'           ){ch2 = '\0';}
                else if(ch2 == '@'           ){ch2 = '\0';}
                else if(ch2 == '`'           ){ch2 = '\0';}
                else if(ch2 == '['           ){ch2 = '\0';}
                else if(ch2 == '{'           ){ch2 = '\0';}
                else if(ch2 == ';'           ){ch2 = '\0';}
                else if(ch2 == '*'           ){ch2 = '\0';}
                else if(ch2 == ']'           ){ch2 = '\0';}
                else if(ch2 == '}'           ){ch2 = '\0';}
                else if(ch2 == '<'           ){ch2 = '\0';}
                else if(ch2 == '>'           ){ch2 = '\0';}
                else if(ch2 == '\\'          ){ch2 = '\0';}
                else if(ch2 == '_'           ){ch2 = '\0';}
        }
}

void chSend1()
{
        if(fig_1 == 0 && fig_2 == 1) //SHIFT "UP"
        {
                baudot_ = baudot; //EVACUATE
                baudot = B11011; //SEND FIGURE CODE FIRST
                shift = 1;
        }
        else if(fig_1 == 1 && fig_2 == 0) //SHIFT "DOWN"
        {
                baudot_ = baudot; //EVACUATE
                baudot = B11111; //SEND LETTER CODE FIRST
                shift = 1;
        }
        else if(space == 1 && fig_2 == 1) //FIGURE AFTER SPACE (TX_UOS)
        {
                baudot_ = baudot; //EVACUATE
                baudot = B11011; //SEND FIGURE CODE FIRST
                shift = 1;
        }
        if(shift != 1 && crLf != 1)
        {
                lcdChU();
        }
        if(fig_2 == 0 || fig_2 == 1)
        {
                space = 0;
                fig_1 = fig_2; //REGISTER LAST STATE (EXCEPT SPACE, CR&LF)
        }
        ti = 0; snd = 1; //SEND(1)
}

void chSend2()
{
        if(shift == 1) //2ND BYTE AFTER SENDING SHIFT CODE
        {
                baudot = baudot_; //RESTORE
                lcdChU();
                shift = 0;
                ti = 0; snd = 1; //SEND(2)
        }
        else if(crLf == 1) //2ND BYTE AFTER SENDING "CR"
        {
                baudot = B00010; //LF
                lcdCrLf();
                crLf = 0;
                ti = 0; snd = 1; //SEND(2)
        }
}


////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//                             -- MAIN LOOP --
//
////////////////////////////////////////////////////////////////////////////////
                                        ////////////////////////////////////////
void loop()
{
        static boolean esc;
        
        if(esc == 1)
        {
                static int  msNo = -1;
                static byte m;
                static byte n;
                static byte o;
                static char mnBuf[8];
                
                if(snd == 0)
                {
                        if(shift == 1 || crLf == 1) //TOP PRIORITY (WHEN 2ND BYTE IS NEEDED)
                        {
                                chSend2();
                        }
                        else if(msNo >= 0) //HANDLES FIXED MESSAGES (MAIN)
                        {
                                ch = ms[msNo][m]; //READ OUT
                                if(ch == '\0') //END OF SENTENCE
                                {
                                        msNo = -1;
                                        if(n == 0) //NO MESSAGE-NUMBER IS STORED FROM THE FIRST, EXIT
                                        {
                                                esc = 0; digitalWrite(14, 0);
                                        }
                                }
                                while(keyboard.available()) //ALWAYS CHECK KEYBOARD
                                {
                                        ch2 = keyboard.read();
                                        if(ch2 == PS2_ESC) //WHEN [Esc] IS TYPED, STOP IMMEDIATELY, AND EXIT
                                        {
                                                msNo = -1;
                                                n = 0;
                                                esc = 0; digitalWrite(14, 0);
                                        }
                                        else if(ch2 >= 48 && ch2 <= 57) //'0'-'9'
                                        {
                                                if(n < 7)
                                                {
                                                        mnBuf[n] = ch2; //REGISTER ADDITIONAL MESSAGE-NUMBERS, 7 NUMBERS AT MAXIMUM
                                                        n++;
                                                }
                                        }
                                }
                                if(msNo >= 0) //-----SEND FIXED MESSAGE-----
                                {
                                        chTableT();
                                        chSend1();
                                        m++;
                                }
                        }
                        else if(n > 0) //COMPLETED SENDING <ONE> FIXED MESSAGE, AND OTHERS STILL REMAIN
                        {
                                ch = mnBuf[o]; //READ OUT
                                if(ch >= 48 && ch <= 57) //'0'-'9'
                                {
                                        msNo = ch - 48; //SPECIFY THE NEXT
                                        m = 0;
                                        o++;
                                }
                                else if(ch == '\0') //THE END OF THE MESSAGE-NUMBERS, EXIT
                                {
                                        n = 0;
                                        esc = 0; digitalWrite(14, 0);
                                }
                        }
                        else if (keyboard.available()) //COMPLETED SENDING <ALL> FIXED MESSAGES, AND KEYBOARD IS TYPED
                        {
                                ch = keyboard.read();
                                if(ch == PS2_ESC) //GO OUT OF [Esc] MODE
                                {
                                        esc = 0;
                                        digitalWrite(14, 0);
                                }
                                else if(ch == PS2_UPARROW) //DIDDLE ON
                                {
                                        ddl = 1;
                                }
                                else if(ch == PS2_DOWNARROW) //DIDDLE OFF
                                {
                                        ddl = 0;
                                }
                                else if(ch >= 48 && ch <= 57) //'0'-'9'
                                {
                                        msNo = ch - 48; //WHEN esc=1 AND A MESSAGE KEY IS TYPED, START SENDING A NEW ONE
                                        //--Ini
                                        m = 0;
                                        o = 0;
                                        for(int i = 0; i < 7; i++)
                                        {
                                                mnBuf[i] = '\0';
                                        }
                                        //--
                                }
                        }
                        else //NOTHING TO PROCESS, DIDDLE
                        {
                                if(ddl == 1 && ddCnt > ddItv)
                                {
                                        baudot = B11111;//LTR(DIDDLE)
                                        fig_1 = 0;
                                        ti = 0; snd = 1;
                                }
                        } 
                }
        }
        else if(esc == 0)
        {
                static byte sWait;
                static byte wdNo;
                static byte w;
                static char iBuf[21];
                static char sBuf[8][21];
                
                if(snd == 0)
                {
                        if(shift == 1 || crLf == 1) //TOP PRIORITY (WHEN 2ND BYTE IS NEEDED)
                        {
                                chSend2();
                        }
                        else if(sWait > 0)
                        {
                                wdNo = 0;
                                ch = sBuf[wdNo][w]; //RAED OUT
                                if(ch == '\0')
                                {
                                        sWait--;
                                        for(wdNo = 0; wdNo < sWait; wdNo++)
                                        {
                                                //---sBuf CLEAR [wdNo]
                                                for(int i = 0; i < 20; i++)
                                                {
                                                        sBuf[wdNo][i] = '\0';
                                                }
                                                //---
                                                w = 0;
                                                while(sBuf[wdNo + 1][w] != '\0')
                                                {
                                                        sBuf[wdNo][w] = sBuf[wdNo + 1][w]; //SHIFT TO "LEFT"
                                                        w++;
                                                }
                                        }
                                        //---sBuf CLEAR [wdNo]
                                        for(int i = 0; i < 20; i++)
                                        {
                                                sBuf[wdNo][i] = '\0';
                                        }
                                        //---
                                        w = 0;
                                }
                                else
                                {
                                        chTableT();
                                        chSend1();
                                        w++;
                                }
                        }
                        else //NOTHING TO SEND
                        {
                                if(ddl == 1 && ddCnt > ddItv)
                                {
                                        baudot = B11111;//LTR(DIDDLE)
                                        fig_1 = 0;
                                        ti = 0; snd = 1;
                                }
                        }
                }
                if(keyboard.available())
                {
                        ch2 = keyboard.read();
                        chConvt();
                        if(ch2 != '\0')
                        {
                                if(ch2 == PS2_ESC) //CHANGE TO [Esc] MODE
                                {
                                        for(wdNo = 0; wdNo < 8; wdNo++)
                                        {
                                                //---sBuf CLEAR [wdNo]
                                                for(int i = 0; i < 20; i++)
                                                {
                                                        sBuf[wdNo][i] = '\0';
                                                }
                                                //---
                                        }
                                        w = 0;
                                        esc = 1;
                                        digitalWrite(14, 1);
                                }
                                else if(ch2 == PS2_UPARROW) //DIDDLE ON
                                {
                                        ddl = 1;
                                }
                                else if(ch2 == PS2_DOWNARROW) //DIDDLE OFF
                                {
                                        ddl = 0;
                                }
                                else if(sWait < 8 && x4 < 21)  //STORE 8 WORDS AT MAXIMUM
                                {
                                        if(ch2 == ' ' || ch2 == '\r')
                                        {
                                                iBuf[x4 - 1] = ch2;
                                                if(sWait == 0)
                                                {
                                                        w = 0;
                                                }
                                                sWait++;
                                                int i = 0;
                                                while(iBuf[i] != '\0')
                                                {
                                                        sBuf[sWait - 1][i] = iBuf[i];
                                                        i++;
                                                }
                                                
                                                //---iBuf CLEAR
                                                for(int i = 0; i < 20; i++)
                                                {
                                                        iBuf[i] = '\0';
                                                }
                                                //---
                                                
                                                //LINE4 CLEAR
                                                lcd.setCursor(1, 3);
                                                for(int i = 0; i < 19; i++)
                                                {
                                                        lcd.print(' ');
                                                }
                                                x4 = 1;
                                                lcd.setCursor(x, y);
                                                //---
                                        }
                                        else if(ch2 == PS2_BACKSPACE) //HANDLES [Delete] or [Back space] KEY
                                        {
                                                if(x4 > 1)
                                                {
                                                        x4--;
                                                        iBuf[x4 - 1] = '\0';
                                                        lcd.setCursor(x4, 3);
                                                        lcd.print(' ');
                                                        lcd.setCursor(x, y);
                                                }
                                        }
                                        else if(x4 < 20)
                                        {
                                                iBuf[x4 - 1] = ch2;
                                                lcdChL();
                                        }
                                }
                        }
                }
        }
        delay(3);
}

//   -- END OF THE SKETCH --
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
