/*
  GND = GND
  VCC = 5v
  SDA = A4
  SCL = A5
*/

#include <Wire.h>
#include "MMA7660.h"
MMA7660 accelemeter;
void setup()
{
    accelemeter.init();
    Serial.begin(115200);
}
void loop()
{
float ax,ay,az;
accelemeter.getAcceleration(&ax,&ay,&az);
    Serial.println(ax);
delay(5);
}
