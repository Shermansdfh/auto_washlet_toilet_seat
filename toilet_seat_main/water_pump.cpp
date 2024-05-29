#include "water_pump.h"
#include <Arduino.h>

#define DEBUG

const int WaterPumpMotorI1 = 6;     
const int WaterPumpMotorI2 = 7; 
const int WaterPumpMotorPWM = 13;

WaterPump::WaterPump() {}

void WaterPump::init() {
#ifdef DEBUG
    Serial.println("WaterPump: waterPump initialized");
#endif

#ifndef DEBUG
    pinMode(WaterPumpMotorI1, OUTPUT);
    pinMode(WaterPumpMotorI2, OUTPUT);
    pinMode(WaterPumpMotorPWM, OUTPUT);
#endif
}

void WaterPump::waterPumpOn() {
#ifdef DEBUG
    Serial.println("WaterPump: waterPumpOn");
#endif

#ifndef DEBUG
    analogWrite(WaterPumpMotorPWM, 255); 
    digitalWrite(WaterPumpMotorI1, LOW);
    digitalWrite(WaterPumpMotorI2, HIGH);
#endif
}

void WaterPump::waterPumpOff() {
#ifdef DEBUG
    Serial.println("WaterPump: waterPumpOff");
#endif

#ifndef DEBUG
    analogWrite(WaterPumpMotorPWM, 0); 
    digitalWrite(WaterPumpMotorI1, LOW);
    digitalWrite(WaterPumpMotorI2, HIGH);
#endif
}

WaterPump water_pump = WaterPump();