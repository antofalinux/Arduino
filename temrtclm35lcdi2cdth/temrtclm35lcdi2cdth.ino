
/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
#include <stdio.h>
#include <string.h>
#include <DS1302.h>
//* #include <time.h>*/


/* Set the appropriate digital I/O pin connections */
uint8_t CE_PIN   = 5; //Pin RST
uint8_t IO_PIN   = 6; //Pin DAT
uint8_t SCLK_PIN = 7; //Pin CLK

#define dht_dpin A1

/* Create buffers */
char buf[50];
char day[50];
char hora[50];
byte bGlobalErr;
byte dht_dat[5];

DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);



/*-----( Declare Constants )-----*/
/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 16 chars 2 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

/*-----( Declare Variables )-----*/
//NONE
// Declaracion de variables

void print_time()
{
  /* Get the current time and date from the chip */
  Time t = rtc.time();
 
 
  /* Name the day of the week */
  memset(day, 0, sizeof(day));  /* clear day buffer */
  switch (t.day) {
    case 1:
      strcpy(day, "Domingo");
      break;
    case 2:
      strcpy(day, "Lunes");
      break;
    case 3:
      strcpy(day, "Martes");
      break;
    case 4:
      strcpy(day, "Miercoles");
      break;
    case 5:
      strcpy(day, "Jueves");
      break;
    case 6:
      strcpy(day, "Viernes");
      break;
    case 7:
      strcpy(day, "Sabado");
      break;
  }

  /* Format the time and date and insert into the temporary buffer */
  snprintf(buf, sizeof(buf), "%s %02d-%02d",
           day,
           t.date, t.mon);
//fecha= t.date;

  /* Print the formatted string to serial so we can see the time */
 // Serial.println(buf);
  
  snprintf(hora, sizeof(hora), "%s %02d:%02d:%02d", 
            "son las ",
           t.hr, t.min, t.sec);
  // Serial.println(buf);
}


float tempC;
int tempPin = 0; // Definimos la entrada en pin A0



void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);  // Used to type in characters  

  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight

// ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on  

//-------- Write characters on the display ------------------
// NOTE: Cursor Position: (CHAR, LINE) start at 0  
  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("Hola Tortuga");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Control Acuario"); // Print text on second line
  delay(1000);  

// Wait and then tell user they can start the Serial Monitor and type in characters to
// Display. (Set Serial Monitor option to "No Line Ending")
/*  lcd.clear();
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Use Serial Mon");
  lcd.setCursor(0,1);
  lcd.print("Type to display"); */

InitDHT();

Serial.begin(9600);

//delay(300);

//Serial.println("Humedad y Temperatura");

//delay(700);



}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  
  
  
  
   ReadDHT();

  switch (bGlobalErr){

     case 0:

lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("Humedad Actual");
  delay(1000);
lcd.setCursor(0,1);
 lcd.print("                ");
 lcd.setCursor(0,1);
 //Serial.print("Humedad Actual   ");
lcd.print(dht_dat[0], DEC);
 //lcd.print(".");
 //Serial.print(dht_dat[1], DEC);
 lcd.print("%  ");
delay(1000);
 lcd.setCursor(0,0);
 lcd.print("temperatura aire");
lcd.setCursor(0,1);
 lcd.print("                ");
 lcd.setCursor(0,1);
 lcd.print(dht_dat[2], DEC);
 //lcd.print(".");
 //lcd.print(dht_dat[3], DEC);
 lcd.println(" G Celsius  ");
 delay(800);
 delay(200);

        break;

     case 1:

        Serial.println("Error 1: DHT start condition 1 not met.");

        break;

     case 2:

        Serial.println("Error 2: DHT start condition 2 not met.");

        break;

     case 3:

        Serial.println("Error 3: DHT checksum error.");

        break;

     default:

        Serial.println("Error: Unrecognized code encountered.");

        break;

      }

  delay(800);
  
  
  
  
  
  
  
  // Lee el valor desde el sensor
    tempC = analogRead(tempPin); 

    // Convierte el valor a temperatura
    tempC = ((5.0 * tempC * 100.0)/1024.0)+2.5;
   lcd.setCursor(0,0); //Start at character 4 on line 0
  
  lcd.print("Temperatura Agua    ");
  delay(800);
  lcd.setCursor(0,1);
  lcd.print(tempC);
  lcd.print(" G Celsius "); // Print text on second line
  delay(1000);  
  
   print_time();
  delay(800);
  
  
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print(buf);
 
 
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print(hora);
  
   Serial.println(buf);
   Serial.println(hora);
  
  delay (1000);
 // Serial.println(day);
  {
    // when characters arrive over the serial port...
    if (Serial.available()) {
      // wait a bit for the entire message to arrive
      delay(100);
      // clear the screen
      //lcd.clear();
      // read all the available characters
      while (Serial.available() > 0) {
        // display each character to the LCD
        //lcd.write(Serial.read());
      }
    }
  }
  

}/* --(end main loop )-- */

void InitDHT(){

   pinMode(dht_dpin,OUTPUT);

        digitalWrite(dht_dpin,HIGH);

}

 

void ReadDHT(){

bGlobalErr=0;

byte dht_in;

byte i;

digitalWrite(dht_dpin,LOW);

delay(20);

 

digitalWrite(dht_dpin,HIGH);

delayMicroseconds(40);

pinMode(dht_dpin,INPUT);

//delayMicroseconds(40);

dht_in=digitalRead(dht_dpin);

 

if(dht_in){

   bGlobalErr=1;

   return;

   }

delayMicroseconds(80);

dht_in=digitalRead(dht_dpin);

 

if(!dht_in){

   bGlobalErr=2;

   return;

   }

delayMicroseconds(80);

for (i=0; i<5; i++)

   dht_dat[i] = read_dht_dat();

pinMode(dht_dpin,OUTPUT);

digitalWrite(dht_dpin,HIGH);

byte dht_check_sum =

       dht_dat[0]+dht_dat[1]+dht_dat[2]+dht_dat[3];

if(dht_dat[4]!= dht_check_sum)

   {bGlobalErr=3;}

};

 

byte read_dht_dat(){

  byte i = 0;

  byte result=0;

  for(i=0; i< 8; i++){

      while(digitalRead(dht_dpin)==LOW);

      delayMicroseconds(30);

      if (digitalRead(dht_dpin)==HIGH)

     result |=(1<<(7-i));

    while (digitalRead(dht_dpin)==HIGH);

    }

  return result;

}


/* ( THE END ) */

