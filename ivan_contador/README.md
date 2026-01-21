# 📊 Ivan - Contador Automático de Plazas

## Descripción del Subsistema

Este módulo es responsable de mantener un registro actualizado en tiempo real de las plazas de estacionamiento disponibles. Procesa datos de sensores, mantiene una base de datos sincronizada y proporciona acceso a la información mediante una API REST desarrollada en Spring Boot.

## Funcionalidades Principales

- **Contador Inteligente**: Sistema de conteo automático de plazas libres y ocupadas
- **Consulta por Zonas**: Obtener disponibilidad de plazas por zona (Zona A, B, C)
- **APIs REST**: Endpoints para consultar disponibilidad en tiempo real
- **Modelo de Datos**: Estructura POJO para gestionar información de plazas
- **Filtrado de Datos**: Validación de información de sensores

## Tecnología Utilizada

- **Framework**: Spring Boot
- **Lenguaje**: Java
- **Build Tool**: Maven
- **API**: REST Controllers con Spring Web

## Estructura de Carpetas

```
ivan_contador/
├-- README.md (Este archivo)
├-- parkingapi/ (Aplicación Spring Boot principal)
│   ├-- src/
│   │   ├-- main/
│   │   │   ├-- java/org/test/parkingapi/
│   │   │   │   ├-- ParkingapiApplication.java (Clase principal)
│   │   │   │   ├-- FreeSpotController.java (Controlador principal)
│   │   │   │   ├-- ParkingSpot.java (Modelo de dato)
│   │   │   │   └-- TestController.java (Controlador de prueba)
│   │   │   └-- resources/
│   │   └-- test/
│   ├-- pom.xml (Configuración Maven)
│   ├-- mvnw (Maven Wrapper)
│   ├-- mvnw.cmd (Maven Wrapper Windows)
└-- target/ (Compilados)
```

## Modelo de Datos: ParkingSpot

La clase `ParkingSpot` representa una plaza de estacionamiento con los siguientes atributos:

- `id` (int): Identificador único de la plaza
- `zone` (String): Zona de la plaza (A, B, C)
- `free` (boolean): Estado de disponibilidad de la plaza

### Constructores y Métodos

```java
public ParkingSpot(int id, String zone, boolean free)
public int getId()
public String getZone()
public boolean isFree()
```

## APIs Disponibles

### 1. Obtener total de plazas libres

```
GET /freespot
Response: int (Número total de plazas libres)
Ejemplo: 2
```

### 2. Obtener plazas libres en Zona A

```
GET /freespot/zoneA
Response: int (Número de plazas libres en Zona A)
Ejemplo: 1
```

### 3. Obtener plazas libres en Zona B

```
GET /freespot/zoneB
Response: int (Número de plazas libres en Zona B)
Ejemplo: 0
```

### 4. Obtener plazas libres en Zona C

```
GET /freespot/zoneC
Response: int (Número de plazas libres en Zona C)
Ejemplo: 1
```

### 5. Endpoint de Prueba

```
GET /hello
Response: "Hola desde la API del parking api"
```

## Ejemplo de Uso

### Consultar total de plazas disponibles

```bash
curl http://localhost:8080/freespot
```

### Consultar disponibilidad por zona

```bash
curl http://localhost:8080/freespot/zoneA
curl http://localhost:8080/freespot/zoneB
curl http://localhost:8080/freespot/zoneC
```

## Controladores

### FreeSpotController

Controlador principal que maneja todas las peticiones relacionadas con plazas disponibles.

**Métodos**:
- `getFreeSpotsCount()`: Devuelve el total de plazas libres
- `getFreeSpots()`: Retorna la lista de plazas (usado internamente)
- `getZoneCountA()`: Devuelve plazas libres en Zona A
- `getZoneCountB()`: Devuelve plazas libres en Zona B
- `getZoneCountC()`: Devuelve plazas libres en Zona C

### TestController

Controlador de prueba para verificar que la aplicación esté en funcionamiento.

**Métodos**:
- `hello()`: Retorna un mensaje de saludo

## Cómo Ejecutar la Aplicación

### Mediante Maven

```bash
cd parkingapi
mvn spring-boot:run
```

### Compilar el proyecto

```bash
cd parkingapi
mvn clean package
```

### Ejecutar el JAR generado

```bash
java -jar target/parkingapi-0.0.1-SNAPSHOT.jar
```

La aplicación se ejecutará en `http://localhost:8080`

## Datos de Ejemplo

Por el momento, la aplicación utiliza datos estáticos en memoria para las pruebas:

```java
List<ParkingSpot> spots = Arrays.asList(
    new ParkingSpot(1, "A", true),   // Plaza 1, Zona A, Libre
    new ParkingSpot(2, "B", false),  // Plaza 2, Zona B, Ocupada
    new ParkingSpot(3, "C", true)    // Plaza 3, Zona C, Libre
);
```

## Próximas Mejoras

- Integración con base de datos (JPA/Hibernate)
- Endpoints POST para actualizar estado de plazas
- Autenticación y autorización
- Sincronización en tiempo real con sensores ESP32
- Endpoint para registrar eventos de entrada/salida
- Generación de reportes estadísticos
- Validación de transiciones de estado de plazas

## Notas de Desarrollo

- El proyecto actualmente utiliza datos estáticos para fines de desarrollo y prueba
- Los datos se regeneran en cada petición
- Se recomienda migrar a una base de datos real para productión
- Los nombres de zonas (A, B, C) están predefinidos en el código

## Contacto

Para más información sobre este subsistema, consulta la documentación del proyecto principal en `/Parking-PAI`
