#include "seat_opener.h"
#include <Arduino.h>

const int UpperMotorI1 = 2;     
const int UpperMotorI2 = 3; 
const int UpperMotorPWM = 11;
const int LowerMotorI1 = 4;     
const int LowerMotorI2 = 5; 
const int LowerMotorPWM = 12;

SeatOpener::SeatOpener() {}

void SeatOpener::init() {
    pinMode(UpperMotorI1, OUTPUT);
    pinMode(UpperMotorI2, OUTPUT);
    pinMode(UpperMotorPWM, OUTPUT);
    pinMode(LowerMotorI1, OUTPUT);
    pinMode(LowerMotorI2, OUTPUT);
    pinMode(LowerMotorPWM, OUTPUT);
}

void SeatOpener::UpperMotorWriting(double v) {
    if (v >= 0) { 
        analogWrite(UpperMotorPWM, v); 
        digitalWrite(UpperMotorI1, LOW);
        digitalWrite(UpperMotorI2, HIGH);
    } else { 
        analogWrite(UpperMotorPWM, -v); 
        digitalWrite(UpperMotorI1, HIGH);
        digitalWrite(UpperMotorI2, LOW);
    }
}

void SeatOpener::LowerMotorWriting(double v) {
    if (v >= 0) { 
        analogWrite(LowerMotorPWM, v); 
        digitalWrite(LowerMotorI1, LOW);
        digitalWrite(LowerMotorI2, HIGH);
    } else {
        analogWrite(LowerMotorPWM, -v); 
        digitalWrite(LowerMotorI1, HIGH);
        digitalWrite(LowerMotorI2, LOW);
    }
}

void SeatOpener::FirstLayerOpener() {
    UpperMotorWriting(200);
}
void SeatOpener::SecondLayerOpener() {
    LowerMotorWriting(200);
}

void SeatOpener::FirstLayerCloser() {
    UpperMotorWriting(-200);
}

void SeatOpener::SecondLayerCloser() {
    LowerMotorWriting(-200);
}

SeatOpener seat_opener = SeatOpener();