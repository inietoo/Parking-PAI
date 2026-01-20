# 🚗 Parking PAI

> **Sistema Inteligente de Estacionamiento con ESP32**
> 
> Un proyecto colaborativo que implementa un sistema de gestión automática de estacionamientos mediante microcontroladores ESP32, sensores IoT y control remoto inteligente.

---

## 📋 Descripción del Proyecto

Parking PAI es una solución completa para la automatización y monitoreo de estacionamientos. El sistema controla dinámicamente las barreras de acceso, indica mediante LEDs la disponibilidad de plazas y mantiene un contador automático actualizado en tiempo real.

**Tecnologías Utilizadas:**
- 🔧 ESP32 (Microcontrolador Principal)
- 🌐 IoT & Conectividad WiFi
- 💾 Base de datos en tiempo real
- ⚡ Lógica de automatización avanzada
- 🔌 Integración de sensores múltiples

---

## 👥 Equipo de Desarrollo

Este proyecto es desarrollado de manera colaborativa entre tres especialistas:

### 🎯 Pol - Control de Barreras
**Responsable del subsistema de acceso**

- Diseño e implementación del control de barreras automáticas
- Integración de servomotores y sistemas de actuación
- Lógica de apertura/cierre sincronizado
- Protocolos de comunicación con el controlador principal
- Validación de seguridad y emergencia

**Componentes Clave:**
```
- Servomotores de alta torque
- Sensores de posición (reed switches)
- Circuitería de control PWM
- Módulo de comunicación I2C/UART
```

---

### 💡 Igor - Sistema de Indicadores LED
**Responsable de la visualización de disponibilidad**

- Desarrollo del sistema de LEDs inteligentes
- Lógica de indicación de plazas libres/ocupadas
- Diseño de patrones visuales intuitivos
- Integración con servidor central
- Optimización de consumo energético

**Componentes Clave:**
```
- Tiras LED direccionables (WS2812B/NeoPixel)
- Drivers de potencia eficientes
- Circuitos de protección
- Control de brillo dinámico
```

---

### 📊 Ivan - Contador Automático de Plazas
**Responsable del sistema de gestión de capacidad**

- Desarrollo del contador inteligente de plazas libres
- Procesamiento de datos de sensores
- Algoritmo de actualización en tiempo real
- Gestión de base de datos
- Dashboard y reportes de ocupación

**Componentes Clave:**
```
- Sensores de presencia (ultrasónicos/PIR)
- Sistema de almacenamiento de datos
- API REST para consultas
- Sincronización con otros subsistemas
```

---

## ⚙️ Arquitectura del Sistema

```
┌─────────────────────────────────────────────────────┐
│              SERVIDOR CENTRAL (Cloud)               │
│           Base de datos en tiempo real               │
└─────────────────────────────────────────────────────┘
         ↑                    ↑                    ↑
         │                    │                    │
      WiFi                 WiFi                 WiFi
         │                    │                    │
    ┌────┴───┐           ┌────┴───┐          ┌────┴───┐
    │ ESP32  │           │ ESP32  │          │ ESP32  │
    │ Pol    │           │ Igor   │          │ Ivan   │
    ├────────┤           ├────────┤          ├────────┤
    │Barreras│           │LEDs    │          │Sensores│
    │Control │           │Indicad │          │Contador│
    │        │           │        │          │        │
    └────────┘           └────────┘          └────────┘
```

---

## 🚀 Guía de Instalación

### Requisitos Previos
- Arduino IDE o PlatformIO
- Driver CH340 para comunicación USB
- Bibliotecas de ESP32 instaladas
- Git para control de versiones

### Pasos de Instalación

```bash
# 1. Clonar el repositorio
git clone https://github.com/inietoo/Parking-PAI.git
cd Parking-PAI

# 2. Instalar dependencias
# Consulta cada carpeta de subsistema para detalles específicos

# 3. Configurar credenciales WiFi
# Editar config.h con tus credenciales

# 4. Subir código a cada ESP32
# Seguir instrucciones en cada carpeta
```

---

## 📁 Estructura del Repositorio

```
Parking-PAI/
├── README.md
├── .gitignore
├── pol_barreras/
│   ├── codigo_principal/
│   ├── esquema_circuito.pdf
│   └── README.md
├── igor_leds/
│   ├── codigo_principal/
│   ├── paleta_colores.md
│   └── README.md
├── ivan_contador/
│   ├── codigo_principal/
│   ├── base_datos/
│   └── README.md
├── documentacion/
│   ├── diagrama_flujo.pdf
│   ├── manual_usuario.md
│   └── especificaciones_tecnicas.md
└── hardware/
    ├── lista_componentes.md
    └── esquemas_montaje.pdf
```

---

## 🔄 Flujo de Trabajo

1. **Detección**: Los sensores detectan entrada/salida de vehículos
2. **Procesamiento**: El contador actualiza disponibilidad
3. **Visualización**: LEDs muestran estado en tiempo real
4. **Control**: Barreras se activan según ocupación
5. **Sincronización**: Datos enviados al servidor central

---

## 📡 Comunicación entre Subsistemas

- **Protocolo**: MQTT + REST API
- **Latencia**: < 100ms
- **Tasa refresco**: 1 segundo
- **Confiabilidad**: Sincronización redundante

---

## 🧪 Testing

```bash
# Ejecutar pruebas unitarias
./run_tests.sh

# Validar conexión
mqtt_sub -h localhost -t 'parking/#'

# Monitoreo en tiempo real
python3 dashboard/monitor.py
```

---

## 📝 Licencia

Este proyecto está licenciado bajo MIT License. Ver `LICENSE` para más detalles.

---

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor:

1. Fork el proyecto
2. Crea una rama para tu feature (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abre un Pull Request

---

## 📞 Contacto & Soporte

- **Issues**: Usar GitHub Issues para reportar bugs
- **Discussions**: Usar GitHub Discussions para preguntas generales
- **Email**: Consultar perfil del equipo

---

## 📊 Estado del Proyecto

- ✅ Arquitectura definida
- 🔄 Desarrollo en progreso
- ⏳ Testing en curso
- 🎯 Próximo: Integración final

---

**Última actualización:** Enero 2026

*Made with ❤️ by Pol, Igor & Ivan*
