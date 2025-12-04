#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define PIR_PIN 4
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
bool accionPendiente = false;
int color = -1; // -1 = nada, 0 = rojo, 1 = verde

// Variables para control con millis
unsigned long tiempoInicioAccion = 0;
const unsigned long duracionAccion = 3000; 

unsigned long ultimoMovimiento = 0;
const unsigned long intervaloMovimiento = 1000; 

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pChar) {
    String rxValue = String(pChar->getValue().c_str()); 
    if (rxValue == "1") {
      color = 1;
      accionPendiente = true;
      tiempoInicioAccion = millis();
    } else if (rxValue == "0") {
      color = 0;
      accionPendiente = true;
      tiempoInicioAccion = millis();
    }
    Serial.println("Comando recibido: " + rxValue);
  }
};

class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) { deviceConnected = true; }
  void onDisconnect(BLEServer* pServer) { deviceConnected = false; }
};

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);

  BLEDevice::init("SensorMovimiento");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ
  );
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();

  Serial.println("Advertising iniciado");

  // LED apagado al inicio
  rgbLedWrite(RGB_BUILTIN, 0, 0, 0);
}

void loop() {
  unsigned long ahora = millis();

  // Ejecutar acción recibida desde móvil
  if (accionPendiente) {
    if (color == 1) {
      rgbLedWrite(RGB_BUILTIN, 0, 255, 0); // Verde
    } else if (color == 0) {
      rgbLedWrite(RGB_BUILTIN, 255, 0, 0); // Rojo
    }

    // Apagar después de 3 segundos
    if (ahora - tiempoInicioAccion >= duracionAccion) {
      rgbLedWrite(RGB_BUILTIN, 0, 0, 0); // Apagar
      accionPendiente = false;
      color = -1;
    }
  }

  // Notificación automática si PIR_PIN está en HIGH
  int estado = digitalRead(PIR_PIN);
  if (deviceConnected && estado == HIGH) {
    if (ahora - ultimoMovimiento >= intervaloMovimiento) {
      pCharacteristic->setValue("Movimiento detectado");
      pCharacteristic->notify();
      Serial.println("Notificación enviada al móvil");
      ultimoMovimiento = ahora;
    }
  }
}
