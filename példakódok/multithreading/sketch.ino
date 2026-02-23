  #include <freertos/FreeRTOS.h>
  #include <freertos/task.h>
  #include <freertos/semphr.h>

  SemaphoreHandle_t xMutex;
  int sensorData = 0;

  void sensorTask(void *pvParameters) {
    while(1) {
      int rawValue = analogRead(A0);
      
      if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
        sensorData = rawValue;
        xSemaphoreGive(xMutex);
      }
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
  }

  void communicationTask(void *pvParameters) {
    while(1) {
      if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
        Serial.print("Sensor value: ");
        Serial.println(sensorData);
        xSemaphoreGive(xMutex);
      }
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
  }

  void setup() {
    Serial.begin(115200);
    pinMode(A0, INPUT);
    xMutex = xSemaphoreCreateMutex();
    
    xTaskCreatePinnedToCore(sensorTask, "SensorTask", 2048, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(communicationTask, "CommTask", 2048, NULL, 1, NULL, 1);
  }

  void loop() {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }