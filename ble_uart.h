#ifndef _BLE_UART_h_
#define _BLE_UART_h_
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID "f087f937-bb08-4803-a85c-7f68aaea5cec"
#define CHARACTERISTIC_UUID_RX "f087f938-bb08-4803-a85c-7f68aaea5cec"
#define CHARACTERISTIC_UUID_TX "f087f939-bb08-4803-a85c-7f68aaea5cec"

class ble_uart {
public:
  ble_uart();
  void init(char *device_name);
  void task_create();

private:
  BLEServer *pServer = NULL;
  BLECharacteristic *pTxCharacteristic;

  class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *pServer);

    void onDisconnect(BLEServer *pServer);
  };
  class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic);
  };

  void ble_task();
};

#endif