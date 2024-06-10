#include <Adafruit_NeoPixel.h>
#include "ard_ics.h"
#include "ble_uart.h"

Adafruit_NeoPixel pixels(1, 2, NEO_GRB + NEO_KHZ800);

ard_ics ics(21);
ble_uart ble;

void setup() {
  Serial.begin(115200);
  //while (!Serial) delay(1);

  pixels.begin();

  ble.init("kmr-m6-1");
  ble.task_create();
}

void loop() {
  // 接続チェック＆LED表示
  while (1) {
    /*
    if (!deviceConnected) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.show();
      delay(100);
      pixels.setPixelColor(0, pixels.Color(0, 0, 255));
      pixels.show();
      delay(100);
    } else {
      pixels.setPixelColor(0, pixels.Color(0, 255, 0));
      pixels.show();
      break;
    }
    */
  }
  ics.set_pos(6, 5000);
  delay(1000);
  ics.set_pos(6, 10000);
  delay(1000);
}