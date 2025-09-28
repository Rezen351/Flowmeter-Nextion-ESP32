#include "flowmeter.h"
#include "sensor.h"
#include "init.h"

// Data kalibrasi dari tabel eksperimen
const int NUM_POINTS = 5;
// Sinyal input dalam miliampere (mA)
const float ma_points[NUM_POINTS] = {6.05, 6.84, 9.87, 12.07, 19.28};
// Nilai output yang sesuai dalam Pascal (Pa)
const float pa_points[NUM_POINTS] = {2316.47, 3173.75, 3202.00, 8936.90, 17218.70};

float convertMaToPa(float milliampere) {
  // Cek jika nilai di luar rentang bawah data
  if (milliampere <= ma_points[0]) {
    // Ekstrapolasi menggunakan dua titik pertama
    return pa_points[0] + (milliampere - ma_points[0]) * (pa_points[1] - pa_points[0]) / (ma_points[1] - ma_points[0]);
  }

  // Cek jika nilai di luar rentang atas data
  if (milliampere >= ma_points[NUM_POINTS - 1]) {
    // Ekstrapolasi menggunakan dua titik terakhir
    return pa_points[NUM_POINTS - 2] + (milliampere - ma_points[NUM_POINTS - 2]) * (pa_points[NUM_POINTS - 1] - pa_points[NUM_POINTS - 2]) / (ma_points[NUM_POINTS - 1] - ma_points[NUM_POINTS - 2]);
  }

  // Cari segmen yang tepat untuk interpolasi
  for (int i = 0; i < NUM_POINTS - 1; i++) {
    if (milliampere >= ma_points[i] && milliampere <= ma_points[i + 1]) {
      // Lakukan interpolasi linier di dalam segmen ini
      return pa_points[i] + (milliampere - ma_points[i]) * (pa_points[i + 1] - pa_points[i]) / (ma_points[i + 1] - ma_points[i]);
    }
  }
  
  // Seharusnya tidak pernah sampai di sini, tapi sebagai fallback
  return 0.0; 
}


void checkValue(Flowmeter* fm) {
  float milliampere;
  if (fm == &flowmeter0) {
    milliampere = readMilliampereSensor0();
  } else if (fm == &flowmeter1) {
    milliampere = readMilliampereSensor1();
  }
  
  fm->currentMilliampere = milliampere; // Store the milliampere value

  // 1. Konversi nilai mA ke Pascal (Pa) menggunakan data kalibrasi
  float pressurePa = convertMaToPa(milliampere);

  if (fm->unit == "kPa") {
    // 2. Konversi dari Pa ke kPa dan simpan
    // Kita bagi 1000 untuk mendapatkan kPa (1 Pa = 0.001 kPa)
    fm->primaryValue = pressurePa / 1000.0;
      
  } else if (fm->unit == "mA") {
    // Tampilkan nilai mA langsung
    fm->primaryValue = milliampere;
      
  } else if (fm->unit == "mmHg") {
    // 2. Konversi dari Pa ke mmHg dan simpan
    float pressureMmHg = pressurePa * 0.00750062;
    fm->primaryValue = pressureMmHg;
  }
}

void checkSerial() {
  if (Serial1.available() > 0) {
    String command = Serial1.readStringUntil('\n'); // Use readStringUntil for better behavior
    command.trim();

    if (command == "run0:0") {
      flowmeter0.state = 0;
      Serial.println("stop"); // Keep for debugging

      // Send the last primaryValue to the display
      char buffer[10]; // Increased buffer size for float
      dtostrf(flowmeter0.primaryValue, 4, 2, buffer); // 4 total width, 2 decimal places
      sendNextionCommand("pv0.txt=\"" + String(buffer) + "\"");

    } else if (command == "run0:1") {
      flowmeter0.state = 1;
      Serial.println("run"); // Keep for debugging
    }
    else if (command == "unit0:kPa"){
      flowmeter0.unit = "kPa";
      Serial.println(flowmeter0.unit);
    }
    else if (command == "unit0:mA"){
      flowmeter0.unit = "mA";
      Serial.println(flowmeter0.unit);
    }
    else if (command == "unit0:mmHg"){
      flowmeter0.unit = "mmHg";
      Serial.println(flowmeter0.unit);
    }
    // New commands for flowmeter1
    else if (command == "run1:0") {
      flowmeter1.state = 0;
      Serial.println("stop1"); // Debugging for flowmeter1
      // Send the last primaryValue to the display for flowmeter1
      char buffer[10]; // Increased buffer size for float
      dtostrf(flowmeter1.primaryValue, 4, 2, buffer); // 4 total width, 2 decimal places
      sendNextionCommand("pv1.txt=\"" + String(buffer) + "\"");
    } else if (command == "run1:1") {
      flowmeter1.state = 1;
      Serial.println("run1"); // Debugging for flowmeter1
    }
    else if (command == "unit1:kPa"){
      flowmeter1.unit = "kPa";
      Serial.println(flowmeter1.unit);
    }
    else if (command == "unit1:mA"){
      flowmeter1.unit = "mA";
      Serial.println(flowmeter1.unit);
    }
    else if (command == "unit1:mmHg"){
      flowmeter1.unit = "mmHg";
      Serial.println(flowmeter1.unit);
    }
  }
}