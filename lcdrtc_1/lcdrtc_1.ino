#include <DS1302.h>

#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
#include <stdio.h>
#include <string.h>
#include <DS1302.h>


// ds1302 library can be found here : http://www.henningkarlsen.com/electronics
//
// DS1302: RST / CE pin - Arduino Digital 12
// I/O / DAT pin - Arduino Digital 11
// SCLK pin - Arduino Digital 10
// LCD: DB7 - Arduino Digital 7
// DB6 - Arduino Digital 6
// DB5 - Arduino Digital 5
// DB4 - Arduino Digital 4
// RS - Arduino Digital 8
// E - Arduino Digital 9
// RW to ground?


//seems it is better to NOT plug VCC when setting the clock...




// Init the DS1302
//DS1302(ce, data, clock);
DS1302 rtc(5,6,7);

// Init the LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address


//void set_time() {
//rtc.setDOW(SUNDAY); // Set Day-of-Week to FRIDAY
//rtc.setTime(19, 2, 0); // Set the time to 12:00:00 (24hr format)
//rtc.setDate(13, 1, 2013); // Set the date to August 6th, 2010
//}

void setup()
{
Serial.begin(9600);
// Set the clock to run-mode, and disable the write protection
//rtc.halt(false);
//rtc.writeProtect(false);
// Setup LCD to 16x2 characters
lcd.begin(16, 2);

// The following lines can be commented out to use the values already stored in the DS1302
//set_time();
}

void loop()
{
// Display time centered on the upper line
lcd.setCursor(4, 0);
lcd.print(rtc.getTimeStr());

// Display abbreviated Day-of-Week in the lower left corner
lcd.setCursor(0, 1);
lcd.print(rtc.getDOWStr(FORMAT_SHORT));

// Display date in the lower right corner
lcd.setCursor(6, 1);
lcd.print(rtc.getDateStr());

Serial.print(rtc.getTimeStr());
Serial.print(" ");
Serial.print(rtc.getDOWStr(FORMAT_SHORT));
Serial.print(" ");
Serial.println(rtc.getDateStr());

// Wait one second before repeating :) 
delay (1000);
}
