#include "water_pump.h"
#include <Arduino.h>

const int WaterPumpMotorI1 = 6;     
const int WaterPumpMotorI2 = 7; 
const int WaterPumpMotorPWM = 13;

WaterPump::WaterPump() {}

void WaterPump::init() {
    pinMode(WaterPumpMotorI1, OUTPUT);
    pinMode(WaterPumpMotorI2, OUTPUT);
    pinMode(WaterPumpMotorPWM, OUTPUT);
}

void WaterPump::waterPumpOn() {
    analogWrite(WaterPumpMotorPWM, 255); 
    digitalWrite(WaterPumpMotorI1, LOW);
    digitalWrite(WaterPumpMotorI2, HIGH);
}

void WaterPump::waterPumpOff() {
    analogWrite(WaterPumpMotorPWM, 0); 
    digitalWrite(WaterPumpMotorI1, LOW);
    digitalWrite(WaterPumpMotorI2, HIGH);
}

WaterPump water_pump = WaterPump();