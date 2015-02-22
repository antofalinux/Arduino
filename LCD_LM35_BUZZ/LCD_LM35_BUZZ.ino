
/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here: 
// www.4tronix.co.uk/arduino/sketches/LiquidCrystal_V1.2.1.zip
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>

/*-----( Declare Constants )-----*/
/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 16 chars 2 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

/*-----( Declare Variables )-----*/
//NONE
// Declaracion de variables
float tempC;
int tempPin = 0; // Definimos la entrada en pin A0

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);  // Used to type in characters
  pinMode(8,OUTPUT);//Set Pin Mode as output  

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
  lcd.print("CTR Acuario"); // Print text on second line
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
  
  lcd.print("Temperatura ");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print(tempC);
  lcd.print(" G Celsius "); // Print text on second line
  delay(1000);  
  
  if (tempC>31) {
    {
  unsigned char i,j;
  while(1)
  {
    for(i=0;i<80;i++) //Sound effect 1
    {
      digitalWrite(8,HIGH);//Make some sound
      delay(1);//Delay 1ms
      digitalWrite(8,LOW);//Be quiet 
      delay(1);//Delay 1ms
    }
    for(i=0;i<100;i++) //Sound effect 2
    {
      digitalWrite(8,HIGH);//Make some sound
      delay(2);//Delay 2ms
      digitalWrite(8,LOW);//Be quiet
      delay(2);//Delay 2ms
    }
  }
}  
}
  
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

