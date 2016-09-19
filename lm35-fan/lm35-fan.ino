float temp;
int tempPin = 7;
int fan =2;
int tempMin = 25;
int  fanSpeed = 0;
int  fanspeed = 0;
void setup()


{

Serial.begin(9600);
pinMode(2, OUTPUT);
pinMode(3, INPUT);
//digitalWrite(2, LOW); 

}

void loop()

{

temp = analogRead(tempPin);
fanSpeed=pulseIn(3,HIGH);
temp = temp * 0.48828125;

Serial.print("TEMPERATURA = ");

Serial.print(temp);

Serial.print("*C");


Serial.println();
 if(temp < tempMin) {   // if temp is lower than minimum temp
       fanSpeed = 0;      // fan is not spinning
       digitalWrite(2, HIGH); 
 }
 
delay(1000);


}
