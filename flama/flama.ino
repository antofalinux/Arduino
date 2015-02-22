#include <core.h>

const int analogInPin =0;  // puerto A0 para medir flama

int sensorValue = 0; // value read from the pot
int count1;

void setup() {

}

void loop() {

count1++;
// read the analog in value:
sensorValue = analogRead(analogInPin);

if(count1==3000)
{
count1=0;

printf(“sensor=%d\n”, sensorValue);
}
}
