/*
 * ============================================================================
 * PROYECTO: Parking-PAI
 * MÓDULO: Detector de Plazas de Parking (Luz Roja/Verde)
 * DESCRIPCIÓN: Sistema de semáforo para indicar si una plaza está ocupada
 *              usando un sensor ultrasónico HC-SR04 y un LED RGB.
 * 
 * HARDWARE UTILIZADO:
 *   - ESP32 DevKit V1
 *   - Sensor ultrasónico HC-SR04 (5V)
 *   - LED RGB (Ánodo Común)
 *   - Resistencias 220Ω (x2) para el LED
 *   - Resistencias para divisor de voltaje (opcional)
 * ============================================================================
 */

#include <Arduino.h>

// ============================================================================
// CONFIGURACIÓN DE PINES
// ============================================================================
// Sensor Ultrasónico
const int PIN_TRIG = 5;     // GPIO5 - Pin Trigger (envía el pulso)
const int PIN_ECHO = 18;    // GPIO18 - Pin Echo (recibe el rebote)

// LED RGB (Ánodo Común - pata larga a 3V3)
const int PIN_ROJO = 22;    // GPIO23 - Pata Roja del LED
const int PIN_VERDE = 23;   // GPIO22 - Pata Verde del LED

// ============================================================================
// PARÁMETROS DE FUNCIONAMIENTO
// ============================================================================
// Si detectamos un objeto a menos de esta distancia, la plaza está OCUPADA
const int DISTANCIA_OCUPADO = 20;  // 20 cm (ajustable según altura del techo)

// ============================================================================
// VARIABLES GLOBALES
// ============================================================================
// Para lectura no bloqueante del sensor (multitarea)
unsigned long tiempoAnterior = 0;
const long INTERVALO_LECTURA = 200;  // Leer cada 200ms (evita saturar Serial)

// ============================================================================
// FUNCIÓN: setup()
// Descripción: Se ejecuta UNA SOLA VEZ al encender el ESP32
// Tareas: Inicializar pines, Serial y hacer test del LED
// ============================================================================
void setup() {
  // Inicializar comunicación serial (para Debug en Monitor Serie)
  Serial.begin(115200);
  Serial.println("\n========================================");
  Serial.println("   PARKING-PAI: Sistema de Semáforo");
  Serial.println("   Módulo: Detector de Plazas");
  Serial.println("========================================\n");

  // Configurar pines del sensor como entrada/salida
  pinMode(PIN_TRIG, OUTPUT);    // TRIGGER: enviamos pulsos (salida)
  pinMode(PIN_ECHO, INPUT);     // ECHO: recibimos señal (entrada)

  // Configurar pines del LED como salida
  pinMode(PIN_ROJO, OUTPUT);
  pinMode(PIN_VERDE, OUTPUT);

  // Apagar ambos colores (en Ánodo Común, HIGH = apagado)
  digitalWrite(PIN_ROJO, HIGH);
  digitalWrite(PIN_VERDE, HIGH);

  // ---- TEST DE HARDWARE AL ARRANCAR ----
  // Esto sirve para verificar que el LED está bien conectado
  Serial.println("[TEST] Encendiendo LED ROJO...");
  digitalWrite(PIN_ROJO, LOW);  // LOW = Encender en Ánodo Común
  delay(1000);                  // Esperar 1 segundo
  digitalWrite(PIN_ROJO, HIGH); // HIGH = Apagar

  Serial.println("[TEST] Encendiendo LED VERDE...");
  digitalWrite(PIN_VERDE, LOW); // LOW = Encender
  delay(1000);
  digitalWrite(PIN_VERDE, HIGH); // HIGH = Apagar

  Serial.println("[OK] Hardware listo. Iniciando detección de plazas...\n");
}

// ============================================================================
// FUNCIÓN: leerDistancia()
// Descripción: Obtiene la distancia en cm usando el sensor HC-SR04
// Retorna: Distancia en centímetros (int)
// Notas: Usa la fórmula: Distancia = (Tiempo × Velocidad del Sonido) / 2
// ============================================================================
int leerDistancia() {
  // 1. PREPARACIÓN: Limpiar el pin TRIGGER (LOW durante 2us)
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);

  // 2. DISPARO: Enviar pulso ultrasónico (HIGH durante 10us)
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  // 3. LECTURA: Esperar a que ECHO se ponga HIGH y medir duración
  // Parámetros: pin, nivel a esperar (HIGH), timeout (30ms)
  // Si no hay respuesta en 30ms, asumimos que el sensor no detecta nada
  long duracion = pulseIn(PIN_ECHO, HIGH, 30000);

  // 4. CÁLCULO: Convertir tiempo en distancia
  // Velocidad del sonido ≈ 0.034 cm/microsegundo
  // Divide por 2 porque el sonido va y vuelve (ida y vuelta)
  int distancia = duracion * 0.034 / 2;

  return distancia;
}

// ============================================================================
// FUNCIÓN: actualizarSemaforoParking()
// Descripción: Actualiza el estado del LED según la distancia detectada
// Parámetro: distancia en cm
// Lógica:
//   - Si distancia < DISTANCIA_OCUPADO → Plaza OCUPADA (ROJO)
//   - Si distancia >= DISTANCIA_OCUPADO → Plaza LIBRE (VERDE)
// ============================================================================
void actualizarSemaforoParking(int distancia) {
  if (distancia > 0 && distancia < DISTANCIA_OCUPADO) {
    // ---- PLAZA OCUPADA: ENCENDER ROJO ----
    digitalWrite(PIN_ROJO, LOW);   // LOW = Encender (Ánodo Común)
    digitalWrite(PIN_VERDE, HIGH); // HIGH = Apagar
    Serial.println("[OCUPADO] Plaza detectada. LED ROJO encendido.");
  } 
  else {
    // ---- PLAZA LIBRE: ENCENDER VERDE ----
    digitalWrite(PIN_ROJO, HIGH);  // HIGH = Apagar
    digitalWrite(PIN_VERDE, LOW);  // LOW = Encender (Ánodo Común)
    Serial.println("[LIBRE] Plaza disponible. LED VERDE encendido.");
  }
}

// ============================================================================
// FUNCIÓN: loop()
// Descripción: Se ejecuta continuamente (infinito)
// Tareas: Leer sensor, mostrar datos, controlar LED
// ============================================================================
void loop() {
  // Obtener tiempo actual en milisegundos
  unsigned long tiempoActual = millis();

  // Ejecutar solo si han pasado INTERVALO_LECTURA ms desde la última lectura
  // Esto permite que otros procesos (WiFi, MQTT, etc.) no se congelen
  if (tiempoActual - tiempoAnterior >= INTERVALO_LECTURA) {
    tiempoAnterior = tiempoActual;

    // --- LECTURA DEL SENSOR ---
    int distancia = leerDistancia();

    // --- MOSTRAR DATOS EN MONITOR SERIE (DEBUG) ---
    Serial.print("Distancia detectada: ");
    Serial.print(distancia);
    Serial.println(" cm");

    // --- ACTUALIZAR ESTADO DEL SEMÁFORO ---
    actualizarSemaforoParking(distancia);
  }
}
