#include "tube_control.h"
#include <Arduino.h>
#include <Servo.h>

const int servo_angular_pin = 1;
const int servo_linear_pin = 2;
Servo servo_angular, servo_linear;

TubeControl::TubeControl() {}

void TubeControl::init() {
    servo_angular.attach(servo_angular_pin);
    servo_linear.attach(servo_linear_pin);
}

void TubeControl::TubeForward(int ang) {
    servo_linear.write(ang);
}

void TubeControl::TubeRotate(int ang) {
	servo_angular.write(ang);
}

TubeControl tube_controller = TubeControl();