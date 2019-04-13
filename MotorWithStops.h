/*
Tracks motor and limit switches for movement between end points
*/
#ifndef MotorWithStops_h
#define MotorWithStops_h


#include "Arduino.h"
#include "LimitSwitch.h"

class MotorWithStops {
  public:
    MotorWithStops(int _dirPin, int _pwmPin, bool _inverted = false, int _closeStop = -1, int _openStop = -1, bool _closeStopNormClose = false, bool _openStopNormClose = false);
    void open();
    void close();
    void stop();
    void suspend(bool suspend);
    void check();
    bool isRunning();
    bool isForward();
    bool isOpen();
    bool isClosed();
  private:
    LimitSwitch closeStop, openStop, *currentStop;
    int dirPin, pwmPin;
    bool inverted, suspended, closeStopNormClose, openStopNormClose;
    void driveMotorToStop(LimitSwitch *selectedStop);
    bool checkOpenStop();
    bool checkCloseStop();
    void accelerate(int stepDelay = 3);
};

#endif
