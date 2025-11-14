# Sensor-de-movimiento
Implementación de un sensor infrarrojo "PIR" anexado a una ESP32s3 de expressif mediante arduino IDE

Perfecto, con lo que me acabas de explicar, puedo estructurar **el flujo completo de tu proyecto** de manera clara y lista para documentarlo, e incluso sirve de guía para programar la ESP32S3. Te lo dejo organizado paso a paso:

---

# 🟡 **Flujo completo del proyecto de alarma con ESP32S3 y sensor PIR**

### 0️⃣ Control remoto de activación

* La ESP32S3 empieza con el **sensor PIR apagado**.
* Vía **WiFi**, la placa puede recibir una señal de **activar o desactivar** el proceso de alarma.

---

### 1️⃣ Vigilancia continua

* Cuando la alarma está activada, el **sensor PIR comienza a vigilar constantemente**.
* Mientras no se detecte movimiento, el sistema **permanece en espera**.

---

### 2️⃣ Detección de movimiento

* Cuando el PIR detecta movimiento:

  * Se **enciende el LED RGB integrado en amarillo**.
  * Se envía un **aviso vía WiFi al teléfono del dueño**.

---

### 3️⃣ Verificación de identidad

* La ESP32S3 espera la respuesta del dueño desde el móvil.
* El dueño puede indicar si **fue él quien causó el movimiento** o si **es un intruso**.

---

### 4️⃣ Acceso autorizado (dueño)

* Si el dueño indica que fue él:

  * Debe introducir un **PIN de 6 dígitos** desde el móvil.
  * Se dispone de **30 segundos** para introducir la clave.
  * Si el PIN es correcto:

    * El LED se **enciende en verde**.
    * Se envía un **mensaje vía WiFi: “Bienvenida a casa”**.
    * El proceso de alarma se **apaga automáticamente después de 5 segundos**.

---

### 5️⃣ Intruso o fallo de verificación

* Si no se introduce la clave en **30 segundos**:

  * Se emite un **sonido de alarma en el móvil**.
  * El LED se **enciende en rojo**.
* Este estado indica una posible intrusión.

---

### 6️⃣ Resumen de colores del LED

| Color    | Significado                                  |
| -------- | -------------------------------------------- |
| Amarillo | Movimiento detectado, esperando confirmación |
| Verde    | Acceso autorizado, alarma apagada            |
| Rojo     | Alarma por intrusión o fallo de PIN          |



¿Quieres que haga ese diagrama?
