/**********
morse.ino
**********/

#include <PS2Keyboard.h>
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

const int DataPin = 8;
const int IRQpin =  2;

PS2Keyboard keyboard;

void setup() {
delay(1000);
lcd.begin(20,4);         // initialize the lcd for 20 chars 4 lines, turn on backlight

 for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on  

lcd.setCursor(3,0); //Start at character 4 on line 0
  lcd.print("Hola, CA1CVI");
  delay(1000);
  lcd.setCursor(2,1);
  lcd.print("Morse En-Decoder");
  delay(1000);  
  lcd.setCursor(0,2);
  lcd.print("Inicializando...");
  lcd.setCursor(0,3);
  delay(2000);   
  lcd.print("http://www.ce1rlp.cl");
  delay(8000);


keyboard.begin(DataPin, IRQpin);
}


void loop() {
if (keyboard.available()) {

char c = keyboard.read();

if (c == 'a') {
p();l();
} else if (c == 'b') {
l();p();p();p();
} else if (c == 'c') {
l();p();l();p();
} else if (c == 'd') {
l();p();p();
} else if (c == 'e') {
p();
} else if (c == 'f') {
p();p();l();p();
} else if (c == 'g') {
l();l();p();
} else if (c == 'h') {
p();p();p();p();
} else if (c == 'i') {
p();p();
} else if (c == 'j') {
p();l();l();l();
} else if (c == 'k') {
l();p();l();
} else if (c == 'l') {
p();l();p();p();
} else if (c == 'm') {
l();l();
} else if (c == 'n') {
l();p();
} else if (c == 'o') {
l();l();l();
} else if (c == 'p') {
p();l();l();p();
} else if (c == 'q') {
l();l();p();l();
} else if (c == 'r') {
p();l();p();
} else if (c == 's') {
p();p();p();
} else if (c == 't') {
l();
} else if (c == 'u') {
p();p();l();
} else if (c == 'v') {
p();p();p();l();
} else if (c == 'w') {
p();l();l();
} else if (c == 'x') {
l();p();p();l();
} else if (c == 'y') {
l();p();l();l();
} else if (c == 'z') {
l();l();p();p();
} else if (c == '1') {
p();l();l();l();l();
} else if (c == '2') {
p();p();l();l();l();
} else if (c == '3') {
p();p();p();l();l();
} else if (c == '4') {
p();p();p();p();l();
} else if (c == '5') {
p();p();p();p();p();
} else if (c == '6') {
l();p();p();p();p();
} else if (c == '7') {
l();l();p();p();p();
} else if (c == '8') {
l();l();l();p();p();
} else if (c == '9') {
l();l();l();l();p();
} else if (c == '0') {
l();l();l();l();l();
} else if (c == ' ') {
pausa();
} else {
tone(4, 300, 250); //error tone
}
}
}

void p(){            //dot
  digitalWrite(12, HIGH);
  tone(4, 700);
  delay(250);
  digitalWrite(12, LOW);
  noTone(4);
  delay(250);
}

void l(){            //dash
  digitalWrite(12, HIGH);
  tone(4, 700);
  delay(750);
  digitalWrite(12,LOW);
  noTone(4);
  delay(250);
}

void pausa(){         //pause between two letters
  delay(1750);
}

