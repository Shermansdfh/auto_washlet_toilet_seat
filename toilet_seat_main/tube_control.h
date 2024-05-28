#include <Arduino.h>
#include <Servo.h>

#ifndef TUBE_CONTROL_H
#define TUBE_CONTROL_H

class TubeControl {
    public:
        TubeControl();
        void init();
        void tubeForward(int ang);
        void tubeRotate(int ang);
};

extern TubeControl tube_controller;

#endif // TUBE_CONTROL_H