#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define MAX_POSE_PARTS 8

#define BRIGHTNESS_MASK 0xff000000
#define RED_MASK 0x00ff0000
#define GREEN_MASK 0x0000ff00
#define BLUE_MASK 0x000000ff
#define BRIGHTNESS_SHIFT 24
#define RED_SHIFT 16
#define GREEN_SHIFT 8
#define BLUE_SHIFT 0

class Part {
  protected:
    u_int min, max, position, delta;
    Part(u_int id, u_int min, u_int max);

  public:
    u_int id;
    virtual void setPosition(u_int position);
    virtual u_int getPosition();
};

class ServoPart : Part {
  public:
    Servo servo;
    ServoPart(u_int id, Servo servo, u_int min, u_int max);
    virtual void setPosition(u_int position);
};

class PixelPart : Part {
  protected:
    static u_int setChannel(u_int color, byte newValue, u_int mask, u_int shift);
  public:
    Adafruit_NeoPixel pixel;
    u_int pixelIndex;
    PixelPart(u_int id, Adafruit_NeoPixel pixel, u_int pixelIndex);

    // static u_int red(u_int color);
    // static u_int blue(u_int color);
    // static u_int green(u_int color);
    // static u_int brightness(u_int color);
    virtual void setPosition(u_int position);
    void setBrightness(byte bright);
    void setRed(byte r);
    void setGreen(byte g);
    void setBlue(byte b);
};

typedef struct {
  u_int partId;
  u_int position;
} Position;

class Pose {
  protected:
    u_int stackPtr = 0;
    Position positions[MAX_POSE_PARTS];

  public:
    Pose push(Part part, u_int position);
    u_int length();
    u_int findPositionFor(Part part);
};
