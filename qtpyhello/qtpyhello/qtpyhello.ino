#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BOARD_PIXEL_PIN 11

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_NeoPixel boardPixel = Adafruit_NeoPixel(1, BOARD_PIXEL_PIN);

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Serial initialized");
  boardPixel.begin();
  Serial.println("board pixel initialized");
  boardPixel.setBrightness(10);
//   SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 allocation failed");
    for (;;); // Don't proceed, loop forever
  }
  Serial.println("initialized");
}

void loop() {
  display.clearDisplay();
  display.invertDisplay(true);
  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.print(F("Hi Ivy!"));
  display.println();
  display.display();
  display.startscrollleft(0x00, 0x0F);
  delay(5000);
  display.stopscroll();
  display.startscrollright(0x00, 0x0F);
  delay(5000);
  display.stopscroll();

  boardPixel.setPixelColor(0, boardPixel.Color(255, 255, 0));
  boardPixel.show();
  delay(1000);
      
  // turn off the pixel
  boardPixel.clear();
  boardPixel.show();

  delay(1000);
}
