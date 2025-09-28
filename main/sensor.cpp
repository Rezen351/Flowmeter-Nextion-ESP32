#include "sensor.h"
#include <Arduino.h>
#include "config.h"
#include <ModbusMaster.h>

// Gunakan objek 'node' yang dideklarasikan secara global di main.ino
extern ModbusMaster node;

float readMilliampereSensor0() {
  static float lastGoodValue = 0.0;
  uint8_t result;

  // Baca 1 holding register di alamat 2
  result = node.readHoldingRegisters(2, 1);

  if (result == node.ku8MBSuccess) {
    uint16_t rawValue = node.getResponseBuffer(0);
    Serial.print("Raw value from Modbus Sensor 0: "); // DEBUG
    Serial.println(rawValue); // DEBUG
    float milliampere = rawValue / 10.0; // Asumsi nilai dikirim sebagai integer (e.g., 401 untuk 4.01mA)
    lastGoodValue = milliampere;
    return milliampere;
  } else {
    Serial.println("Gagal membaca Modbus untuk Sensor 0 (Register 2)!");
    return lastGoodValue;
  }
}

float readMilliampereSensor1() {
  static float lastGoodValue = 0.0;
  uint8_t result;

  // Baca 1 holding register di alamat 3
  result = node.readHoldingRegisters(3, 1);

  if (result == node.ku8MBSuccess) {
    uint16_t rawValue = node.getResponseBuffer(0);
    float milliampere = rawValue / 10.0; // Asumsi nilai dikirim sebagai integer (e.g., 401 untuk 4.01mA)
    lastGoodValue = milliampere;
    return milliampere;
  } else {
    Serial.println("Gagal membaca Modbus untuk Sensor 1 (Register 3)!");
    return lastGoodValue;
  }
}

// Fungsi baru untuk debug register Modbus
void debugModbusRegisters() {
  uint8_t result;
  uint8_t registersToRead = 5;

  Serial.println("--- Membaca 5 Register Modbus ---");
  result = node.readHoldingRegisters(0, registersToRead); // Baca 5 register mulai dari alamat 0

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
