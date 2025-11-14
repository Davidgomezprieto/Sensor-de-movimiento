/*
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

void setup() {
  Serial.begin(115200);
  BLEDevice::init("esp32_david");  // Nombre visible en BLE
  BLEServer *pServer = BLEDevice::createServer();
  pServer->createService("180A");    // Servicio genérico
  pServer->getAdvertising()->start();
  Serial.println("✅ Anunciando BLE, busca 'ESP32S3_Test' en tu app.");
}

void loop() {}
*/
#include <BLEDevice.h>

void setup() {
  Serial.begin(115200);
  BLEDevice::init("ESP32S3_Test");
  Serial.println("BLE inicializado correctamente.");
}

void loop() {}

