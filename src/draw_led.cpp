#include "draw_led.h"

draw_led::draw_led() {
  current_color = BLUE;
  current_mode = 0;
}

void draw_led::task() {
  Adafruit_NeoPixel pixels(1, 2, NEO_GRB + NEO_KHZ800);
  pixels.begin();
  while (1) {
    switch (current_mode) {
      case LIT:
        pixels.setPixelColor(0, current_color);
        pixels.show();
        break;
      case BLINK:
        pixels.setPixelColor(0, BLACK);
        pixels.show();
        vTaskDelay(100 / portTICK_RATE_MS);
        pixels.setPixelColor(0, current_color);
        pixels.show();
        vTaskDelay(100 / portTICK_RATE_MS);
        break;
    }
  }
}

void draw_led::set_mode(uint32_t color, uint8_t blink_mode) {
  current_color = color;
  current_mode = blink_mode;
}