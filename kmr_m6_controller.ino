#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include "src/ard_ics.h"
#include "src/draw_led.h"

ard_ics ics(21, 48);
draw_led led;

void setup() {
  led.create_task("led_task", 1);

  ics.create_task("ics_task", 2);

  Dabble.begin("kmr-m6-01");

  Serial.begin(115200);
  //while (!Serial) delay(1);

  delay(1000);

  led.set_mode(BLUE, LIT);
}

void loop() {
  Dabble.processInput();
  if (GamePad.isUpPressed()) {
    ics.latest_rx = 'f';
  } else if (GamePad.isDownPressed()) {
    ics.latest_rx = 'b';
  } else if (GamePad.isRightPressed()) {
    ics.latest_rx = 'r';
  } else if (GamePad.isLeftPressed()) {
    ics.latest_rx = 'l';
  } else {
    ics.latest_rx = 'n';
  }
}