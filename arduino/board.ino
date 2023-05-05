#include <LiquidCrystal.h>

// Define los pines utilizados para el LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define los pines utilizados para el sensor HC-SR04
const int trigPin = 7;
const int echoPin = 6;

// Define el pin analógico utilizado para el sensor de temperatura
const int sensorPin = A0;

// Define el pin utilizado para el motor
const int motorPin = 9;

void setup() {
  // Inicializa el LCD
  lcd.begin(16, 2);

  // Configura los pines del sensor HC-SR04 como entrada/salida
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Configura el pin del motor como salida
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // Lee el valor del sensor de temperatura
  int sensorValue = analogRead(sensorPin);

  // Convierte el valor leído del sensor a una temperatura en grados Celsius
  float temperature = (sensorValue * 5.0 / 1024.0 - 0.5) * 100.0;

  // Muestra la temperatura en el LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");

  // Verifica si la temperatura es mayor o igual que 21 grados centígrados y hay una persona en el área de detección del sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float distance = pulseIn(echoPin, HIGH) * 0.034 / 2.0;
  if (temperature >= 21 && distance <= 300) {
    // Ajusta la velocidad del motor según la temperatura leída del sensor
    int speed = map(sensorValue, 0, 1023, 0, 255);
    analogWrite(motorPin,speed);

    // Muestra la velocidad del motor en el LCD
    lcd.setCursor(0, 1);
    lcd.print("Motor Speed: ");
    lcd.print(speed);
  } else {
    // Si la temperatura es menor que 21 grados centígrados o no hay una persona en el área de detección del sensor, apaga el motor
    analogWrite(motorPin, 0);

    // Muestra un mensaje en la pantalla LCD indicando que el motor está apagado
    lcd.setCursor(0, 1);
    lcd.print("Motor apagado");
  }

  // Espera un momento antes de leer el valor del sensor de temperatura y del sensor HC-SR04 nuevamente
  delay(1000);
}