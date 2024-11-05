/*
 * ######## FreeRTOS Porting Template for nRF52 Chip ########
 * (c) 2024 by Hasan Albinsaid (https://github.com/hasanabs/)
 *
 * This example demonstrates two LEDs blinking at different intervals.
 * Here, `configTICK_RATE_HZ` is set to 100, so each tick represents 10 ms.
 * Therefore, `vTaskDelay(50)` results in an idle period of 500 ms.
 */

#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>

#define pinLed1 27
#define pinLed2 28

// First task routine
void TaskBlink1(void *pvParameters)
{
  (void)pvParameters;
  pinMode(pinLed1, OUTPUT);
  for (;;)
  {
    digitalWrite(pinLed1, HIGH);
    vTaskDelay(50);
    digitalWrite(pinLed1, LOW);
    vTaskDelay(50);
  }
}

// Second task routine
void TaskBlink2(void *pvParameters)
{
  (void)pvParameters;
  pinMode(pinLed2, OUTPUT);
  for (;;)
  {
    digitalWrite(pinLed2, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Another way to define (means 1000 ms)
    digitalWrite(pinLed2, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  xTaskCreate(TaskBlink1, "Blink1", 256, NULL, 1, NULL); // Task 1 initialization
  xTaskCreate(TaskBlink2, "Blink2", 256, NULL, 2, NULL); // Task 2 initialization
  vTaskStartScheduler();                                 // Start the scheduler
}

void loop()
{
  // No code here, as FreeRTOS handles the execution flow.
}
