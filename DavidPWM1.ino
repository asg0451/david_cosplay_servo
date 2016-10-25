
#include <Servo.h>

enum ServoState {
  opened,
  closed,
  somewhere
};

enum State {
  travelling,
  chilling
};

static int CLOSED_POS = 180;
static int OPENED_POS = 0;

Servo left;
Servo right;

static int buttonRight = 12;

State rstate;
State lstate;

ServoState rightServoPrevState;

ServoState getServoState(Servo s) {
  int val = s.read();
  if(val <= 180 && val >= 170) { return closed; };
  if(val <= 10 && val >= 0) { return opened; }
  return somewhere;
}

void setup() {
  left.attach(9);
  right.attach(10);
  pinMode(buttonRight, INPUT);
  pinMode(13, OUTPUT);
  rstate = chilling;
  rightServoPrevState = opened;
  lstate = chilling;
  right.write(CLOSED_POS);
}

void rightLoop() {
  if(rstate == travelling) { digitalWrite(13, HIGH); }
  else { digitalWrite(13, LOW); }
  
  if(rstate == travelling) {
    if(getServoState(right) == closed && rightServoPrevState == opened) { 
      right.write(OPENED_POS);
      rightServoPrevState = closed; 
      rstate = chilling;
    } 
    else if(getServoState(right) == opened && rightServoPrevState == closed) { 
      right.write(CLOSED_POS); 
      rightServoPrevState = opened;
      rstate = chilling;
    }
//    else {
//      rstate = chilling; 
//    }
  }
  else {
    // pushed for first time
    if(digitalRead(buttonRight) == HIGH) {
      rstate = travelling;
    }
  }
}


void loop() {
  rightLoop();  
  delay(200);
}
