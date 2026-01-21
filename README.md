# 🚗 Parking PAI

> **Sistema Inteligente de Estacionamiento con ESP32**
> 
> Proyecto colaborativo de gestión automática de estacionamientos mediante microcontroladores ESP32, sensores ultrasónicos y API REST.

---

## 📋 Descripción del Proyecto

Parking PAI es un sistema modular para la automatización y monitoreo de estacionamientos. Cada módulo funciona de forma independiente y está diseñado para integrarse en un sistema completo de gestión de plazas de parking.

**Tecnologías Utilizadas:**
- 🔧 ESP32 (Microcontrolador)
- 📡 Sensores Ultrasónicos HC-SR04
- 💡 LEDs RGB para indicadores visuales
- ☕ Spring Boot (Backend API REST)
- 🔌 Servomotores para control de barreras

---

## 👥 Equipo de Desarrollo

### 🎯 Pol - Control de Barreras
**Responsable del subsistema de acceso automático**

Implementa el control de barreras mediante servomotores y sensores reed switch para validar el estado de apertura/cierre.

**Componentes:**
- Servomotores MG996R
- Reed Switches para detección de posición
- Control PWM con ESP32

**Estado Actual:** 
- ✅ Código físico para control de barrera implementado
- 📁 Archivo: `pol_barreras/Codi_fisic1`

---

### 💡 Igor - Sistema de Indicadores LED
**Responsable de la detección y señalización de plazas**

Sistema de detección automática de disponibilidad de plazas mediante sensor ultrasónico HC-SR04 y LED RGB. Indica visualmente el estado de cada plaza en tiempo real.

**Características Implementadas:**
- 🟢 LED Verde: Plaza libre (distancia ≥ 20 cm)
- 🔴 LED Rojo: Plaza ocupada (distancia < 20 cm)
- 📊 Lectura no bloqueante cada 200ms
- 🔍 Test automático de hardware al inicio
- 📡 Comunicación serial para monitoreo

**Componentes:**
- ESP32 DevKit V1
- Sensor Ultrasónico HC-SR04 (rango 2-400 cm)
- LED RGB de ánodo común

**Estado Actual:**
- ✅ Sistema completamente funcional
- 📁 Archivo: `igor_leds/igor_leds.ino`

---

### 📊 Ivan - Contador y API REST
**Responsable del backend y gestión de datos**

API REST desarrollada en Spring Boot que proporciona información sobre la disponibilidad de plazas por zonas. Sistema de conteo y consulta de plazas libres.

**Endpoints Disponibles:**
```
GET /freespot          → Total de plazas libres
GET /freespot/zoneA    → Plazas libres en Zona A
GET /freespot/zoneB    → Plazas libres en Zona B
GET /freespot/zoneC    → Plazas libres en Zona C
GET /hello             → Test de funcionamiento
```

**Tecnología:**
- Spring Boot + Java
- Maven para gestión de dependencias
- Modelo de datos con POJOs
- Datos en memoria (desarrollo)

**Estado Actual:**
- ✅ API REST completamente funcional
- ✅ Endpoints de consulta por zona implementados
- 📁 Directorio: `ivan_contador/parkingapi/`

---

## 📁 Estructura del Repositorio

```
Parking-PAI/
├── README.md                    # Este archivo
├── pol_barreras/
│   ├── README.md               # Documentación del módulo
│   └── Codi_fisic1             # Código control de barrera
├── igor_leds/
│   ├── README.md               # Documentación detallada
│   └── igor_leds.ino           # Código ESP32 completo
└── ivan_contador/
    ├── README.md               # Documentación de la API
    └── parkingapi/             # Aplicación Spring Boot
        ├── src/
        │   └── main/java/org/test/parkingapi/
        │       ├── ParkingapiApplication.java
        │       ├── FreeSpotController.java
        │       ├── ParkingSpot.java
        │       └── TestController.java
        ├── pom.xml
        └── mvnw
```

---

## 🚀 Instalación y Uso

### Módulo de Igor (Sistema LED)

1. **Requisitos:**
   - Arduino IDE 1.8.0+
   - Drivers CH340
   - Librería ESP32

2. **Conexiones:**
   ```
   HC-SR04:  VCC→5V, GND→GND, TRIG→GPIO5, ECHO→GPIO18
   LED RGB:  Rojo→GPIO23, Verde→GPIO22, Ánodo→3V3, Cátodo→GND
   ```

3. **Cargar código:**
   ```bash
   # Abrir igor_leds/igor_leds.ino en Arduino IDE
   # Seleccionar Board: ESP32 Dev Module
   # Seleccionar Port: COM[X]
   # Upload (Ctrl + U)
   ```

4. **Monitorizar:**
   ```bash
   # Abrir Serial Monitor a 115200 baud
   ```

### Módulo de Ivan (API REST)

1. **Requisitos:**
   - Java 17+
   - Maven

2. **Ejecutar aplicación:**
   ```bash
   cd ivan_contador/parkingapi
   mvn spring-boot:run
   ```

3. **Probar endpoints:**
   ```bash
   curl http://localhost:8080/freespot
   curl http://localhost:8080/freespot/zoneA
   ```

### Módulo de Pol (Barreras)

1. Consultar documentación específica en `pol_barreras/README.md`
2. Cargar el código `Codi_fisic1` en el ESP32
3. Calibrar servomotores según especificaciones

---

## 🔧 Configuración

### Parámetros Ajustables (Módulo Igor)

```cpp
// En igor_leds.ino
const int DISTANCIA_OCUPADO = 20;     // Umbral de detección (cm)
const int INTERVALO_LECTURA = 200;    // Frecuencia de lectura (ms)
```

### Datos de Prueba (API Ivan)

La API actualmente utiliza datos estáticos en memoria:
```java
// Zona A: 1 plaza libre
// Zona B: 0 plazas libres  
// Zona C: 1 plaza libre
// Total: 2 plazas libres
```

---

## 📊 Funcionamiento del Sistema

### Flujo de Detección (Módulo Igor)

```
1. Sensor HC-SR04 emite pulso ultrasónico cada 200ms
2. Mide distancia del objeto detectado
3. Si distancia < 20cm → LED ROJO (ocupado)
4. Si distancia ≥ 20cm → LED VERDE (libre)
5. Envía datos por serial para monitoreo
```

### API de Consulta (Módulo Ivan)

```
Cliente → GET /freespot/zoneA → API procesa → Retorna conteo
```

---

## 🧪 Testing

### Test del Sistema LED

El código incluye test automático:
1. LED ROJO encendido 1 segundo
2. LED VERDE encendido 1 segundo
3. Inicio de detección continua

### Test de la API

```bash
# Verificar que la API está funcionando
curl http://localhost:8080/hello

# Obtener plazas totales
curl http://localhost:8080/freespot

# Verificar zonas individuales
curl http://localhost:8080/freespot/zoneA
curl http://localhost:8080/freespot/zoneB
curl http://localhost:8080/freespot/zoneC
```

---

## 🛠️ Troubleshooting

### Módulo LED no funciona
- Verificar conexiones GPIO (5, 18, 22, 23)
- Comprobar alimentación 5V del HC-SR04
- Verificar baudrate 115200 en monitor serial
- Limpiar superficie del sensor ultrasónico

### API no responde
- Verificar que Java 17+ está instalado
- Comprobar que el puerto 8080 está libre
- Revisar logs de Spring Boot
- Ejecutar `mvn clean install` antes de `mvn spring-boot:run`

---

## 📚 Documentación Adicional

Cada módulo tiene su propia documentación detallada:

- **Pol (Barreras):** `pol_barreras/README.md`
- **Igor (LEDs):** `igor_leds/README.md` - Documentación completa con esquemas
- **Ivan (API):** `ivan_contador/README.md` - Especificación de endpoints

---

## 🔮 Próximos Pasos

- [ ] Integrar módulo de barreras con API central
- [ ] Conectar sistema LED con API de Ivan vía WiFi
- [ ] Implementar base de datos persistente (MySQL/PostgreSQL)
- [ ] Añadir autenticación a la API
- [ ] Desarrollar interfaz web de administración
- [ ] Integración completa entre los tres módulos
- [ ] Sistema de notificaciones en tiempo real

---

## 📝 Licencia

Este proyecto está licenciado bajo MIT License.

---

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor:

1. Fork el proyecto
2. Crea una rama para tu feature (`git checkout -b feature/NuevaFuncionalidad`)
3. Commit tus cambios (`git commit -m 'Añadir nueva funcionalidad'`)
4. Push a la rama (`git push origin feature/NuevaFuncionalidad`)
5. Abre un Pull Request

---

## 📞 Contacto

Para reportar problemas o hacer consultas:
- 📋 **Issues**: [GitHub Issues](https://github.com/inietoo/Parking-PAI/issues)
- 💬 **Discussions**: [GitHub Discussions](https://github.com/inietoo/Parking-PAI/discussions)

---

## 📊 Estado del Proyecto

| Módulo | Estado | Progreso |
|--------|--------|----------|
| Igor - Sistema LED | ✅ Funcional | 100% |
| Ivan - API REST | ✅ Funcional | 100% |
| Pol - Barreras | 🔄 En desarrollo | 70% |
| Integración | ⏳ Pendiente | 0% |

---

**Última actualización:** Enero 2026

*Desarrollado con ❤️ por Pol, Igor e Ivan*
