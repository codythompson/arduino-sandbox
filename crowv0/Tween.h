//#include <Math.h>
#include <Arduino.h>

#ifndef TWEEN_MAX_CHAIN
  #define TWEEN_MAX_CHAIN 4
#endif

typedef struct {
  int start;
  int end;
  int duration;
  int delay;
  int delayAfter;
} TweenParams;

class Tween {
  private:
    // path parameters
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
    void begin(int start, int end, int duration, int delay=0, int delayAfter=0);
    int interpolate(double t);
    void pause();
    void resume();
    void update(int time);
    void push(int start, int end, int duration, int delay=0, int delayAfter=0);

    bool isActive();
    bool hasCompleted();
    int value();
    int delayedStartTime();
    int delayedEndTime();
};
