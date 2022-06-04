#include <Servo.h>

#include "Ticker.h"
#include "Tween.h"

#define TICK_INTERVAL_MILLIS 33 // ~ 30fps
// #define TICK_INTERVAL_MILLIS 1000 // ~ 1fps
#define HEAD_SERVO_PIN 10

Ticker ticker(TICK_INTERVAL_MILLIS);
Servo headServo;
Tween p1 = Tween();

int lastVal;

void setup() {
  // while(!Serial) {};
  Serial.begin(9600);
  // delay(3000);
  // Serial.println("SETUP");

  // put your setup code here, to run once:
  headServo.attach(HEAD_SERVO_PIN);
  headServo.write(1500);
  delay(30);

  p1.update(millis());
  p1.begin(p1.IN_OUT_EXP, 1500, 2000, 2000, 1000);
  p1.push(p1.IN_OUT_EXP, 2000, 700, 1700);
  p1.push(p1.IN_OUT_EXP, 700, 1500, 1000);
  p1.push(p1.IN_OUT_EXP, 1500, 700, 1000);
  p1.push(p1.IN_OUT_EXP, 700, 1500, 1000);
}

void loop() {
  ticker.tick();
  int time = millis();
  int preTick = p1.value();
  p1.update(time);
  if (p1.value() != lastVal) {
    lastVal = p1.value();
    headServo.writeMicroseconds(p1.value());
  }
}
