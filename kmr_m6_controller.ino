#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include "src/ard_ics.h"
#include "src/draw_led.h"

ard_ics ics(21, 64);
draw_led led;

void setup() {
  led.create_task("led_task");

  ics.create_task("ics_task");

  Dabble.begin("kmr-m6-01");

  Serial.begin(115200);
  //while (!Serial) delay(1);

  delay(1000);

  led.set_mode(BLUE, LIT);

  int home[12] = { 0, 0, 0, 0,
                   0, 0, 0, 0,
                   0, 0, 0, 0 };
  ics.set_all(home);

  int f1[12] = { 1400, -600, 0, 0,
                 0, 0, 600, -1400,
                 1400, -600, 0, 0 };

  int f2[12] = { 0, -600, 0, 0,
                 0, 0, 600, 0,
                 0, -600, 0, 0 };


  int f3[12] = { 0, 0, 600, -1400,
                 1400, -600, 0, 0,
                 0, 0, 600, -1400 };

  int f4[12] = { 0, 0, 600, 0,
                 0, -600, 0, 0,
                 0, 0, 600, 0 };

  while (1) {
    vTaskDelay(1000 / portTICK_RATE_MS);
    ics.set_all(f1);
    vTaskDelay(1000 / portTICK_RATE_MS);
    ics.set_all(f2);
    vTaskDelay(1000 / portTICK_RATE_MS);
    ics.set_all(f3);
    vTaskDelay(1000 / portTICK_RATE_MS);
    ics.set_all(f4);
  }
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