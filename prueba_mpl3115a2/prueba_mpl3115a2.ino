#include <ESP8266WiFi.h>
#include <Wire.h> //I2C needed for sensors
#include "MPL3115A2.h" //Pressure sensor
MPL3115A2 myPressure; //Create an instance of the pressure sensor
float pressure;
float presion;
float inhg;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  
  myPressure.begin(); // Get sensor online
  myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
  myPressure.setOversampleRate(128); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags 
  myPressure.setModeActive(); // Go to active mode and start measuring!


  delay(100);
  Serial.println();
  Serial.println();
  Serial.println("Inicializando Sistema ");
}

void loop() {
  // put your main code here, to run repeatedly:
  const int station_elevation_m = 87; //Accurate for the roof on my house
    pressure = myPressure.readPressure();
  Serial.print("Pressure: ");
  Serial.println(pressure);
  float presion=pressure *=0.000295301;
  Serial.print("Presion: ");
  Serial.println(presion);
delay (500);

}
