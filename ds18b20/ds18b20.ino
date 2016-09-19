#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 12

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup(void) {
Serial.begin(9600);
//Serial.println("Dallas Temperature IC Control Library Demo");

sensors.begin();
}

void loop(void) {
//Serial.print("Conectando...");
sensors.requestTemperatures();
float temp = sensors.getTempCByIndex(0);// invento mio
//Serial.println("Listo");
Serial.print("xyz123 ");
// Serial.println(sensors.getTempCByIndex(0));
Serial.println(temp);

}
