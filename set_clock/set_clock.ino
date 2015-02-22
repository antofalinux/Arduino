/*
Example sketch for interfacing with the DS1302 timekeeping chip.

Copyright (c) 2009, Matt Sparks
All rights reserved.

http://quadpoint.org/projects/arduino-ds1302
*/
#include <stdio.h>
#include <string.h>
#include <DS1302.h>

/* Set the appropriate digital I/O pin connections */
uint8_t CE_PIN   = 5;
uint8_t IO_PIN   = 6;
uint8_t SCLK_PIN = 7;

/* Create buffers */
char buf[50];
char day[10];

/* Create a DS1302 object */
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);


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
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day,
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  /* Print the formatted string to serial so we can see the time */
  Serial.println(buf);
  Serial.print(t.date);
  Serial.print("-");
  Serial.print(t.mon);
  Serial.print("-");
  Serial.println(t.yr);
}


void setup()
{
  Serial.begin(9600);

  /* Initialize a new chip by turning off write protection and clearing the
     clock halt flag. These methods needn't always be called. See the DS1302
     datasheet for details. */
//  rtc.write_protect(false);
//  rtc.halt(false);

  /* Make a new time object to set the date and time */
  /*   Tuesday, May 19, 2009 at 21:16:37.            */
//  Time t(2014, 7, 6, 16, 23, 00, 1);

  /* Set the time and date on the chip */
//  rtc.time(t);
}


/* Loop and print the time every second */
void loop()
{
  print_time();
  delay(1000);
}
