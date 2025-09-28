#include "flowmeter.h"
#include "init.h"
#include "starting.h"
#include "checks.h"
#include "sensor.h"
#include "config.h"
#include <ModbusMaster.h>

// Initialize two flowmeter instances
Flowmeter flowmeter0;
Flowmeter flowmeter1;

// Buat objek ModbusMaster
ModbusMaster node;

// =================================================================
// == TASK & CORE DEFINITIONS                                     ==
// =================================================================
TaskHandle_t DisplayTask;

// =================================================================
// == TIMING & STATE VARIABLES                                    ==
// =================================================================
unsigned long previousSensorMillis = 0;
const long sensorInterval = 250; // Interval pembacaan sensor (ms)
static bool readSensor0Next = true; // Flag untuk pembacaan sensor bergantian

// =================================================================
// == DISPLAY UPDATE FUNCTIONS (RUN ON CORE 0)                    ==
// =================================================================

void updateDisplay0(){
  if (flowmeter0.state == 1) {
    // Update primary value display
    char buffer[10];
    dtostrf(flowmeter0.primaryValue, 4, 2, buffer);
    sendNextionCommand("pv0.txt=\"" + String(buffer) + "\"");

    // Update gauge j0
    int gaugeValue = (flowmeter0.currentMilliampere - 4.0) * 6.25;
    if (gaugeValue < 0) {
      gaugeValue = 0;
    } // Clamp gauge value to be non-negative
    sendNextionCommand("j0.val=" + String(gaugeValue));
  }
}

void updateDisplay1(){
  if (flowmeter1.state == 1) {
    // Update primary value display for flowmeter1
    char buffer[10];
    dtostrf(flowmeter1.primaryValue, 4, 2, buffer);
    sendNextionCommand("pv1.txt=\"" + String(buffer) + "\"");

    // Update gauge j1
    int gaugeValue = (flowmeter1.currentMilliampere - 4.0) * 6.25;
    if (gaugeValue < 0) {
      gaugeValue = 0;
    } // Clamp gauge value to be non-negative
    sendNextionCommand("j1.val=" + String(gaugeValue));
  }
}

// Task untuk Core 0: Hanya mengurus update display
void DisplayTaskCode(void * pvParameters) {
  Serial.print("Display task running on core ");
  Serial.println(xPortGetCoreID());

  for (;;) {
    updateDisplay0();
    delay(10);
    updateDisplay1();
    vTaskDelay(500 / portTICK_PERIOD_MS); // Update display setiap 250ms
  }
}

// =================================================================
// == SENSOR & LOGIC FUNCTIONS (RUN ON CORE 1)                    ==
// =================================================================

void updateSensorValues() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousSensorMillis >= sensorInterval) {
    previousSensorMillis = currentMillis;

    // Baca sensor secara bergantian
    if (readSensor0Next) {
      checkValue(&flowmeter0);
    } else {
      checkValue(&flowmeter1);
    }
    readSensor0Next = !readSensor0Next; // Ganti sensor untuk pembacaan berikutnya

    // Cetak nilai yang telah diupdate untuk debug
    Serial.print("Sensor 0 (mA): ");
    Serial.println(flowmeter0.currentMilliampere);
    Serial.print("Sensor 1 (mA): ");
    Serial.println(flowmeter1.currentMilliampere);
  }
}

// =================================================================
// == SETUP & LOOP (MAIN CORE - CORE 1)                           ==
// =================================================================

void setup() {
  initial();
  Serial.begin(MONITOR_BAUD_RATE);
  Serial1.begin(HMI_BAUD_RATE, SERIAL_8N1, 16, 17);
  Serial2.begin(MODBUS_BAUD_RATE, SERIAL_8N1, 25, 26);
  node.begin(MODBUS_SLAVE_ID, Serial2);

  // Buat task untuk display di Core 0
  xTaskCreatePinnedToCore(
      DisplayTaskCode,   /* Function to implement the task */
      "DisplayTask",     /* Name of the task */
      10000,             /* Stack size in words */
      NULL,              /* Task input parameter */
      1,                 /* Priority of the task */
      &DisplayTask,      /* Task handle. */
      0);                /* Core where the task should run */
}

void loop() {
  checkSerial(); 
  updateSensorValues(); 
}
