#include "flowmeter.h"

void starting() {
  // starting check: ensure all systems are normal

  // Initialize primmaryButton for flowmeter0 for checking
  // Nextion: pb1, pb2, pb3, pb4
  for (int i = 0; i < 4; i++) {
    flowmeter0.primmaryButton[i] = 1;
  }

  // Check primmaryButton values and send to Nextion
  for (int i = 0; i < 4; i++) {
    Serial1.print("pb");
    Serial1.print(i + 1);
    Serial1.print(".val=");
    Serial1.print(flowmeter0.primmaryButton[i]);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    delay(500);
  }
  // cycle through function buttons 0-4
  for (int i = 0; i < 5; i++) {
    flowmeter0.functionButton[i] = 1;
  }
  for (int i = 0; i < 5; i++) {
    Serial1.print("fb");
    Serial1.print(i + 1);
    Serial1.print(".val=");
    Serial1.print(flowmeter0.functionButton[i]);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    delay(500);
  }

  // run primaryValue from 0000 - 9999
  // This loop is for demonstration during starting, primaryValue is float now.
  // The range 0-9999 is for integer display, so we will simulate that.
  for (float i = 0.0; i <= 9999.0; i += 100.0) { // Increment by 100 to see changes faster
    flowmeter0.primaryValue = i;
    char buffer[10]; // Increased buffer size for float
    dtostrf(flowmeter0.primaryValue, 4, 0, buffer); // 4 total width, 0 decimal places for integer-like display
    Serial1.print("pv0.txt=\"");
    Serial1.print(buffer);
    Serial1.print("\"");
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    Serial1.write(0xFF);
    delay(10);
  }
  // cycle units from kPa to mmHg and back to kPa
  String units[] = {"kPa", "mA", "mmHg"};
  for (int i = 0; i < 3; i++) {
    flowmeter0.unit = units[i];

    // Hide all unit indicators first
    Serial1.print("vis un1,0");
    Serial1.write(0xFF); Serial1.write(0xFF); Serial1.write(0xFF);
    Serial1.print("vis un2,0");
    Serial1.write(0xFF); Serial1.write(0xFF); Serial1.write(0xFF);
    Serial1.print("vis un3,0");
    Serial1.write(0xFF); Serial1.write(0xFF); Serial1.write(0xFF);
    
    // Show the current unit indicator
    if (units[i] == "kPa") {
      Serial1.print("vis un1,1");
    } else if (units[i] == "mA") {
      Serial1.print("vis un2,1");
    } else if (units[i] == "mmHg") {
      Serial1.print("vis un3,1");
    }
    Serial1.write(0xFF); Serial1.write(0xFF); Serial1.write(0xFF);
    delay(500);
  }

  
  // run density from 0000 - 9999
  // run temp from 000 - 999
  // run totalizer from 0000 - 9999
  // change state from start to stop
  // change dir from 0 to 1 and alternate 0 1 0 1
  // alternate alarm 0 1 0 1
}
