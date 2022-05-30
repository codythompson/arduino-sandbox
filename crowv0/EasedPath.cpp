#include "EasedPath.h"

void debugPrint(String label, int value) {
  Serial.print(label);
  Serial.print(" ");
  Serial.println(value);
}

int EasedPath::interpolate(double t) {
  Serial.print("interpolate: ");
  Serial.println(t);
  return this->start + (round(this->delta * t));
}

void EasedPath::begin(int start, int end, int duration) {
  this->start = start;
  this->end = end;
  this->delta = end - start;
  this->duration = duration;

  this->begun = true;
  this->complete = false;
  this->paused = false;
  this->startTime = this->lastUpdate;
}

void EasedPath::pause() {
  this->pausedAt = this->lastUpdate;
  this->paused = true;
}

void EasedPath::resume() {
  this->startTime = this->startTime + (this->pausedAt - this->startTime);
  this->paused = true;
}

int EasedPath::update(int time) {
  this->lastUpdate = time;

  int value = 0;
  if (this->paused) {
    value = this->lastValue;
  }
  else if (this->complete) {
    value = this->end;
  }
  else if (!this->begun) {
    value = this->start;
  }
  else {
    double t = (double)(time - this->startTime) / (double)this->duration;
    debugPrint("start", this->startTime);
    if (t >= 1.0) {
      t = 1.0;
      this->begun = false;
      this->complete = true;
      return this->end;
    }
    value = this->interpolate(t);
  }

  this->lastValue = value;
  return value;
}

bool EasedPath::isActive() {
  return this->begun && !this->complete;
}

bool EasedPath::hasCompleted() {
  return this->complete;
}

int EasedPath::value() {
  return this->lastValue;
}
