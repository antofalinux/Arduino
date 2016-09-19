
//#include <LiquidCrystal.h>
#include <DS1302RTC.h>
#include <Time.h>

int speaker = 4;




// Init the DS1302
// Set pins:  CE, IO,CLK
DS1302RTC RTC(9, 8, 7);

// Optional connection for RTC module
#define DS1302_GND_PIN 1
#define DS1302_VCC_PIN 3

// Init the LCD
//   initialize the library with the numbers of the interface pins
//            lcd(RS,  E, d4, d5, d6, d7, bl, polarity)
//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup()
{
  Serial.begin(9600);


//  pinMode(8,OUTPUT);
 // pinMode(2,OUTPUT);


  pinMode(4, OUTPUT);
  digitalWrite(2,LOW);
  digitalWrite(4,LOW);

  // Setup LCD to 16x2 characters
//  lcd.begin(16,2);

  // Activate RTC module
//  digitalWrite(DS1302_GND_PIN, LOW);
//  pinMode(DS1302_GND_PIN, OUTPUT);

//  digitalWrite(DS1302_VCC_PIN, HIGH);
//  pinMode(DS1302_VCC_PIN, OUTPUT);

  Serial.println("RTC activated");

  delay(500);

//  lcd.clear();
  if (RTC.haltRTC())
    Serial.println("Clock stopped!");
  else
    Serial.println("Clock working.");

//  lcd.setCursor(0,1);
  if (RTC.writeEN())
    Serial.println("Write allowed.");
  else
    Serial.println("Write protected.");

  delay (1000);

  // Setup time library  
//  lcd.clear();
  Serial.println("RTC Sync");
  setSyncProvider(RTC.get);      // the function to get the time from the RTC
  if(timeStatus() == timeSet)
    Serial.println(" Ok!");
  else
    Serial.println(" FAIL!");

  delay ( 2000 );

//  lcd.clear();


}

void loop()
{
  tmElements_t tm;
 Serial.println(" ");
  Serial.println(" ");
  
//  lcd.setCursor(4, 0);
  Serial.print(hour());
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print("");
  Serial.print(" ");
//  lcd.setCursor(0, 1);
  Serial.print(dayShortStr(weekday()));

//  lcd.setCursor(5, 1);
  Serial.print(" ");
  Serial.print(day());
  Serial.print("/");
  Serial.print(month());
  Serial.print("/");
  Serial.print(year());
Serial.print("");
delay ( 1000 );



 // if(hour() == 17 && minute() >= 57 && minute() < 59)
  if(hour() >= 18 && hour()< 19)
  {
   // tone(speaker,1000,200);
    digitalWrite(4, HIGH);
  }
  else
  {
    digitalWrite(4, LOW);
  }





  // Warning!
  if (timeStatus() != timeSet) {
  //  lcd.setCursor(0, 1);
    Serial.println(F("RTC ERROR: SYNC!"));
  }
  delay(100);

}











