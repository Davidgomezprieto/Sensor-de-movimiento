# Sensor de Movimiento BLE con ESP32

Este proyecto implementa un sensor de movimiento con ESP32 que utiliza un sensor PIR y comunicación Bluetooth Low Energy (BLE) para enviar notificaciones a un dispositivo móvil. Además, permite controlar el LED RGB integrado del ESP32 desde la aplicación móvil.

---

✨ Características
- 📡 Comunicación BLE con UUID de servicio y característica personalizadas.
- 👀 Detección de movimiento mediante un sensor PIR conectado al pin `GPIO 4`.
- 🔔 Notificaciones automáticas al móvil cuando se detecta movimiento.
- 🎨 Control remoto del LED RGB integrado:
  - `0` → LED rojo
  - `1` → LED verde
- ⏱️ Uso de millis() para un código no bloqueante.

---

🛠️ Hardware necesario
- ESP32 con LED RGB integrado.
- Sensor PIR (conectado al pin `GPIO 4`).
- Cableado básico.

---

📂 Estructura del código
- BLE inicialización: Configura servidor, servicio y característica BLE.
- Callbacks:
  - `MyCallbacks`: recibe comandos desde el móvil.
  - `MyServerCallbacks`: gestiona conexión/desconexión.
- Loop principa:
  - Ejecuta acciones pendientes (encender LED por 3 segundos).
  - Envía notificaciones al móvil si el PIR detecta movimiento.

---

🚀 Instalación y uso
1. Clona este repositorio:
   ```bash
   git clone https://github.com/tuusuario/sensor-movimiento-ble.git
