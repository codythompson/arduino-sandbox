
#include <Adafruit_NeoPixel.h>
#include <ezButton.h>

const int ledPin = 7;
const int neoPixelPin = 8;
const int buttonPin = 2;

Adafruit_NeoPixel neoPixel = Adafruit_NeoPixel(1, neoPixelPin, NEO_RGB + NEO_KHZ800);
ezButton button(buttonPin);

const int colorCount = 3;
const uint32_t colorsByState[] = {
  neoPixel.Color(255, 0, 0),
  neoPixel.Color(0, 255, 0),
  neoPixel.Color(0, 0, 255)
};

// variables will change:
int buttonState = HIGH;

int neoPixelState = 0;

void printColor(uint32_t color) {
  Serial.print("color: ");
  Serial.print(color, HEX);
  Serial.print("|");
}

void setNeoPixelState(int stateIndex) {
  Serial.print("set state: ");

  if (stateIndex == 0) {
    neoPixel.clear();
  }
  else {
    Serial.print(" - ");
    printColor(colorsByState[stateIndex-1]);
    neoPixel.setPixelColor(0, colorsByState[stateIndex-1]);
  }
  Serial.println(stateIndex-1);
  neoPixel.show();
}

void setup() {  
  neoPixelState = 0;
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);

  neoPixel.begin();
  neoPixel.setBrightness(1);
  neoPixel.show(); // Initialize all pixels to 'off'

  //Initiate Serial communication.
  Serial.begin(9600);
}

void loop() {
  button.loop();

  int lastState = buttonState;
    // read the state of the pushbutton value:
  buttonState = button.getState();

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, LOW);

    if (buttonState != lastState) {
      Serial.print("button release");
      Serial.print(neoPixelState);
      neoPixelState++;
      Serial.print(neoPixelState);
      Serial.print(" - ");
      neoPixelState = neoPixelState % (colorCount+1);
      Serial.println(neoPixelState);
      setNeoPixelState(neoPixelState);
      delay(500);
    }
  } else {
    // turn LED off:
    digitalWrite(ledPin, HIGH);
  }
}
