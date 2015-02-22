/*
  Programa para controlar un LED RGB con arduino.
  Usando las salidas PWM se puede controlar la intensidad de cada color para hacer las mezclas.
  Se hacen dos funciones:
    rgbon(): Muestra los 3 colores principales uno despues de otro (rojo, verde y azul)
    colors(): Permite elegir entre tres colores (amarillo (y), narajno (o) o rosado (p)) 
              usando sus siglas en ingles
    
  Materiales:
  1 Arduino UNO Rev3
  1 LED RGB de 4 patas catodo comun
  3 resistencias de 220[ohm]
  cables de conexion
  
  Autor: Arduino UTFSM
  Fecha: 22 Mayo 2014
*/

/*-----Declaracion de variables para cada color R G B-----*/
int rled = 11; // Pin PWN 11 para led rojo
int bled = 10; // Pin PWM 10 para led azul
int gled = 9;  // Pin PWM 9  para led verde

/*----Declaracion de variables auxiliares-----*/
int i; // Variable para ciclos repetitivos
int repeat = 5; // Variables para cantidad limite de repeticiones


void setup() {
/*----- Se inicializan pines PWM como salida*/  
  pinMode(rled, OUTPUT);
  pinMode(bled, OUTPUT);
  pinMode(gled, OUTPUT);
}

void loop() {
  
 for(i=0; i<repeat; i++) //Se repite la ejecucion de la funcion rgbon() "repeat" veces
  	rgbon();
 delay(1000); //Se espera 1 segundo 
 colors('y'); //Se enciende el LED en color amarillo (y de yellow)
 delay(1000);
 colors('o'); //Se enciende el LED en color naranko (o de orange)	
 delay(1000);
 colors('p'); //Se enciende el LED en color rosado (p de pink)
 delay(1000); 
}

/*-----Funcion para mostrar colores principales cada 500 ms-----*/
void rgbon(){
  analogWrite(rled,255); // Se enciende color rojo
  delay(500);            // Se esperan 500 ms
  analogWrite(rled,0);   // Se apaga color rojo 
  analogWrite(bled,255); // Se enciende color azul
  delay(500);            // Se esperan 500 ms
  analogWrite(bled,0);   // Se apaga color azul
  analogWrite(gled,255); // Se enciende color verde
  delay(500);            // Se esperan 500 ms
  analogWrite(gled,0);   // Se apaga colo verde
}

/*-----Funcion que permite escoger entre color amarillo, naranjo o rosado-----*/
void colors(char color){ //La funcion recibe un parametro que se guarda en variable color
  
  switch(color){ //Se compara variable color con dato guardado
    case 'y': analogWrite(rled,255); // Si color == 'y' se enciende color amarillo
    	      analogWrite(gled,255); // Mezclando r = 255 / g = 255 / b = 0
    	      analogWrite(bled,0);
    break;
    case 'o': analogWrite(rled,255); // Si color == 'o' se enciende color naranjo
    	      analogWrite(gled,180); // Mezclando r = 255 / g = 180 / b = 0
    	      analogWrite(bled,0);
    break;
    case 'p': analogWrite(rled,255); // Si color == 'p' se enciende color rosado
   	      analogWrite(gled,0);   // Mezclando r = 255 / g = 0 / b = 255
    	      analogWrite(bled,255);
    break;
  } 
}
