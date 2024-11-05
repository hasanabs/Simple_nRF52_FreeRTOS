/*
 * ######## FreeRTOS porting template for nRF52 chip ########
 * (c) 2024 by Hasan Albinsaid (https://github.com/hasanabs/)
 *
 * This example demonstrates blinking an LED in Low Power mode. The idea is to enter sleep mode
 * whenever there are no tasks to process (idle), minimizing power consumption. The tick
 * config is set up in `low_power_config.cpp`, and can be modified to suit specific requirements.
 *
 * In this example, an interrupt is generated every 100 ticks, where each tick defined as 10 ms.
 * Therefore, `vTaskDelay(1)` results in a 1-second idle period. For instance, if 1 tick were set to
 * 100 ms, then `vTaskDelay(5)` would result in a 500 ms idle period.
 *
 * Note: The interrupt clock is defined to occur every 100 ticks (1 second), so a `vTaskDelay` value
 * of 1 corresponds to 1 second (minimum delay).
 */

#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include "low_power_config.h" //Preconfig for low power in vTaskDelay if there is no other task to run.

#define pinLed1 27

// First task routine
void TaskBlink1(void *pvParameters)
{
  (void)pvParameters;
  pinMode(pinLed1, OUTPUT);
  for (;;)
  {
    digitalWrite(pinLed1, HIGH);
    vTaskDelay(1); // interrupt clock defined as 100 ticks (1 s), hence 1 here means 1 s (minimum amount)
    digitalWrite(pinLed1, LOW);
    vTaskDelay(1); // delay(x ms) is still can be used as the standard Arduino, but it is a blocking function.
  }
}

void setup()
{
  xTaskCreate(TaskBlink1, "Blink1", 256, NULL, 1, NULL); // Task 1 initialization
  vTaskStartScheduler();                                 // Start the scheduler
}

void loop()
{
  // No code here, as FreeRTOS handles the execution flow.
}
