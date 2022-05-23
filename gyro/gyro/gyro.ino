#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include "GyroUtil.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Servo servo;

void doServo(int angle) {
  angle += 90;
  
  if (angle < 10) {
    angle = 10;
  }
  if (angle > 170) {
    angle = 170;
  }
  int finalAngle = 180 - angle;
  display.println(finalAngle);
  servo.write(finalAngle);
}

void setup(void) {
  Serial.begin(115200);
//  while (!Serial)
//    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  //  Serial.println("Adafruit LSM6DSOX test!");
  setupGyro();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  Serial.println(F("initialized"));

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  //  display.display();
  //  delay(2000); // Pause for 2 seconds

  servo.attach(10);
  servo.writeMicroseconds(1500);  // set servo to mid-point

  // Clear the buffer
  display.clearDisplay();
  //
  //  // Draw a single pixel in white
  display.drawPixel(100, 10, SSD1306_WHITE);
  display.display();
}

void loop() {
  //    display.loop();

  float angle, z;
  readAngle(angle);
//  Serial.print(angle); Serial.print(",");
//  Serial.println(lastZ());
//
  display.clearDisplay();

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(angle);
  display.setCursor(0, 16);

  doServo(angle);
  display.display();

  delay(30);
}
