# 💡 Igor - Sistema de Indicadores LED

## Descripción del Subsistema

Este módulo es responsable de la visualización inteligente de la disponibilidad de plazas de estacionamiento mediante un sistema de LEDs programables. Proporciona retroalimentación visual en tiempo real del estado del estacionamiento.

### Funcionalidades Principales

- **LEDs Direccionables**: Control individual de múltiples LEDs WS2812B/NeoPixel
- **Patrones Visuales**: Animaciones intuitivas para indicar ocupación
- **Control de Brillo**: Ajuste dinámico según condiciones de luz ambiental
- **Eficiencia Energética**: Optimización de consumo de potencia
- **Integración con Servidor**: Sincronización en tiempo real

## Componentes de Hardware

```
Tiras LED WS2812B (NeoPixel)
Drivers de Potencia Eficientes
Circuitos de Protección/Filtrado
Capacitores de Desacoplamiento
Resistencias de Protección
```

## Estructura de Carpetas

```
igor_leds/
├── README.md (Este archivo)
├── codigo_principal/
│   ├── leds.ino
│   ├── patrones.h
│   ├── animaciones.h
│   └── comunicacion.h
├── paleta_colores.md
└── pruebas/
    └── test_leds.cpp
```

## Código de Colores

```
🟢 VERDE: Plazas disponibles
🔴 ROJO: Estacionamiento lleno
🟡 AMARILLO: Pocas plazas disponibles
🔵 AZUL: Sistema en espera
⚪ BLANCO: Error o mantenimiento
```

## Protocolo de Comunicación

### Mensajes Recibidos
```json
{
  "accion": "actualizar",
  "plazas_libres": 15,
  "plazas_totales": 50,
  "estado": "normal" | "alerta" | "lleno"
}
```

### Estados de Visualización
```json
{
  "estado_led": "prendido" | "apagado" | "parpadeante",
  "color": "rojo" | "verde" | "amarillo",
  "brillo": 0-255
}
```

## Instalación

1. Cargar el código `leds.ino` en el ESP32
2. Calibrar los parámetros de brillo
3. Definir patrones de animación
4. Validar sincronización con servidor

## Patrones Especiales

- **Respiración**: Indica status de conexión
- **Parpadeo**: Alerta de condición especial
- **Onda**: Transición entre estados
- **Arco Iris**: Modo de diagnóstico

## Desarrollador

**Igor** - Sistema de Indicadores LED
