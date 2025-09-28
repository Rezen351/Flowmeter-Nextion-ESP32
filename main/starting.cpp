#include "flowmeter.h"
#include "init.h"

void starting() {
  // starting check: ensure all systems are normal

  // Initialize primmaryButton for flowmeter0 for checking
  // Nextion: pb1, pb2, pb3, pb4
  for (int i = 0; i < 4; i++) {
    flowmeter0.primmaryButton[i] = 1;
  }

  // Check primmaryButton values and send to Nextion
  for (int i = 0; i < 4; i++) {
    sendNextionCommand("pb" + String(i + 1) + ".val=" + String(flowmeter0.primmaryButton[i]));
    delay(500);
  }
  // cycle through function buttons 0-4
  for (int i = 0; i < 5; i++) {
    flowmeter0.functionButton[i] = 1;
  }
  for (int i = 0; i < 5; i++) {
    sendNextionCommand("fb" + String(i + 1) + ".val=" + String(flowmeter0.functionButton[i]));
    delay(500);
  }

  // run primaryValue from 0000 - 9999
  // This loop is for demonstration during starting, primaryValue is float now.
  // The range 0-9999 is for integer display, so we will simulate that.
  for (float i = 0.0; i <= 9999.0; i += 100.0) { // Increment by 100 to see changes faster
    flowmeter0.primaryValue = i;
    char buffer[10]; // Increased buffer size for float
    dtostrf(flowmeter0.primaryValue, 4, 0, buffer); // 4 total width, 0 decimal places for integer-like display
    sendNextionCommand("pv0.txt=\"" + String(buffer) + "\"");
    delay(10);
  }
  // cycle units from kPa to mmHg and back to kPa
  String units[] = {"kPa", "mA", "mmHg"};
  for (int i = 0; i < 3; i++) {
    flowmeter0.unit = units[i];

    if (units[i] == "kPa") {
      sendNextionCommand("vis un1,1");
      sendNextionCommand("vis un2,0");
      sendNextionCommand("vis un3,0");
    } else if (units[i] == "mA") {
      sendNextionCommand("vis un1,0");
      sendNextionCommand("vis un2,1");
      sendNextionCommand("vis un3,0");
    } else if (units[i] == "mmHg") {
      sendNextionCommand("vis un1,0");
      sendNextionCommand("vis un2,0");
      sendNextionCommand("vis un3,1");
    }
    delay(500);
  }

  
  // run density from 0000 - 9999
  // run temp from 000 - 999
  // run totalizer from 0000 - 9999
  // change state from start to stop
  // change dir from 0 to 1 and alternate 0 1 0 1
  // alternate alarm 0 1 0 1
}
