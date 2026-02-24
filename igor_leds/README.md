# igor_leds — Módulo Detector de Plazas

Módulo ESP32 encargado de detectar si una plaza de aparcamiento está **libre u ocupada** mediante un sensor ultrasónico HC-SR04, controlar un LED semáforo (rojo/verde) y enviar el estado al servidor central vía HTTP POST.

---

## 📶 Conexión de Red

Este módulo se conecta a la red **`gencat_ENS_EDU`** usando autenticación **WPA2 Enterprise (PEAP/MSCHAPv2)** a través de la librería `esp_wpa2.h`.

| Parámetro     | Valor              |
|--------------|--------------------|
| SSID         | `gencat_ENS_EDU`   |
| Método Auth  | WPA2 Enterprise    |
| Identity     | `W43007257`        |

---

## 📡 Servidor

| Parámetro   | Valor                                      |
|------------|--------------------------------------------|
| URL        | `http://192.168.3.249:8080/api/parking`    |
| Método     | `POST`                                     |
| Formato    | JSON                                       |

**Ejemplo de payload enviado:**
```json
{"id": 6, "zone": "C", "free": false}
```

El envío **solo se realiza cuando cambia el estado** de la plaza (libre ↔ ocupado) o en la primera ejecución, evitando tráfico innecesario.

---

## 🔌 Pines ESP32

| Componente         | Pin GPIO |
|-------------------|----------|
| HC-SR04 TRIG      | 5        |
| HC-SR04 ECHO      | 18       |
| LED Rojo (ánodo)  | 23       |
| LED Verde (ánodo) | 22       |

> Los LEDs usan configuración de **ánodo común**: `LOW` = encendido, `HIGH` = apagado.

---

## 📌 Datos de la Plaza

| Parámetro | Valor |
|----------|-------|
| ID       | `6`   |
| Zona     | `C`   |

---

## ⚙️ Lógica de Funcionamiento

1. **Setup:** Configura pines, conecta al WiFi WPA2 Enterprise y hace un test visual de LEDs.
2. **Loop (cada 200 ms):**
   - Lanza un pulso ultrasónico y mide la distancia.
   - Si `distancia < 20 cm` → plaza **ocupada** → LED rojo encendido.
   - Si `distancia >= 20 cm` (o sin eco) → plaza **libre** → LED verde encendido.
   - Si el estado cambió respecto al ciclo anterior (o es la primera lectura), envía un **POST HTTP** al servidor.
3. **Reconexión automática:** Si el WiFi tarda más de 20 segundos en conectar, el ESP32 se **reinicia** automáticamente.

---

## 📦 Dependencias

- `WiFi.h` (incluida en el core ESP32)
- `HTTPClient.h` (incluida en el core ESP32)
- `esp_wpa2.h` (incluida en el core ESP32)

> No se requieren librerías externas. Compilar con el **Arduino IDE** o **PlatformIO** con el core de ESP32 instalado.

---

## 📁 Estructura de Archivos

```
igor_leds/
├── igor_leds.ino   # Código fuente principal
└── README.md       # Este archivo
```
