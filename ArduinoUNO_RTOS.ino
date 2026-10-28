
/*
 * Proyecto: FreeRTOS en Arduino UNO - Version 2
 * Plataforma: Arduino UNO (ATmega328P)
 * Biblioteca: Arduino_FreeRTOS
 *
 * Se agrega una tercera tarea para controlar otro LED.
 */

#include <Arduino_FreeRTOS.h>

// Pines de los LEDs
#define LED_CRITICO 8
#define LED_TELEMETRIA 9
#define LED_ADICIONAL 10

// Prototipos de las tareas
void TaskCritica(void *pvParameters);
void TaskTelemetria(void *pvParameters);
void TaskAdicional(void *pvParameters);

void setup() {
  Serial.begin(9600);

  // Configurar los LEDs como salidas
  pinMode(LED_CRITICO, OUTPUT);
  pinMode(LED_TELEMETRIA, OUTPUT);
  pinMode(LED_ADICIONAL, OUTPUT);

  Serial.println("Iniciando FreeRTOS con 3 tareas...");

  // Tarea critica - Prioridad alta
  xTaskCreate(TaskCritica, "Critica", 128, NULL, 2, NULL);

  // Tarea de telemetria - Prioridad baja
  xTaskCreate(TaskTelemetria, "Telemetria", 128, NULL, 1, NULL);

  // Nueva tarea - Prioridad baja
  xTaskCreate(TaskAdicional, "Adicional", 128, NULL, 1, NULL);

  // Iniciar FreeRTOS
  vTaskStartScheduler();

  // Si no inicia, puede ser por falta de memoria
  Serial.println("Error al iniciar FreeRTOS");
}

void loop() {
  // FreeRTOS controla las tareas
}

// Tarea 1: LED del pin 8
void TaskCritica(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    digitalWrite(LED_CRITICO, !digitalRead(LED_CRITICO));
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

// Tarea 2: LED del pin 9
void TaskTelemetria(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    digitalWrite(LED_TELEMETRIA, !digitalRead(LED_TELEMETRIA));
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

// Tarea 3: LED del pin 10 (nueva)
void TaskAdicional(void *pvParameters) {
  (void) pvParameters;

  for (;;) {
    digitalWrite(LED_ADICIONAL, !digitalRead(LED_ADICIONAL));
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
