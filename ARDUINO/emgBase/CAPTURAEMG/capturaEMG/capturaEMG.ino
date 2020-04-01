#include <ESP8266WiFi.h>
/*Pines Analogos*/
const int pinSignalEMG = A0;
/*Pines Digitales*/
const int pinRed = D5;
const int pinGreen = D6;
const int pinBlue = D7;



void setup()
{
  Serial.begin(9600);

  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
}

void loop()
{
  /*Capturamos señal analoga del sensor*/
  int  EMG = analogRead(pinSignalEMG);

  /*Divide el máximo valor de voltage entre el máximo valor del sensor y lo multiplica por el valor de la señal EMG*/
  float voltageA0 = (float)(EMG * (5.0 / 1023.0));


  if (voltageA0 > 0.10 && voltageA0 < 0.20)
  {
    setLed(1);
  }
  if (voltageA0 > 0.20 && voltageA0 < 0.40)
  {
    setLed(2);
  }
  if (voltageA0 > 0.40 && voltageA0 < 0.60)
  {
    setLed(3);
  }
  if (voltageA0 > 0.60 && voltageA0 < 1)
  {
    setLed(4);
  }

  if (voltageA0 <= 0.10 )
  {
    setLed(0);
  }

  Serial.println("Voltage");
  Serial.println(voltageA0);
  Serial.println("EMG pura");
  Serial.println(EMG);

delay(5);

}


void setLed(int option)
{
  Serial.println("SetLed");
  Serial.println(option);


/*Recordar que el Led es Anodo Comun, su tabla de verdad es inversa*/
  switch (option) {
    case 0:
      // Blanco
      digitalWrite(pinRed, LOW);
      digitalWrite(pinGreen, LOW);
      digitalWrite(pinBlue, LOW);

      break;
    case 1:
      // Azul
      digitalWrite(pinRed, HIGH);
      digitalWrite(pinGreen, HIGH);
      digitalWrite(pinBlue, LOW);


      break;
    case 2:
      // Rojo
      digitalWrite(pinRed, LOW);
      digitalWrite(pinGreen, HIGH);
      digitalWrite(pinBlue, HIGH);


      break;
    case 3:
      //Violeta
      digitalWrite(pinRed, LOW);
      digitalWrite(pinGreen, HIGH);
      digitalWrite(pinBlue, LOW);


      break;
    case 4:
      //Amarillo
      digitalWrite(pinRed, LOW);
      digitalWrite(pinGreen, LOW);
      digitalWrite(pinBlue, HIGH);


      break;


  }

}
