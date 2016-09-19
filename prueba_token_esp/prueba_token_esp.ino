//#include <ESP8266WiFi.h>


// Example input=3:255&4:0&8:180
void setup() {
  Serial.begin(9600); // Opens serial port, sets data rate to 9600 bit/s.
    Serial.println("Inicializando Sistema ");
  Serial.println("Conectando ");
  Serial.println("");
}

void loop() {
#define INPUT_SIZE 300
int valuePar;
double portId ;
  // Get next command from Serial
  if (Serial.available())
  {
    char input[INPUT_SIZE + 1];
    byte size = Serial.readBytes(input, INPUT_SIZE);

    // Add the final 0 to end the string
    input[size] = 0;

    // Read each command pair
    char* command = strtok(input, "&");
    while (command != 0)
    {
      // Split the command in two values
      char* separator = strchr(command, ':');
      if (separator != 0)
      {
        // Actually split the string in 2: replace ':' with 0
        *separator = 0;
        portId = atoi(command);
        Serial.print("temp C:");
        Serial.print(portId);
        double jota=portId/10;
        ++separator;
        valuePar = atoi(separator);
        Serial.print(", humedad:");
        Serial.println(valuePar);
        Serial.print("temp corregida C:");
        
        Serial.print(jota);

 //     double th = portId+5;  
 //      Serial.print("Temp +5: ");
 //      Serial.println(th);
       Serial.println(""); 
      float humidity=valuePar;
      double tempf=jota;
      double a = 17.271;
      double b = 237.7;
      //double temppp = (a * tempf) / (b + tempf); //borrar y dejar la que sigue
      double temppp = (a * tempf) / (b + tempf) + log(humidity*0.01);
      double Tr = (b * temppp) / (a - temppp);
      
       Tr = tempf - ((100 - humidity)/5);
       int    Td=Tr*10;
       Serial.print("Punto de Rocio: ");
       Serial.println(Tr);
              Serial.print("Punto de Rocio: ");
       Serial.println(Td);
      
       Serial.println("");


Tr=0;
Td=0;
valuePar=0;
portId=0;

      }
loop();
      
    }
  }

}
