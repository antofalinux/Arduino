/*
  Sensing the Temperature with the LM35
  Authors: Andrea Lizzi, Edoardo Scalafiotti edoardo.s@daviom.com
  This script will output the sensed temperature of the LM35 from 20 to 32°C .
*/

const int sensorPin = A0;

void setup() {
  Serial.begin(9600);

}

void loop() {
  int sensorVal = analogRead(sensorPin);
  float voltage = (sensorVal/1024.0)*5.0;

  float temperature = (voltage-.5)*100;
  String a;
  char temp[10];
  dtostrf(temperature, 2, 1, temp);
  String tempAsString = String(temp);
  Serial.println("xyz123 " + tempAsString);
    
  delay(200);
}
