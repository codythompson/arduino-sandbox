#include "Ticker.h"

Ticker::Ticker(int interval) {
  this->interval = interval;
  this->lastTick = millis();
}

int Ticker::delta() {
  return (millis() - this->lastTick) % (this->interval*2); // handles integer rollover of millis.
}

int Ticker::tick() {
  this->lastTick = millis();
  while (this->delta() < this->interval);
  return this->delta();
}
