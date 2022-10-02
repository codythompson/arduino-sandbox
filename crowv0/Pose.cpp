#include "Pose.h"

Part::Part(u_int id, u_int min, u_int max) {
  this->id = id;
  this->min = min;
  this->max = max;
  this->position = min;
  this->delta = max-min;
};
void Part::setPosition(u_int position) {
  if (position < this->min) {
    this->position = this->min;
  }
  else if (position > this->max) {
    this->position = this->max;
  }
  else {
    this->position = position;
  }
}
u_int Part::getPosition() {
  return this->position;
}

ServoPart::ServoPart(u_int id, Servo servo, u_int min, u_int max): Part(id, min, max) {
  this->servo = servo;
}
void ServoPart::setPosition(u_int position) {
  Part::setPosition(position);
  this->servo.writeMicroseconds(this->position);
}

PixelPart::PixelPart(u_int id, Adafruit_NeoPixel pixel, u_int pixelIndex): Part(id, 0, 0xffffffff) {
  this->pixel = pixel;
  this->pixelIndex = pixelIndex;
}
// static u_int red(u_int color) {
//   // mask and shift right - the mask might be redundant here if ints are 4 bytes
//   u_int result = (color & 0xff000000)>>24;
//   return result;
// }
// static u_int green(u_int color) {
//   // mask and shift right
//   u_int result = (color & 0x00ff0000)>>16;
//   return result;
// }
// static u_int blue(u_int color) {
//   // mask and shift right
//   u_int result = (color & 0x0000ff00)>>8;
//   return result;
// }
// static u_int brightness(u_int color) {
//   // only need to mask for brightness, as its in the least significant bits
//   u_int result = color & 0x000000ff;
//   return result;
// }
void PixelPart::setPosition(u_int color) {
  Part::setPosition(color);
  this->pixel.setPixelColor(this->pixelIndex, this->position);
}
u_int PixelPart::setChannel(u_int color, byte newValue, u_int mask, u_int shift) {
  return (color & (~mask)) | (newValue << shift);
}
void PixelPart::setBrightness(byte bright) {
  u_int newColor = this->setChannel(this->position, bright, BRIGHTNESS_MASK, BRIGHTNESS_SHIFT);
  this->setPosition(newColor);
}
void PixelPart::setRed(byte r) {
  u_int newColor = this->setChannel(this->position, r, RED_MASK, RED_SHIFT);
  this->setPosition(newColor);
}
void PixelPart::setGreen(byte g) {
  u_int newColor = this->setChannel(this->position, g, GREEN_MASK, GREEN_SHIFT);
  this->setPosition(newColor);
}
void PixelPart::setBlue(byte b) {
  u_int newColor = this->setChannel(this->position, b, BLUE_MASK, BLUE_SHIFT);
  this->setPosition(newColor);
}

Pose Pose::push(Part part, u_int position) {
  if (this->stackPtr == MAX_POSE_PARTS) {
    Serial.print(F("REACHED MAX FOR POSE! Unable to push part-position to pose. PARTID: "));
    Serial.println(part.id);
  }
  this->positions[this->stackPtr] = {
    partId: part.id,
    position: position
  };
  this->stackPtr++;
  return *this;
}

u_int Pose::length() {
  return this->stackPtr;
}
