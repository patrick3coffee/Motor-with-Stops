#include "MotorWithStops.h"

#ifndef FORWARD
#define FORWARD  0
#define REVERSE 1
#endif

MotorWithStops::MotorWithStops(int _dirPin, int _pwmPin,  bool _inverted = false, int _closeStopPin, int _openStopPin, bool _closeStopNormClose = false, bool _openStopNormClose = false) {
    inverted = _inverted;
    suspended = false;

    dirPin = _dirPin;
    pwmPin = _pwmPin;

    pinMode(dirPin, OUTPUT);
    pinMode(pwmPin, OUTPUT);

    digitalWrite(dirPin, LOW);
    digitalWrite(pwmPin, LOW);
    
    closeStop.setPin(_closeStopPin);
    closeStop.setNormalState(_closeStopNormClose);
    
    openStop.setPin(_openStopPin);
    openStop.setNormalState(_openStopNormClose);
}

void MotorWithStops::open() {
    if (inverted) {
        digitalWrite(dirPin, REVERSE);
    }
    else {
        digitalWrite(dirPin, FORWARD);
    }
    driveMotorToStop(&openStop);
}

void MotorWithStops::close() {
    if (inverted) {
        digitalWrite(dirPin, FORWARD);
    }
    else {
        digitalWrite(dirPin, REVERSE);
    }
    driveMotorToStop(&closeStop);
}


void MotorWithStops::stop() {
    digitalWrite(pwmPin, LOW);
}


void MotorWithStops::suspend(bool suspend) {
    if (suspend) {
        stop();
        suspended = true;
    }
    else {
        suspended = false;
    }
}


void MotorWithStops::driveMotorToStop(LimitSwitch *selectedStop) {
  if (suspended || selectedStop->limitReached() ) {
    stop();
  }
  else {
    for (int i = 0; i< 255; i++){
      analogWrite(pwmPin, i);
      delay(3);
    }
    digitalWrite(pwmPin, HIGH);

    bool done = false;
    while (!done) {
      if (suspended || selectedStop->limitReached() ) {
        done = true;
      }
      delay(200);
    }
    stop();
  }
}


bool MotorWithStops::isRunning() {
  if ( digitalRead(pwmPin) == HIGH) {
    return true;
  }
  else {
    return false;
  }
}

bool MotorWithStops::isForward() {

  if ( digitalRead(dirPin) == HIGH) {
    return true;
  }
  else {
    return false;
  }
}

bool MotorWithStops::isOpen() {
    return openStop.limitReached();
}

bool MotorWithStops::isClosed() {
    return closeStop.limitReached();
}

