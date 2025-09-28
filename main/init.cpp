#include "flowmeter.h"
#include "init.h"

void initial() {
  // //primarybutton{1,0,0,0}
  // flowmeter0.primmaryButton[0] = 1;
  // flowmeter0.primmaryButton[1] = 0;
  // flowmeter0.primmaryButton[2] = 0;
  // flowmeter0.primmaryButton[3] = 0;

  // //functionbutton{0,0,0,0,0}
  // for (int i = 0; i < 5; i++) {
  //   flowmeter0.functionButton[i] = 0;
  // }

  flowmeter0.primaryValue = 0.0f; // Use float literal
  flowmeter1.primaryValue = 0.0f; // Use float literal

  //Initialize flowmeter0
  flowmeter0.unit = "kPa";
  flowmeter0.state = 0; 

  // Initialize flowmeter1
  flowmeter1.unit = "kPa";
  flowmeter1.state = 0; 
}

void sendNextionCommand(String command) {
  Serial1.print(command);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
}
