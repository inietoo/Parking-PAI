/*
 * ============================================================================
 * PROYECTO: Parking-PAI
 * MÓDULO: Detector de Plazas (Igor) + Conexión WiFi GenCat
 * ============================================================================
 */


#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "esp_wpa2.h" // Se usa la librería clásica (ignorar aviso 'deprecated')


// ============================================================================
// CONFIGURACIÓN DE RED Y SERVIDOR
// ============================================================================
const char* ssid = "gencat_ENS_EDU"; // Nombre de la red WiFi
#define EAP_IDENTITY "W43007257"     // Usuario
#define EAP_PASSWORD "zhz0ot1par"    // Contraseña


const String SERVER_URL = "http://192.168.3.249:8080/api/parking";


// Datos de ESTA plaza
const int PLAZA_ID = 6;
const String PLAZA_ZONA = "C";


// ============================================================================
// CONFIGURACIÓN DE PINES
// ============================================================================
const int PIN_TRIG = 5;
const int PIN_ECHO = 18;
const int PIN_ROJO = 23;  
const int PIN_VERDE = 22; 


// ============================================================================
// VARIABLES GLOBALES
// ============================================================================
const int DISTANCIA_OCUPADO = 20; // cm
unsigned long tiempoAnterior = 0;
const long INTERVALO_LECTURA = 200; 


// Control de estado para enviar petición solo al cambiar
bool estaLibreAnterior = true; 
bool primeraEjecucion = true;


// ============================================================================
// SETUP
// ============================================================================
void setup() {
  Serial.begin(115200);
  
  // 1. Configurar Pines
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_ROJO, OUTPUT);
  pinMode(PIN_VERDE, OUTPUT);
  
  digitalWrite(PIN_ROJO, HIGH);   // Apagado (Ánodo común)
  digitalWrite(PIN_VERDE, HIGH);  // Apagado (Ánodo común)


  // 2. Conexión WiFi WPA2 Enterprise (GenCat)
  Serial.println("\n\nConectando a WiFi (WPA2 Enterprise)...");
  
  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  
  // Configuración de credenciales empresariales
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
  esp_wifi_sta_wpa2_ent_enable();
  
  WiFi.begin(ssid);


  // Esperar conexión
  int contador = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    contador++;
    if(contador > 40) { // Si tarda más de 20 segs
         Serial.println("\nNo se pudo conectar. Reiniciando...");
         ESP.restart();
    }
  }


  Serial.println("");
  Serial.println("WiFi Conectado!");
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP()); 


  // 3. Test rápido de LEDs
  digitalWrite(PIN_ROJO, LOW); delay(500); digitalWrite(PIN_ROJO, HIGH);
  digitalWrite(PIN_VERDE, LOW); delay(500); digitalWrite(PIN_VERDE, HIGH);
}


// ============================================================================
// LÓGICA DEL SENSOR
// ============================================================================
int leerDistancia() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  long duracion = pulseIn(PIN_ECHO, HIGH, 30000);
  return duracion * 0.034 / 2;
}


// ============================================================================
// ENVIAR POST AL SERVIDOR
// ============================================================================
void enviarEstadoAlServidor(bool estaLibre) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(SERVER_URL);
    http.addHeader("Content-Type", "application/json");


    // Construir JSON manualmente
    String estadoBool = estaLibre ? "true" : "false";
    String jsonPayload = "{\"id\": " + String(PLAZA_ID) + 
                         ", \"zone\": \"" + PLAZA_ZONA + 
                         "\", \"free\": " + estadoBool + "}";


    Serial.print("Enviando POST: ");
    Serial.println(jsonPayload);


    int httpResponseCode = http.POST(jsonPayload);


    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("Codigo respuesta: ");
      Serial.println(httpResponseCode); 
    } else {
      Serial.print("Error en el envio: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Error: WiFi desconectado");
  }
}


// ============================================================================
// BUCLE PRINCIPAL
// ============================================================================
void loop() {
  unsigned long tiempoActual = millis();


  if (tiempoActual - tiempoAnterior >= INTERVALO_LECTURA) {
    tiempoAnterior = tiempoActual;


    int distancia = leerDistancia();
    bool estaLibreActual = true;


    // Lógica del semáforo
    if (distancia > 0 && distancia < DISTANCIA_OCUPADO) {
      // Ocupado
      digitalWrite(PIN_ROJO, LOW);   // Encender
      digitalWrite(PIN_VERDE, HIGH); // Apagar
      estaLibreActual = false;
    } else {
      // Libre
      digitalWrite(PIN_ROJO, HIGH); // Apagar
      digitalWrite(PIN_VERDE, LOW); // Encender
      estaLibreActual = true;
    }


    // Comprobar si ha cambiado el estado para enviar al servidor
    if (estaLibreActual != estaLibreAnterior || primeraEjecucion) {
      Serial.print("Cambio de estado detectado. Distancia: ");
      Serial.println(distancia);
      
      enviarEstadoAlServidor(estaLibreActual);
      
      estaLibreAnterior = estaLibreActual;
      primeraEjecucion = false;
    }
  }
}
