
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
static int OPENED_POS = 100;

Servo left;
Servo right;

static int buttonRight = 12;
static int buttonLeft = 11;

static int rightLED = 7;
static int leftLED = 6;

State rstate;
State lstate;

ServoState rightServoPrevState;
ServoState leftServoPrevState;

ServoState getServoState(Servo s) {
  int val = s.read();
  if(val <= 180 && val >= 170) { return closed; };
  if(val <= OPENED_POS + 10 && val >= OPENED_POS) { return opened; }
  return somewhere;
}

void setup() {
  left.attach(9);
  right.attach(10);
  pinMode(buttonRight, INPUT);  
  pinMode(buttonLeft, INPUT);
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  rstate = chilling;
  lstate = chilling;
  rightServoPrevState = opened;
  leftServoPrevState = opened;
  right.write(CLOSED_POS);
  left.write(CLOSED_POS);


   pinMode(6, OUTPUT);
}

void rightLoop() {
  if(rstate == travelling) { digitalWrite(rightLED, HIGH); }
  else { digitalWrite(rightLED, LOW); }
  
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
  }
  else {
    // pushed for first time
    if(digitalRead(buttonRight) == HIGH) {
      rstate = travelling;
    }
  }
}


void leftLoop() {
  if(lstate == travelling) { digitalWrite(leftLED, HIGH); }
  else { digitalWrite(leftLED, LOW); }
  
  if(lstate == travelling) {
    if(getServoState(left) == closed && leftServoPrevState == opened) { 
      left.write(OPENED_POS);
      leftServoPrevState = closed; 
      lstate = chilling;
    } 
    else if(getServoState(left) == opened && leftServoPrevState == closed) { 
      left.write(CLOSED_POS); 
      leftServoPrevState = opened;
      lstate = chilling;
    }
  }
  else {
    // pushed for first time
    if(digitalRead(buttonLeft) == HIGH) {
      lstate = travelling;
    }
  }
}
void loop() {
  rightLoop();  
  leftLoop();
  delay(300);
}
