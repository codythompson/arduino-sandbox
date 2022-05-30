#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include "GyroUtil.h"

//#define SCREEN_WIDTH 128 // OLED display width, in pixels
//#define SCREEN_HEIGHT 32 // OLED display height, in pixels
//#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
//#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SERVO_MIN 700
#define SERVO_MAX 2300
const int servoRange = SERVO_MAX - SERVO_MIN;

Servo servo;

int seekingTo;
int pos = -1;
bool locked = false;
const int minDelta = 20;
const int seekSpeed = 100;

void doServo(float angle) {
  float finalAngle = 180 - (angle+90);
  int newSeekingTo = (int)round(((finalAngle/180) * servoRange) + SERVO_MIN);

  // if we haven't already hit the edge of servo range,
  // set the seek position to the edge, and set locked to true,
  // to avoid flip flopping between each edge until the gyro is back in a better angle
  if (newSeekingTo <= SERVO_MIN) {
    if (!locked) {
      locked = true;
      newSeekingTo = SERVO_MIN;
    }
    else {
      newSeekingTo = seekingTo;
    }
  }
  else if (newSeekingTo > SERVO_MAX) {
    if (!locked) {
      locked = true;
      newSeekingTo = SERVO_MAX;
    }
    else {
      newSeekingTo = seekingTo;
    }
  }
  else if (locked){
    if (abs(seekingTo-newSeekingTo) <= seekSpeed) {
      locked = false;
    }
    else {
      newSeekingTo = seekingTo; 
    }
  }
  seekingTo = newSeekingTo;

  if (pos == -1) {
    pos = seekingTo;
  }
  else {
    int delta = seekingTo - pos;
    if (abs(delta) < minDelta) {
      delay(15);
      return;
    }
    if (abs(delta) <= seekSpeed) {
      pos = seekingTo;
    }
    else if (delta < 0) {
      pos -= seekSpeed;
    }
    else {
      pos += seekSpeed;
    }
  }
  
  servo.write(pos);
  delay(15);
}

void setup(void) {
  int delayCount = 10;
  Serial.begin(9600);
  while (!Serial && delayCount > 0) {
    delayCount--;
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  //  Serial.println("Adafruit LSM6DSOX test!");
  setupGyro();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
//  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
//    Serial.println(F("SSD1306 allocation failed"));
//    for (;;); // Don't proceed, loop forever
//  }
//  Serial.println(F("initialized"));

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  //  display.display();
  //  delay(2000); // Pause for 2 seconds

  servo.attach(10);
  servo.writeMicroseconds(1500);  // set servo to mid-point

  // Clear the buffer
//  display.clearDisplay();
  //
  //  // Draw a single pixel in white
//  display.drawPixel(100, 10, SSD1306_WHITE);
//  display.display();
}

void loop() {
  //    display.loop();

  float angle, z;
  readAngle(angle);
//  Serial.print(angle); Serial.print(",");
//  Serial.println(lastZ());
////
//  display.clearDisplay();
//
//  display.setTextSize(2);             // Normal 1:1 pixel scale
//  display.setTextColor(SSD1306_WHITE);        // Draw white text
//  display.setCursor(0, 0);            // Start at top-left corner
//  display.println(angle);
//  display.setCursor(0, 16);

  doServo(angle);
//  display.display();
  Serial.print(pos);
  Serial.print(",");
  Serial.println(seekingTo);

  delay(16);
}
