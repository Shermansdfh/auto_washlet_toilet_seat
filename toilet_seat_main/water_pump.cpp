#include "water_pump.h"
#include <Arduino.h>

//#define DEBUG

WaterPump::WaterPump() {}

void WaterPump::init() {
    Serial.println("WaterPump: waterPump initialized");

#ifndef DEBUG
    pinMode(WaterPumpMotorI1, OUTPUT);
    pinMode(WaterPumpMotorI2, OUTPUT);
    pinMode(WaterPumpMotorPWM, OUTPUT);
#endif
}

void WaterPump::waterPumpOn() {
    Serial.println("WaterPump: waterPumpOn");

#ifndef DEBUG
    analogWrite(WaterPumpMotorPWM, 200); 
    digitalWrite(WaterPumpMotorI1, LOW);
    digitalWrite(WaterPumpMotorI2, HIGH);
#endif
}

void WaterPump::waterPumpOff() {
    Serial.println("WaterPump: waterPumpOff");

#ifndef DEBUG
    analogWrite(WaterPumpMotorPWM, 0); 
    digitalWrite(WaterPumpMotorI1, HIGH);
    digitalWrite(WaterPumpMotorI2, LOW);
#endif
}

WaterPump water_pump = WaterPump();