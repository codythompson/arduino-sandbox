//#include <Math.h>
#include <Arduino.h>

#ifndef TWEEN_MAX_CHAIN
  #define TWEEN_MAX_CHAIN 16
#endif

typedef struct {
  int interpFunc;
  int start;
  int end;
  int duration;
  int delay;
  int delayAfter;
} TweenParams;

class Tween {
  private:
    // path parameters
    int interpFunc;
    int start;
    int end;
    int delta;
    int duration;
    int delay;
    int delayAfter; // AKA cooldown

    TweenParams chain[TWEEN_MAX_CHAIN];
    unsigned int chainLength = 0;
    unsigned int chainPtr = 0;

    // timestamps and variables
    int lastUpdate;
    int lastValue;
    int startTime;
    int pausedAt;

    // flags
    bool begun = false;
    bool complete = false;
    bool paused = false;

  public:
    static const int LINEAR = 0;
    static const int IN_OUT_EXP = 1;
    static const int IN_OUT_QUAD = 2;

    void begin(int interpFunc, int start, int end, int duration, int delay=0, int delayAfter=0);
    int interpolateLinear(double t);
    int interpolateInOutExp(double t);
    int interpolateInOutQuad(double t);
    int interpolate(double t);
    void pause();
    void resume();
    void update(int time);
    void push(int interpFunc, int start, int end, int duration, int delay=0, int delayAfter=0);

    bool isActive();
    bool hasCompleted();
    int value();
    int delayedStartTime();
    int delayedEndTime();
};
