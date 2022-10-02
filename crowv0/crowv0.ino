#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <ezButton.h>

#include "Ticker.h"
#include "Tween.h"
#include "Pose.h"

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

// FINE TUNE MODE STUFF


// BUTTON STUFF
#define BREAD_BUTTON_PIN 2
#define POT_PIN 3
Adafruit_NeoPixel onboard(1, PIN_NEOPIXEL);
ezButton bbutt(BREAD_BUTTON_PIN);

void setup() {
  Serial.begin(9600);
  // while(!Serial) {};

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

// BUTTON STUFF
  bbutt.setDebounceTime(100);
  onboard.begin();
  onboard.setBrightness(10);
  onboard.setPixelColor(0, onboard.Color(255, 0, 255));
  onboard.show();
}

void loop() {
  ticker.tick();
  int time = millis();
  int preTick = p1.value();
  p1.update(time);
  p2.update(time);

  // BUTTON STUFF
  bbutt.loop();
  if (bbutt.getState() == LOW) { // low == pushed
    onboard.clear();
    onboard.setPixelColor(0, onboard.Color(255, 0, 255));
    onboard.show();
    neckServo.writeMicroseconds(1000);
  }
  else {
    onboard.clear();
    onboard.setPixelColor(0, onboard.Color(0, 255, 255));
    onboard.show();
    neckServo.writeMicroseconds(1500);
  }
  double potVal = (double)analogRead(POT_PIN)/1000.0;
  int servoVal = 800 + (int)(potVal * 1400.0);
  if (servoVal < 800) {
    Serial.println("HIT BOTTOM");
    servoVal = 800;
  }
  if (servoVal > 2200) {
    Serial.println("HIT TOP");
    servoVal = 2200;
  }
  neckServo.writeMicroseconds(servoVal);
  // END BUTTON STUFF

  // if (p1.value() != lastVal) {
  //   lastVal = p1.value();
  //   bodyServo.writeMicroseconds(p1.value());
  // }

  //
  // neckServo.writeMicroseconds(p2.value());
}
