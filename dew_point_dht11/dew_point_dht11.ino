        double celsius;
        double humidity;



void setup()
{
    Serial.begin(9600);
}



void loop()
{
    //    celsius=24;
    //    humidity=65;

	double a = 17.271;
	double b = 237.7;
	double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
	double Td = (b * temp) / (a - temp);
	//return Td;

Serial.print("Temperatura: ");
Serial.println(celsius);
Serial.print("Humedad: ");
Serial.println(humidity);
Serial.print("Punto Rocio: ");
Serial.println(Td);
delay (500);
}

