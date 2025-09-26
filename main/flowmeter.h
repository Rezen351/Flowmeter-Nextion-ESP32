#ifndef FLOWMETER_H
#define FLOWMETER_H

#include <Arduino.h>

// Define a structure to hold all variables for a single flowmeter
struct Flowmeter {
  float primaryValue;    // max 4 digits, now float for decimal values
  float currentMilliampere; // Store the current milliampere reading
  String unit;           // "kPa", "mA", "mmHg"
  int state;             // 0: stop, 1: running
  int temp;              // max 3 digits
  int density;           // max 4 digits
  long totalizer;        // max 4 digits, but long for future proofing
  int dir;               // 1: right, 0: left
  int alarm;             // 1: on, 0: off
  int primmaryButton[4];
  int functionButton[5];
};

// Declare two flowmeter instances as extern
extern Flowmeter flowmeter0;
extern Flowmeter flowmeter1;

#endif