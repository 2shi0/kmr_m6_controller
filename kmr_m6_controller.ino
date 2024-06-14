#include "src/ard_ics.h"
#include "src/ble_uart.h"
#include "src/draw_led.h"

ard_ics ics(21);
ble_uart ble;
draw_led led;

void setup() {
  Serial.begin(115200);
  //while (!Serial) delay(1);

  ble.init("kmr-m6-01");

  ble.create_task("ble_task");

  led.create_task("led_task");

  delay(1000);

  ics.set_speed(64);

  ics.set_motion();


  while (1) {
    if (!ble.get_deviceConnected()) {
      led.set_mode(BLUE, BLINK);
    } else {
      led.set_mode(GREEN, LIT);
      break;
    }
  }
}

void loop() {

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