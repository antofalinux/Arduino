
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

/* Create buffers */
char buf[50];
char day[50];
char hora[50];

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


}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  
  // Lee el valor desde el sensor
    tempC = analogRead(tempPin); 

    // Convierte el valor a temperatura
    tempC = (5.0 * tempC * 100.0)/1024.0;
   lcd.setCursor(0,0); //Start at character 4 on line 0
  
  lcd.print("Temperatura     ");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print(tempC);
  lcd.print(" G Celsius "); // Print text on second line
  delay(1000);  
  
   print_time();
  delay(1000);
  
  
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
  
  delay (2000);
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


/* ( THE END ) */

