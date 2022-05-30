//#include <Math.h>
#include <Arduino.h>

class EasedPath {
  private:
    // path parameters
    int start;
    int end;
    int delta;
    int duration;

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
//    EasedPath();

    int interpolate(double t);
    void begin(int start, int end, int duration);
    void pause();
    void resume();
    int update(int time);

    bool isActive();
    bool hasCompleted();
    int value();
};
