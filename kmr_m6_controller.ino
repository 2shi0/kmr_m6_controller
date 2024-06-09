#include <Adafruit_NeoPixel.h>

#include "ard_ics.h"

Adafruit_NeoPixel pixels(1, 2, NEO_GRB + NEO_KHZ800);

ard_ics ics(21);

void setup() {
  pixels.begin();
}

void loop() {
  pixels.setPixelColor(0, pixels.Color(0, 0, 255));
  pixels.show();
  delay(500);

  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  delay(500);
}
