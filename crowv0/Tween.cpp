#include "Tween.h"

/**
 * @brief https://easings.net/#easeInOutExpo
 *
 * @param t
 * @return int
 */
int Tween::interpolateInOutExp(double t) {
  double newT = t == 0
    ? 0
    : t == 1
    ? 1
    : t < 0.5 ? pow(2, 20 * t - 10) / 2
    : (2 - pow(2, -20 * t + 10)) / 2;
  return this->interpolateLinear(newT);
}
int Tween::interpolateInOutQuad(double t) {
  double newT = t < 0.5 ? 2 * t * t : 1 - pow(-2 * t + 2, 2) / 2;
  return this->interpolateLinear(newT);
}
int Tween::interpolateLinear(double t) {
  return this->start + (round(this->delta * t));
}
int Tween::interpolate(double t) {
  if (this->interpFunc == this->LINEAR) {
    return this->interpolateLinear(t);
  }
  else if (this->interpFunc == this->IN_OUT_EXP) {
    return this->interpolateInOutExp(t);
  }
  else if (this->interpFunc == this->IN_OUT_QUAD) {
    return this->interpolateInOutQuad(t);
  }
  else {
    Serial.println(F("Unknown interp func"));
    return this->start;
  }
}

void Tween::begin(int interpFunc, int start, int end, int duration, int delay, int delayAfter) {
  this->interpFunc = interpFunc;
  this->start = start;
  this->end = end;
  this->delta = end - start;
  this->duration = duration;
  this->delay = delay;
  this->delayAfter = delayAfter;

  this->startTime = this->lastUpdate;

  this->begun = true;
  this->complete = false;
  this->paused = false;
}

void Tween::pause() {
  this->pausedAt = this->lastUpdate;
  this->paused = true;
}

void Tween::resume() {
  this->startTime = this->startTime + (this->pausedAt - this->startTime);
  this->paused = true;
}

void Tween::update(int time) {
  this->lastUpdate=time;

  int value = 0;
  if (this->paused) {
    value = this->lastValue;
  }
  else if (this->complete) {
    value = this->end;
  }
  else if (!this->begun || time <= this->delayedStartTime()) {
    value = this->start;
  }
  else {
    double t = (double)(time - this->delayedStartTime()) / (double)this->duration;
    // debugPrint("start", this->startTime);
    if (t >= 1.0) {
      int endVal = this->end;
      if (time >= this->delayedEndTime()) {
        this->begun = false;
        this->complete = true;
        if (this->chainPtr < this->chainLength) {
          TweenParams p = this->chain[this->chainPtr++];
          this->begin(
            p.interpFunc,
            p.start,
            p.end,
            p.duration,
            p.delay,
            p.delayAfter
          );
        }
      }
      value = endVal;
    }
    else {
      value = this->interpolate(t);
    }
  }

  this->lastValue = value;
}

void Tween::push(int interpFunc, int start, int end, int duration, int delay, int delayAfter) {
  if (this->chainLength >= TWEEN_MAX_CHAIN) {
    Serial.println(F("ERROR!!! - MAX CHAIN REACHED"));
    return;
  }
  this->chain[this->chainLength] = {
    interpFunc,
    start,
    end,
    duration,
    delay,
    delayAfter
  };
  this->chainLength++;
}

bool Tween::isActive() {
  return this->begun && !this->complete;
}

bool Tween::hasCompleted() {
  return this->complete;
}

int Tween::value() {
  return this->lastValue;
}

int Tween::delayedStartTime() {
  return this->startTime + this->delay;
}

int Tween::delayedEndTime() {
  return this->delayedStartTime() + this->duration + this->delayAfter;
}
