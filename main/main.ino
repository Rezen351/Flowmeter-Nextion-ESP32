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

// Untuk Arduino Mega, kita gunakan objek Serial2 yang sudah ada.
// Serial1: Pins 19 (RX), 18 (TX)
// Serial2: Pins 17 (RX), 16 (TX)
// Serial3: Pins 15 (RX), 14 (TX)

// Untuk ESP-32
// HardwareSerial ModbusSerial(2);
unsigned long previousMillis = 0;
const long interval = 1000; // Interval diperlambat jadi 1 detik untuk pembacaan debug


void setup() {
  // put your setup code here, to run once:
  initial();
  
  // Inisialisasi Serial untuk Monitor/Debug
  Serial.begin(MONITOR_BAUD_RATE);

  // Inisialisasi Serial1 untuk HMI Nextion Display
  Serial1.begin(HMI_BAUD_RATE);

  // Inisialisasi Serial2 untuk Modbus Master
  Serial2.begin(MODBUS_BAUD_RATE);

  //ModbusSerial.begin(MODBUS_BAUD_RATE, SERIAL_8N1, MODBUS_RX_PIN,MODBUS_TX_PIN);
  
  // Hubungkan objek node ke port serial Modbus
  node.begin(MODBUS_SLAVE_ID, Serial2);
}

void loop() {
  // put your main code here, to run repeatedly:
  checkSerial();
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Panggil fungsi update flowmeter seperti biasa
    // flowmeter0Update(); 
    // flowmeter1Update();

    // Panggil fungsi debug baru
    // debugModbusRegisters();
    Serial.println(readModbusSensor());
  
  }
}

void flowmeter0Update(){
  if (flowmeter0.state == 1) {
    checkValue(&flowmeter0);
    // Update primary value display
    char buffer[10]; // Increased buffer size for float
    dtostrf(flowmeter0.primaryValue, 4, 2, buffer); // 4 total width, 2 decimal places
    Serial1.print("pv0.txt=\"");
    Serial1.print(buffer);
    Serial1.print("\"");
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);

    // Update gauge j0
    int gaugeValue = (flowmeter0.currentMilliampere - 4.0) * 6.25;
    Serial1.print("j0.val=");
    Serial1.print(gaugeValue);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
  }
}

void flowmeter1Update(){
  if (flowmeter1.state == 1) {
    checkValue(&flowmeter1);

    // Update primary value display for flowmeter1
    char buffer[10]; // Increased buffer size for float
    dtostrf(flowmeter1.primaryValue, 4, 2, buffer); // 4 total width, 2 decimal places
    Serial1.print("pv1.txt=\""); // Assuming pv1.txt for flowmeter1
    Serial1.print(buffer);
    Serial1.print("\"");
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);

    // Update gauge j1
    int gaugeValue = (flowmeter1.currentMilliampere - 4.0) * 6.25;
    Serial1.print("j1.val=");
    Serial1.print(gaugeValue);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
  }
}