#include <Servo.h>

#include "Ticker.h"
#include "Tween.h"

#define CROW_BODY_MAX 850
// #define CROW_BODY_MAX 1000 // actual max
#define CROW_BODY_MIN 700
#define CROW_BODY_HALF CROW_BODY_MAX-CROW_BODY_MIN
#define CROW_BODY_MID CROW_BODY_MIN + CROW_BODY_HALF

#define TICK_INTERVAL_MILLIS 18 // ~ 60fps
// #define TICK_INTERVAL_MILLIS 34 // ~ 30fps
// #define TICK_INTERVAL_MILLIS 1000 // ~ 1fps
#define BODY_SERVO_PIN 10
#define NECK_SERVO_PIN 1

Ticker ticker(TICK_INTERVAL_MILLIS);
Servo bodyServo;
Servo neckServo;
Tween p1 = Tween();
Tween p2 = Tween();

int lastVal;

void setup() {
  // Serial.begin(9600);
  // while(!Serial) {};
  // delay(3000);

  // put your setup code here, to run once:
  bodyServo.writeMicroseconds(CROW_BODY_MIN+50);
  bodyServo.attach(BODY_SERVO_PIN);
  neckServo.attach(NECK_SERVO_PIN);
  delay(30);
  neckServo.writeMicroseconds(1500);

  p1.update(millis());
  p2.update(millis());
  // p1.begin(p1.LINEAR, 1500, 700, 5000, 1000);
  // p1.begin(p1.IN_OUT_QUAD, CROW_BODY_MIN, CROW_BODY_MID, 3000);
  // p1.push(p1.IN_OUT_QUAD, CROW_BODY_MID, CROW_BODY_MIN, 1000);

  p1.begin(p1.LINEAR, CROW_BODY_MIN+50, CROW_BODY_MIN, 250);
  p1.push(p1.LINEAR, CROW_BODY_MIN, CROW_BODY_MIN+50, 250, 1000);
  p1.push(p1.LINEAR, CROW_BODY_MIN+50, CROW_BODY_MIN, 250);
  p1.push(p1.LINEAR, CROW_BODY_MIN, CROW_BODY_MIN+50, 250);
  p1.push(p1.LINEAR, CROW_BODY_MIN+50, CROW_BODY_MIN, 250);
  p1.push(p1.LINEAR, CROW_BODY_MIN, CROW_BODY_MIN+50, 250);
  p1.push(p1.LINEAR, CROW_BODY_MIN+50, CROW_BODY_MIN, 250);
  p1.push(p1.LINEAR, CROW_BODY_MIN, CROW_BODY_MIN+50, 250);
  p1.push(p1.LINEAR, CROW_BODY_MIN+50, CROW_BODY_MIN, 250);
  p1.push(p1.LINEAR, CROW_BODY_MIN, CROW_BODY_MIN+50, 250);

  // p1.push(p1.IN_OUT_QUAD, CROW_BODY_MIN+50, CROW_BODY_MIN, 3000);

  // p2.begin(p1.IN_OUT_QUAD, 1500, 1400, 250);
  // p2.push(p1.IN_OUT_QUAD, 1600, 1400, 500);
  // p2.push(p1.IN_OUT_QUAD, 1400, 1600, 500);
  // p2.push(p1.IN_OUT_QUAD, 1600, 1400, 500);
  // p2.push(p1.IN_OUT_QUAD, 1400, 1600, 500);
  // p2.push(p1.IN_OUT_QUAD, 1500, 1500, 250);
}

void loop() {
  ticker.tick();
  int time = millis();
  int preTick = p1.value();
  p1.update(time);
  p2.update(time);
  if (p1.value() != lastVal) {
    lastVal = p1.value();
    bodyServo.writeMicroseconds(p1.value());
    Serial.println(lastVal);
  }

  //
  // neckServo.writeMicroseconds(p2.value());
}
