#ifndef _DRAW_LED_h_
#define _DRAW_LED_h_
#include <Adafruit_NeoPixel.h>
#include "task_maker.h"

#define BLUE 255
#define BLACK 0
#define GREEN 65280
#define WHITE 16777215

#define LIT 0
#define BLINK 1

class draw_led : public task_maker {
public:
  draw_led();
  void set_mode(uint32_t color, uint8_t blink_mode);
  void task();
private:
  uint32_t current_color;
  uint8_t current_mode;
};

#endif