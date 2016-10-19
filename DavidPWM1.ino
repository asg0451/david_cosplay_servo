
#include <Servo.h>

enum ServoState {
  opened,
  closed
};

static int CLOSED_POS = 180;
static int OPENED_POS = 0;

Servo left;
Servo right;

ServoState leftState;
ServoState rightState;

ServoState getState(Servo s) {
  int val = s.read();
  if(val <= 180 && val >= 170) { return closed; };
  if(val <= 10 && val >= 0) { return opened; }
}

void setup() {
  left.attach(9);
  right.attach(10);
}

void loop() {
  leftState = getState(left);
  rightState = getState(right);

  // left transition table
//  switch(leftState) {
//    case opened: left.write(CLOSED_POS); break;
//    case closed: left.write(OPENED_POS); break;
//  }

  // right transition table
  switch(rightState) {
    case opened: right.write(CLOSED_POS); break;
    case closed: right.write(OPENED_POS); break;
  }
  
  delay(3000);
}
