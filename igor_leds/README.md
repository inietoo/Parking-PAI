# 💡 Igor - Sistema de Indicadores LED

## Detector de Plazas de Parking con Semáforo RGB

Sistema inteligente de detección de ocupación de plazas de estacionamiento mediante sensor ultrasónico HC-SR04 y LED RGB de ánodo común. Proporciona indicación visual en tiempo real del estado de disponibilidad de cada plaza.

---

## 📋 Descripción General

Este módulo implementa un semáforo inteligente que detecta si una plaza de parking está ocupada o libre usando:

- **Sensor Ultrasónico HC-SR04**: Detecta la presencia de vehículos midiendo la distancia
- **LED RGB (Ánodo Común)**: 
  - 🔴 **ROJO**: Plaza ocupada (distancia < 20 cm)
  - 🟢 **VERDE**: Plaza libre (distancia ≥ 20 cm)

### Características Principales

✅ Lectura no bloqueante del sensor (multitarea)  
✅ Indicación visual intuitiva con LED RGB  
✅ Test de hardware automático al arrancar  
✅ Comunicación serial para debugging  
✅ Bajo consumo de energía  
✅ Fácil integración con otros módulos del sistema

---

## 🔧 Hardware Requerido

| Componente | Cantidad | Notas |
|---|---|---|
| ESP32 DevKit V1 | 1 | Microcontrolador principal |
| Sensor Ultrasónico HC-SR04 | 1 | Rango: 2cm - 400cm |
| LED RGB (Ánodo Común) | 1 | Cátodo: 3V3, Ánodo: GND |
| Resistencias 220Ω | 2 | Protección para LED (rojo, verde) |
| Cables Dupont | ~8 | Conexiones generales |
| Protoboard | 1 | Montaje de circuito |

---

## 🔌 Esquema de Conexiones

### Sensor Ultrasónico HC-SR04

```
HC-SR04          ESP32
─────────────────────
VCC     ─────→  5V
GND     ─────→  GND
TRIG    ─────→  GPIO 5
ECHO    ─────→  GPIO 18
```

### LED RGB (Ánodo Común)

```
LED RGB          ESP32
────────────────────
Rojo    ─[220Ω]─→  GPIO 23
Verde   ─[220Ω]─→  GPIO 22
Ánodo   ─────────→  3V3
Cátodo  ─────────→  GND
```

---

## 📝 Configuración de Pines

```cpp
const int PIN_TRIG = 5;      // Trigger del sensor ultrasónico
const int PIN_ECHO = 18;     // Echo del sensor ultrasónico
const int PIN_ROJO = 23;     // LED Rojo
const int PIN_VERDE = 22;    // LED Verde
```

---

## 🎯 Parámetros Ajustables

| Parámetro | Valor | Descripción |
|---|---|---|
| `DISTANCIA_OCUPADO` | 20 cm | Umbral de detección (ajustable según altura) |
| `INTERVALO_LECTURA` | 200 ms | Frecuencia de lecturas del sensor |

### Cómo Ajustar el Umbral

Si necesitas cambiar la sensibilidad del detector:

```cpp
const int DISTANCIA_OCUPADO = 20;  // Aumenta para más distancia
                                    // Disminuye para más sensibilidad
```

---

## 📂 Estructura del Código

### Función: `setup()`
Inicializa pines, comunicación serial y realiza test de hardware.

### Función: `leerDistancia()`
Obtiene la distancia en cm del sensor HC-SR04 usando:
- Envío de pulso ultrasónico (10 µs)
- Medición del tiempo de retorno del echo
- Cálculo: Distancia = (Duración × 0.034 / 2) cm

### Función: `actualizarSemaforoParking()`
Actualiza el estado del LED según la distancia detectada:
- Distancia < 20 cm → LED ROJO (plaza ocupada)
- Distancia ≥ 20 cm → LED VERDE (plaza libre)

### Función: `loop()`
Lectura continua no bloqueante cada 200 ms.

---

## 🚀 Instalación y Uso

### Requisitos Previos

- Arduino IDE 1.8.0+
- Drivers CH340 instalados
- Librería ESP32 en Arduino IDE

### Pasos de Instalación

1. **Clonar el repositorio**
   ```bash
   git clone https://github.com/inietoo/Parking-PAI.git
   cd Parking-PAI/igor_leds
   ```

2. **Abrir el código en Arduino IDE**
   ```
   File → Open → igor_leds.ino
   ```

3. **Configurar la placa**
   ```
   Tools → Board → ESP32 Dev Module
   Tools → Port → COM[X] (tu puerto)
   Tools → Upload Speed → 115200
   ```

4. **Subir el código**
   ```
   Sketch → Upload (o Ctrl + U)
   ```

5. **Monitorizar el funcionamiento**
   ```
   Tools → Serial Monitor (115200 baud)
   ```

---

## 📊 Salida en Monitor Serial

```
========================================
   PARKING-PAI: Sistema de Semáforo
   Módulo: Detector de Plazas
========================================

[TEST] Encendiendo LED ROJO...
[TEST] Encendiendo LED VERDE...
[OK] Hardware listo. Iniciando detección de plazas...

Distancia detectada: 45 cm
[LIBRE] Plaza disponible. LED VERDE encendido.

Distancia detectada: 15 cm
[OCUPADO] Plaza detectada. LED ROJO encendido.
```

---

## 🔬 Pruebas Recomendadas

### Test de Hardware
El código incluye un test automático que:
1. Enciende LED ROJO durante 1 segundo
2. Apaga y enciende LED VERDE durante 1 segundo
3. Confirma que el sensor responde correctamente

### Test de Calibración

1. Sube el código y abre Monitor Serial
2. Aproxima tu mano lentamente al sensor
3. Anota a qué distancia cambia de ROJO a VERDE
4. Ajusta `DISTANCIA_OCUPADO` si es necesario

### Test de Integración

```bash
# Monitorizar continuamente
screen /dev/ttyUSB0 115200

# O en Windows
mode COM3:115200
```

---

## 🎨 Lógica de Funcionamiento

```
┌─────────────────────────────────────┐
│   INICIO - Setup del Hardware       │
└──────────────┬──────────────────────┘
               │
        ┌──────▼──────┐
        │ Cada 200 ms │
        └──────┬──────┘
               │
        ┌──────▼──────────────┐
        │ Leer Sensor HC-SR04 │
        └──────┬──────────────┘
               │
        ┌──────▼──────────────┐
        │ ¿Distancia < 20cm? │
        └──────┬───────┬──────┘
              SÍ      NO
               │       │
         ┌─────▼──┐  ┌─▼──────┐
         │LED ROJO│  │LED VERDE│
         │OCUPADO │  │ LIBRE   │
         └────────┘  └─────────┘
               │       │
               └───┬───┘
                   │
           ┌───────▼────────┐
           │ Monitor Serial │
           │  + Pausa 200ms │
           └────────────────┘
```

---

## 🐛 Troubleshooting

### Problema: LED no cambia de color
- ✓ Verifica las conexiones de pines (GPIO 22 y 23)
- ✓ Comprueba que las resistencias de 220Ω estén conectadas
- ✓ Verifica que el LED está correctamente polarizado

### Problema: Sensor no detecta distancia
- ✓ Verifica pines TRIG (GPIO 5) y ECHO (GPIO 18)
- ✓ Asegúrate de que el sensor tiene alimentación (5V)
- ✓ Limpia la superficie del sensor

### Problema: Lectura inestable
- ✓ Aumenta `INTERVALO_LECTURA` a 300 o 400 ms
- ✓ Añade capacitores de 100nF cerca del sensor
- ✓ Verifica que no hay interferencias electromagnéticas

### Problema: Monitor Serial muestra basura
- ✓ Verifica que la velocidad de conexión sea 115200 baud
- ✓ Comprueba el driver CH340
- ✓ Intenta con otro cable USB

---

## 📚 Documentación Técnica

### Sensor HC-SR04
- **Voltaje de funcionamiento**: 5V DC
- **Corriente**: 15 mA máximo
- **Rango de medición**: 2 cm - 400 cm
- **Precisión**: ±3 mm
- **Ángulo de detección**: 15°
- **Tiempo de pulso TRIG**: 10 µs (mínimo)

### LED RGB Ánodo Común
- **Voltaje directo**: 2V (rojo), 2.2V (verde)
- **Corriente máxima**: 20 mA por color
- **Resistencia recomendada**: 220Ω
- **Luminosidad**: 1000-2000 mcd

---

## 🔗 Integración con Otros Módulos

Este módulo se comunica con:

- **Pol - Control de Barreras**: Envía estado de ocupación para activar/desactivar barreras
- **Ivan - Contador de Plazas**: Proporciona datos de ocupación en tiempo real
- **Servidor Central**: Via WiFi/MQTT (extensible)

---

## 📄 Licencia

MIT License - Proyecto Parking-PAI (2026)

---

## 👨‍💻 Autor

**Igor** - Responsable del Sistema de Indicadores LED  
Parking-PAI Project Team

---

## 💬 Soporte

Para preguntas o problemas:
- 📧 Abrir un Issue en GitHub
- 💬 Usar GitHub Discussions
- 📞 Contactar al equipo del proyecto

---

**Última actualización**: Enero 2026  
*Made with 💚 by Igor*
