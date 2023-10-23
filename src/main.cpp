#include <Arduino.h>

int semaforos[3][3] = {{13, 12, 14}, {27, 26, 25}, {33, 32, 2}};
int cantLed = 3;
int delayTime = 1000; 
int delayParpadeo = 500;
int parpadeo = 1;
int ledParpadeo = 0;
 
String leds[3] = {"v", "a", "r"};
String encender = "E";
String parar = "P";


// Semaforo reflejo
void encenderSemaforo(int semaforos[3][3], int tiempoRetardo){
    for(int j = 0; j < cantLed; j++){
        for(int i = 0; i < cantLed; i++){
            digitalWrite(semaforos[i][j], HIGH);
        }
        Serial.println(leds[j] + "-1");
        delay(tiempoRetardo);
        if(j ==  1){
            parpadeo = 1;


            while(parpadeo < 3 ){
                for(int i = 0; i < cantLed; i++){
                    digitalWrite(semaforos[i][j], LOW);
                }
                Serial.println(leds[j] + "-0"); 
                delay(delayParpadeo);
                for(int i = 0; i < cantLed; i++){
                    digitalWrite(semaforos[i][j], HIGH);
                }
                Serial.println(leds[j] + "-1"); 
                delay(delayParpadeo);
                parpadeo++;
            }


        }
        for(int i = 0; i < cantLed; i++){
            digitalWrite(semaforos[i][j], LOW);
        }
        Serial.println(leds[j] + "-0"); 
    }
}



void detenerSemaforo(){
  for(int i = 0; i < cantLed; i++){
    for(int j = 0; j < cantLed; j++){
      digitalWrite(semaforos[i][j], LOW);
    }
  }
}

void setup(){

  Serial.begin(9600);
  for(int i = 0; i < cantLed; i++){
    for(int j = 0; j < cantLed; j++){
      pinMode(semaforos[i][j], OUTPUT);
    }
  }
}

void loop() {
  if (Serial.available() > 0) {
    int  consolaRead = Serial.read();

    while (consolaRead == encender.charAt(0))
    {      
      encenderSemaforo(semaforos, delayTime);

      if (consolaRead == parar.charAt(0)) {
      detenerSemaforo();
    }
    }

  }
}




// ! Semaforo en serie
//  void encenderSemaforo(int semaforos[3][3], int tiempoRetardo){

//      for(int i = 0; i < cantLed; i++){
//        for(int j = 0; j < cantLed; j++){
//          int primerElemento = semaforos[i][0];
//          digitalWrite(semaforos[i][j], HIGH);
//          delay(tiempoRetardo);
//          if(j == 0){
//            parpadeo = 0;

//            while(parpadeo < 3){
//              digitalWrite(primerElemento, LOW);
//              delay(delayParpadeo);
//              digitalWrite(primerElemento, HIGH);
//              delay(delayParpadeo);
//              parpadeo++;
//            }
//          }
//          digitalWrite(semaforos[i][j], LOW);
//        }
//      }
//  }


