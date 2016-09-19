#include <ESP8266WiFi.h>
unsigned char buffer[300];
unsigned char i=0, ok=0, j=0;
String data="";
char input;

//Se configura el puero serie a 9600 baudios
void setup(){
Serial.begin(9600);
}

void loop(){
//Si se recibió un dato entra
if (Serial.available()>0){
input=Serial.read(); //Leo dato
if(input=='$'){
data=="";
j=1;
}
if(input!='#'){
  
buffer[i]=input;
data+=input;
//Serial.println(data);
buffer[i+1]='\0';

i++;
}else ok=1;

//Si ya llego toda la trama entra aqui
if(ok==1){
//leo el buffer, proceso información y borro el buffer
//Serial.println(i);
//Serial.println(ok);
Serial.print("data= ");
Serial.println(data);
Serial.print(data.length());
Serial.println(" Caracteres");
Serial.println("J=1");
Serial.println("OK=1");
ok=0; //bajo bandera
i=0; //borro el contador
data="";
rst();
}
}
}

void rst(){
  Serial.println("programa terminado");
}

