/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>
#include <ezButton.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
ezButton button(2);

int ledPin = 7;

boolean servoOn = true;

const int stepSize = 40;
const int minPos = 1040;
const int maxPos = 1960;
int pos = ((maxPos - minPos)/2)+minPos;    // variable to store the servo position
int posTarget = minPos;

void setup() {
  
//  myservo.writeMicroseconds(pos);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
 pinMode(ledPin, OUTPUT); 
 Serial.begin(9600);
}

void step() {
  if (!servoOn) {
//    Serial.println("NOT ON");
//    myservo.write(pos);
    delay(500);
    return;
  }
  int delta = posTarget - pos;
  Serial.print(pos);
  Serial.print(" - ");
  Serial.print(posTarget);
  Serial.print(" D: ");
  Serial.println(delta);
  if (abs(delta) <= stepSize) {
    pos = posTarget;
    if (posTarget == maxPos) {
      posTarget = minPos;
    }
    else {
      posTarget = maxPos;
    }
    Serial.println("----");
    Serial.println(delta);
    Serial.println(posTarget);
    Serial.println(pos);
    Serial.println("END O LINE");
  }
  else if (delta > 0) {
//    Serial.print("plus");
    pos += stepSize;
//    Serial.println(pos);
  }
  else {
//    Serial.print("minus");
    pos -= stepSize;
//    Serial.println(delta < 0.0f);
  }
  
  if (pos < minPos || pos > maxPos) {
    Serial.print("BAD BAD NOT GOOD: ");
    Serial.println(pos);
    // BAD BAD NOT GOOD
    digitalWrite(ledPin, LOW);
    delay(500);
    digitalWrite(ledPin, HIGH);
    delay(500);
//    servoOn = false;
  }
  else {
//    Serial.print("GOOD: ");
//    Serial.println(pos);
    myservo.writeMicroseconds(pos);
  }
}

void loop() {
  button.loop();
  servoOn = !button.getState();
  step();
  delay(30);
}
