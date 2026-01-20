# 📊 Ivan - Contador Automático de Plazas

## Descripción del Subsistema

Este módulo es responsable de mantener un registro actualizado en tiempo real de las plazas de estacionamiento disponibles. Procesa datos de sensores, mantiene una base de datos sincronizada y proporciona acceso a la información mediante APIs.

### Funcionalidades Principales

- **Contador Inteligente**: Incrementa/decrementa según entradas/salidas detectadas
- **Procesamiento de Datos**: Filtrado y validación de información de sensores
- **Almacenamiento**: Base de datos en tiempo real con sincronización
- **APIs REST**: Endpoints para consultar disponibilidad
- **Reportes**: Historial de ocupación y estadísticas

## Componentes de Hardware

```
Sensores Ultrasónicos HC-SR04
Sensores PIR (Infrarrojo Pasivo)
Módulo de Almacenamiento SD/EEPROM
Conectores I2C/SPI
Fuentes de alimentación reguladas
```

## Estructura de Carpetas

```
ivan_contador/
├── README.md (Este archivo)
├── codigo_principal/
│   ├── contador.ino
│   ├── sensores.h
│   ├── base_datos.h
│   └── api_rest.h
├── base_datos/
│   ├── schema.sql
│   └── migraciones.sql
└── pruebas/
    └── test_contador.cpp
```

## Protocolo de Comunicación

### Eventos de Detección
```json
{
  "tipo": "entrada" | "salida",
  "timestamp": "2024-01-20T19:00:00Z",
  "sensor": "sensor_1",
  "validado": true
}
```

### Estado Actual
```json
{
  "plazas_disponibles": 15,
  "plazas_totales": 50,
  "ocupancia_porcentaje": 70,
  "ultima_actualizacion": "2024-01-20T19:00:00Z"
}
```

## APIs Disponibles

### Obtener disponibilidad actual
```
GET /api/plazas/disponibles
Response: {"plazas": 15, "total": 50, "ocupancia": 70}
```

### Obtener historial
```
GET /api/plazas/historial?dias=7
Response: [{...}, {...}, ...]
```

### Registrar evento
```
POST /api/eventos/registrar
Body: {"tipo": "entrada", "sensor": "sensor_1"}
```

## Algoritmo de Detección

1. **Lectura de Sensores**: Muestreo cada 100ms
2. **Filtrado**: Eliminación de lecturas erróneas
3. **Validación de Transición**: Confirmación de cambio de estado
4. **Actualización**: Incremento/decremento de contador
5. **Sincronización**: Envío a servidor central

## Calibración

```bash
# Establecer plazas totales
POST /api/admin/calibrar
{"plazas_totales": 50}

# Resetear contador
POST /api/admin/resetear
{"confirmacion": true}
```

## Instalación

1. Instalar bibliotecas de sensores en Arduino IDE
2. Cargar `contador.ino` en el ESP32
3. Calibrar sensores
4. Configurar credenciales WiFi
5. Validar sincronización con API

## Desarrollador

**Ivan** - Sistema de Contador Automático de Plazas
