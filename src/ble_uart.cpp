#include "ble_uart.h"

bool deviceConnected;
bool oldDeviceConnected;

ble_uart::ble_uart()
{
  newest_rx_value = NULL;
}
void ble_uart::MyServerCallbacks::onConnect(BLEServer *pServer)
{
  deviceConnected = true;
}

void ble_uart::MyServerCallbacks::onDisconnect(BLEServer *pServer)
{
  deviceConnected = false;
}

void ble_uart::set_newest_rx_value(char a)
{
  newest_rx_value = a;
}

void ble_uart::MyCallbacks::onWrite(BLECharacteristic *pCharacteristic)
{
  std::string rxValue = pCharacteristic->getValue();

  /*
  if (rxValue.length() > 0) {
    Serial.println("*********");
    Serial.print("Received Value: ");
    for (int i = 0; i < rxValue.length(); i++)
      Serial.print(rxValue[i]);

    Serial.println();
    Serial.println("*********");
  }
  */
}

void ble_uart::init(char *device_name)
{
  BLEDevice::init(device_name);

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pTxCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID_TX,
      BLECharacteristic::PROPERTY_NOTIFY);

  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID_RX,
      BLECharacteristic::PROPERTY_WRITE);

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
}

void ble_uart::task()
{
  while (1)
  {
    // disconnecting
    if (!deviceConnected && oldDeviceConnected)
    {
      vTaskDelay(500 / portTICK_RATE_MS); // give the bluetooth stack the chance to get things ready
      pServer->startAdvertising();        // restart advertising
      // Serial.println("start advertising");
      oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected)
    {
      // do stuff here on connecting
      oldDeviceConnected = deviceConnected;
    }
  }
}

bool ble_uart::get_deviceConnected()
{
  return deviceConnected;
}