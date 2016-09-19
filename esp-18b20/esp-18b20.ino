
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 8  // DS18B20 pin
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);


void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    Serial.println("");
  Serial.println("");
  Serial.println("Inicializando Sistema 2");
  Serial.print("Conectando sensor ");
  Serial.println("");
  Serial.println("");

}

void loop() {
  // put your main code here, to run repeatedly:
    float temp;
    DS18B20.requestTemperatures(); 
    temp = DS18B20.getTempCByIndex(0);
    Serial.print("Temperature: ");
    Serial.println(temp);
}
