
#include <LiquidCrystal.h>
#include <Servo.h>

// LCD connections: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Servo motor
Servo gateServo;

// Parking IR sensors
const int parkingSensor1 = 2;
const int parkingSensor2 = 3;
const int parkingSensor3 = 4;
const int parkingSensor4 = 5;

// Gate IR sensor
const int gateSensor = 6;

// Street light control
const int streetLight1 = A0;
const int streetLight2 = A1;
const int streetLight3 = A2;

// Gate servo pin
const int servoPin = 13;

// Number of parking slots
const int totalSlots = 4;

void setup() {
  pinMode(parkingSensor1, INPUT);
  pinMode(parkingSensor2, INPUT);
  pinMode(parkingSensor3, INPUT);
  pinMode(parkingSensor4, INPUT);

  pinMode(gateSensor, INPUT);

  pinMode(streetLight1, OUTPUT);
  pinMode(streetLight2, OUTPUT);
  pinMode(streetLight3, OUTPUT);

  gateServo.attach(servoPin);
  gateServo.write(0);

  lcd.begin(16, 2);
  lcd.print("Smart Parking");
  delay(2000);
  lcd.clear();
}

void loop() {
  int occupiedSlots = 0;

  // Count occupied parking slots
  if (digitalRead(parkingSensor1) == LOW) {
    occupiedSlots++;
  }

  if (digitalRead(parkingSensor2) == LOW) {
    occupiedSlots++;
  }

  if (digitalRead(parkingSensor3) == LOW) {
    occupiedSlots++;
  }

  if (digitalRead(parkingSensor4) == LOW) {
    occupiedSlots++;
  }

  int availableSlots = totalSlots - occupiedSlots;

  // Display parking status
  lcd.setCursor(0, 0);
  lcd.print("Available: ");
  lcd.print(availableSlots);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  lcd.print("Occupied: ");
  lcd.print(occupiedSlots);
  lcd.print("   ");

  // Open gate when a vehicle is detected
  if (digitalRead(gateSensor) == LOW && availableSlots > 0) {
    gateServo.write(90);
    delay(3000);
    gateServo.write(0);
  }

  // Street light automation
  // Turn on LEDs when vehicle/motion is detected
  if (digitalRead(gateSensor) == LOW) {
    digitalWrite(streetLight1, HIGH);
    digitalWrite(streetLight2, HIGH);
    digitalWrite(streetLight3, HIGH);
  } else {
    digitalWrite(streetLight1, LOW);
    digitalWrite(streetLight2, LOW);
    digitalWrite(streetLight3, LOW);
  }

  delay(500);
}
