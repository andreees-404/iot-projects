#include <Servo.h>

/* LED Variables  */
int ledRojo = 3;
int ledVerde = 6;
int ledAzul = 5;
int piezo = 12;
Servo servomotor;

int button = 7;
int flag = 0;

/*
  Ultrasonic Sensor HC-SR04
@var echo
  Pin que recibe las señales
  
@var trig
  Pin que envía las señales
*/
const int trig = 8;
const int echo = 9;
long duration;
int distance;
int buttonState = 0;

void setup()
{
  Serial.begin(9600);
  
  // Diodos LED
  pinMode(ledRojo,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  pinMode(ledAzul,OUTPUT);
  
  // Servomotor
  servomotor.attach(13);
 
  // Pines del Ultrasonic Sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
 
  // Pulsador
  pinMode(button, INPUT);
}



void loop()
{ 
  buttonState = digitalRead(button);
  // Limpiar el pin emisor
  clearTrigPin();
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  
  

  // Leer los datos que recibe el pin echo
  duration = pulseIn(echo, HIGH);

  // Calcular la distancia
  distance = duration * 0.034 /2;
  
  unlockBarrier(distance);
  	
}


/* 
  Limpiar el pin emisor
 */
void clearTrigPin(){
  digitalWrite(trig, LOW);
  delay(50);
}


/*
  Imprimir la distancia
  
  @param _distance
  	Distancia entre el objeto y el sensor
*/
void unlockBarrier(int _distance){
  Serial.print("Distance: ");
  Serial.print(_distance);
  
  
  if(_distance < 100){
    
    if(digitalRead(button) == HIGH){
    	// Girar el motor en 90°
    servomotor.write(90);

    // Encender el LED verde
    analogWrite(ledRojo,0);
    analogWrite(ledVerde, 255);
    analogWrite(ledAzul,0);
    // Secuencia piezo
    for(int i = 0; i < 3; i++){
      noTone(piezo);    
      delay(250);
      tone(piezo, 1000);
    }	
    } else {
    	noTone(piezo);
    }
    
    analogWrite(ledRojo, 0);
    analogWrite(ledVerde, 0);
    analogWrite(ledAzul, 255);
    
    
  
  }
  else {
    noTone(piezo);
    servomotor.write(0);
    
    // Encender el LED rojo
 	analogWrite(ledRojo,255);
 	analogWrite(ledVerde,0);
 	analogWrite(ledAzul,0);
 	delay(10);	
  }
}


