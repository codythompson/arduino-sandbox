#include <Arduino.h>

class Ticker {
  public:
    int interval;
    int lastTick = 0;

    Ticker(int interval);

    int delta();
    int tick();
};
