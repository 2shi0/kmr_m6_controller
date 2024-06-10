#include "ard_ics.h"
#include "ble_uart.h"
#include "draw_led.h"

ard_ics ics(21);
ble_uart ble;
draw_led led;

void setup() {
  Serial.begin(115200);
  //while (!Serial) delay(1);

  ble.init("kmr-m6-01");
  ble.create_task("ble_task");

  led.create_task("led_task");

  led.set_mode(BLUE, LIT);
}

void loop() {
  // 接続チェック＆LED表示
  if (!ble.get_deviceConnected()) {
    led.set_mode(BLUE, BLINK);
  } else {
    led.set_mode(GREEN, LIT);
  }


  //ics.set_pos(6, 5000);
  //delay(1000);
  //ics.set_pos(6, 10000);
  //delay(1000);
}