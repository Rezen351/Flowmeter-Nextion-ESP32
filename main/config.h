#ifndef CONFIG_H
#define CONFIG_H

// =================================================================
// ==            KONFIGURASI SERIAL UTAMA                       ==
// =================================================================

// Konfigurasi untuk Serial Monitor (Koneksi USB PC)
#define MONITOR_BAUD_RATE 115200

// Konfigurasi untuk Serial1 (Nextion HMI Display)
#define HMI_BAUD_RATE 115200

// Baud rate untuk komunikasi Modbus
#define MODBUS_BAUD_RATE 9600

// Pin untuk Serial (UART) Modbus
// Untuk Arduino Mega, pin ini sudah ditentukan oleh port HardwareSerial yang digunakan (misal: Serial2 menggunakan pin 16 & 17).
// #define MODBUS_RX_PIN 16
// #define MODBUS_TX_PIN 17

// Pin untuk kontrol DE/RE (Driver Enable/Receive Enable) pada driver RS485.
//#define MODBUS_DE_RE_PIN 4 // Contoh: Pin GPIO4


// ID perangkat/slave Modbus yang akan dibaca
#define MODBUS_SLAVE_ID 1

// Alamat register untuk sensor 0.
// Alamat 1 di dokumentasi seringkali berarti 0 di implementasi.
#define SENSOR0_MODBUS_ADDRESS 1
// #define SENSOR1_MODBUS_ADDRESS 1

#endif // CONFIG_H
