#include <Servo.h>
#include <Adafruit_NeoPixel.h>
//#include <ezButton.h>

#define BOARD_PIXEL_PIN 11
Adafruit_NeoPixel boardPixel = Adafruit_NeoPixel(1, BOARD_PIXEL_PIN);

//ezButton button(2);
Servo myServo;

void setup() {
  Serial.begin(9600);

  boardPixel.begin();
  boardPixel.setBrightness(10);
`  
//  pinMode(7, OUTPUT);
//  pinMode(2, INPUT);
  pinMode(10, OUTPUT);
//  button.setDebounceTime(200);
  myServo.attach(10);
}

void loop() {

  boardPixel.setPixelColor(0, boardPixel.Color(0, 0, 255));
  boardPixel.show();
//  button.loop();

  int pos = 45;
  Serial.println("released");
//  digitalWrite(7, LOW);
  myServo.write(pos);
  delay(1000);
  Serial.println(pos);
  myServo.write(90);

  boardPixel.clear();
  boardPixel.show();
  delay(1000);
  Serial.println("done");
}
