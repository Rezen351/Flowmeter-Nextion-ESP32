#include "sensor.h"
#include <Arduino.h>
#include "config.h"
#include <ModbusMaster.h>

// Gunakan objek 'node' yang dideklarasikan secara global di main.ino
extern ModbusMaster node;

// Fungsi ini dikembalikan ke versi simulasi asli
float readMilliampereSensor0() {
  static float currentValue = 4.0;
  currentValue += 0.1;
  if (currentValue > 20.0) {
    currentValue = 4.0;
  }
  return currentValue;
}


// Biarkan sensor1 sebagai simulasi untuk saat ini
float readMilliampereSensor1() {
  static float currentValue = 4.0;
  currentValue += 0.2; // Different increment for sensor 1
  if (currentValue > 20.0) {
    currentValue = 4.0;
  }
  return currentValue;
}

// Fungsi baru untuk debug register Modbus
void debugModbusRegisters() {
  uint8_t result;
  uint8_t registersToRead = 5;

  Serial.println("--- Membaca 5 Register Modbus ---");
  result = node.readInputRegisters(0, registersToRead); // Baca 5 register mulai dari alamat 0

  if (result == node.ku8MBSuccess) {
    for (uint8_t i = 0; i < registersToRead; i++) {
      Serial.print("Register[");
      Serial.print(i);
      Serial.print("]: ");
      Serial.println(node.getResponseBuffer(i));
    }
  } else {
    Serial.println("Gagal membaca Modbus!");
  }
}

// Fungsi baru khusus untuk pembacaan sensor Modbus
float readModbusSensor() {
  static float lastGoodValue = 0.0; // Simpan nilai terakhir yang valid
  uint8_t result;
  uint8_t registersToRead = 3;
  result = node.readInputRegisters(0, registersToRead);
  if (result == node.ku8MBSuccess) {
    for (uint8_t i = 0; i < registersToRead; i++) {
      Serial.print("Register[");
      Serial.print(i);
      Serial.print("]: ");
      Serial.println(node.getResponseBuffer(i));
    }
    float floatValue=node.getResponseBuffer(1);
    return floatValue;
  } else {
    // Jika pembacaan gagal, kembalikan nilai terakhir yang valid
    Serial.println("Gagal membaca Modbus!");
    return lastGoodValue;
  }
}