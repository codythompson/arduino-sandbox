#include "Servo.h"

#include "EasedPath.h"

#define TICK_INTERVAL_MILLIS 33 // ~ 30fps
//#define TICK_INTERVAL_MILLIS 1000 // ~ 1fps
#define HEAD_SERVO_PIN 10

Servo headServo;
EasedPath p1 = EasedPath();

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  headServo.attach(HEAD_SERVO_PIN);
  headServo.write(1500);
  delay(1000);
}

void loop() {
  int time = millis();
  p1.update(time);
  if (p1.isActive()) {
    headServo.writeMicroseconds(p1.value());
  }

  if (!p1.hasCompleted() && !p1.isActive() && time > 3000) {
    Serial.println("
    p1.begin(1500, 2000, 5000);
  }

  while (millis() - time < TICK_INTERVAL_MILLIS); // delay by TICK_INTERVAL 
}
