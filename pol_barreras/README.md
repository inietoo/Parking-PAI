# 🎯 Pol - Control de Barreras

## Descripción del Subsistema

Este módulo es responsable del control automático de las barreras de acceso del estacionamiento. Implementa la lógica de apertura y cierre sincronizado basada en los datos recibidos del servidor central.

### Funcionalidades Principales

- **Control de Servomotores**: Control PWM de alta precisión
- **Detección de Posición**: Uso de reed switches para validar estado
- **Protocolos de Comunicación**: I2C/UART con el controlador principal
- **Lógica de Seguridad**: Protección ante fallas y emergencias
- **Validación de Acceso**: Verificación antes de permitir paso

## Componentes de Hardware

```
Servomotores MG996R (x2)
Reed Switches
Módulo de Control PWM
Diodos de protección
Capacitores de estabilización
```

## Estructura de Carpetas

```
pol_barreras/
├── README.md (Este archivo)
├── codigo_principal/
│   ├── barreras.ino
│   ├── control_pwm.h
│   ├── sensores.h
│   └── comunicacion.h
├── esquema_circuito.pdf
└── pruebas/
    └── test_barreras.cpp
```

## Protocolo de Comunicación

### Mensajes Recibidos
```json
{
  "comando": "abrir" | "cerrar",
  "tiempo_espera": 5000,
  "validar_posicion": true
}
```

### Estados Reportados
```json
{
  "estado": "abierto" | "cerrado" | "error",
  "posicion_actual": 0-180,
  "sensores": {
    "reed1": true,
    "reed2": false
  }
}
```

## Instalación

1. Cargar el código `barreras.ino` en el ESP32
2. Calibrar los servomotores
3. Validar los reed switches
4. Probar la comunicación con el servidor

## Desarrollador

**Pol** - Sistema de Control de Barreras
