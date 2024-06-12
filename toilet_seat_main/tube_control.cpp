#include "tube_control.h"
#include <Arduino.h>
#include <Servo.h>

// #define DEBUG

const int servo_angular_pin = 9;
const int servo_linear_pin = 10;
Servo servo_angular, servo_linear;

TubeControl::TubeControl() {}

void TubeControl::init() {
    Serial.println("TubeControl: Tube controller initialized");
#ifndef DEBUG
    servo_angular.attach(servo_angular_pin);
    servo_linear.attach(servo_linear_pin);
#endif
}

void TubeControl::tubeForward(int ang) {
    Serial.println("TubeControl: Servo for forward movement activated.");
#ifndef DEBUG
    servo_linear.write(ang);
#endif
}

void TubeControl::tubeRotate(int ang) {
    Serial.println("TubeControl: Servo for rotation movement activated.");
#ifndef DEBUG
	servo_angular.write(ang);
#endif
}

TubeControl tube_controller = TubeControl();