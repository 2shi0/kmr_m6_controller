#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include "src/ard_ics.h"
#include "src/draw_led.h"


ard_ics ics(21);
draw_led led;

char rx_value = 's';

void setup() {
  led.create_task("led_task");

  ics.create_task("ics_task");

  Dabble.begin("kmr-m6-01");

  Serial.begin(115200);
  //while (!Serial) delay(1);

  ics.set_speed(64);

  ics.motion_neutral();

  delay(1000);

  ics.motion_forward();
}

void loop() {
  Dabble.processInput();
  if (GamePad.isUpPressed()) {
    ics.latest_rx = 'f';
  } else if (GamePad.isDownPressed()) {
    ics.latest_rx = 'b';
  } else {
    ics.latest_rx = 'n';
  }

  /*
  if (!ble.get_deviceConnected()) {
    led.set_mode(BLUE, BLINK);
  } else {
    led.set_mode(GREEN, LIT);
  }

  ics.set_pos(6, 5000);
  delay(1000);
  ics.set_pos(4, 5000);
  delay(1000);
  ics.set_pos(6, 10000);
  delay(1000);
  ics.set_pos(4, 10000);
  delay(1000);
  */
}