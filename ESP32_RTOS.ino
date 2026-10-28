
/*
 * Proyecto: FreeRTOS en ESP32 - Version 2
 * Plataforma: ESP32-WROOM-32
 * Sistema: FreeRTOS nativo
 *
 * Se agrega una tercera tarea para controlar
 * un LED externo conectado al GPIO 18.
 */

#include <Arduino.h>

// Pines de los LEDs
#define LED_CRITICO 2
#define LED_ADICIONAL 18

// Tarea 1: LED azul integrado - Prioridad alta
void TaskCritica(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    digitalWrite(LED_CRITICO, !digitalRead(LED_CRITICO));
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

// Tarea 2: Telemetria - Prioridad baja
void TaskTelemetria(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    Serial.println("Telemetria enviada desde el Core 0");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

// Tarea 3: LED externo - Prioridad baja
void TaskAdicional(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    digitalWrite(LED_ADICIONAL, !digitalRead(LED_ADICIONAL));
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  Serial.begin(115200);

  // Configurar pines como salidas
  pinMode(LED_CRITICO, OUTPUT);
  pinMode(LED_ADICIONAL, OUTPUT);

  Serial.println("Iniciando FreeRTOS con 3 tareas...");

  // Tarea critica en Core 1 - Prioridad 2
  xTaskCreatePinnedToCore(
    TaskCritica,
    "Critica",
    2048,
    NULL,
    2,
    NULL,
    1
  );

  // Tarea telemetria en Core 0 - Prioridad 1
  xTaskCreatePinnedToCore(
    TaskTelemetria,
    "Telemetria",
    4096,
    NULL,
    1,
    NULL,
    0
  );

  // Nueva tarea en Core 1 - Prioridad 1
  xTaskCreatePinnedToCore(
    TaskAdicional,
    "Adicional",
    2048,
    NULL,
    1,
    NULL,
    1
  );
}

void loop() {
  // FreeRTOS administra las tareas
  vTaskDelay(pdMS_TO_TICKS(1000));
}
