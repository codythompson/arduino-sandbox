#include "GyroUtil.h"

Adafruit_LSM6DSOX sox;

void setupGyro(void) {
  if (!sox.begin_I2C()) {
    Serial.println(F("Unable to connect to sox gyro"));
    while (1) {
      delay(10);
    }
  }
}

float x, y, z;
void readAngle(float &angle) {
  sox.readAcceleration(x, y, z);
  angle = (atan(y/x)) * (180/PI);
}

float lastZ() {
  return z;
}
