#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

static constexpr size_t kArraySize = 64;
static int g_numbers[kArraySize];
static SemaphoreHandle_t g_data_ready = nullptr;

static void generatorTask(void *param) {
  (void)param;
  for (;;) {
    for (size_t i = 0; i < kArraySize; ++i) {
      g_numbers[i] = random(0, 1000);
      vTaskDelay(pdMS_TO_TICKS(10));
    }
    xSemaphoreGive(g_data_ready);
  }
}

static void sumTask(void *param) {
  (void)param;
  for (;;) {
    if (xSemaphoreTake(g_data_ready, portMAX_DELAY) == pdTRUE) {
      long sum = 0;
      for (size_t i = 0; i < kArraySize; ++i) {
        sum += g_numbers[i];
      }
      Serial.printf("Sum of %u numbers: %ld\n", static_cast<unsigned>(kArraySize), sum);
    }
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  randomSeed(micros());

  g_data_ready = xSemaphoreCreateBinary();
  xTaskCreatePinnedToCore(generatorTask, "gen_task", 4096, nullptr, 1, nullptr, 0);
  xTaskCreatePinnedToCore(sumTask, "sum_task", 4096, nullptr, 1, nullptr, 1);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}
