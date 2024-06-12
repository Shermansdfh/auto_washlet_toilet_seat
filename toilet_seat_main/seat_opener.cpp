#include "seat_opener.h"
#include <Arduino.h>

//#define DEBUG

SeatOpener::SeatOpener() {}

void SeatOpener::init() {
    Serial.println("SeatOpener: Seat opener initialized.");

#ifndef DEBUG
    pinMode(UpperMotorAIN1, OUTPUT);
    pinMode(UpperMotorAIN2, OUTPUT);
    pinMode(UpperMotorPWMA, OUTPUT);
    pinMode(LowerMotorBIN1, OUTPUT);
    pinMode(LowerMotorBIN2, OUTPUT);
    pinMode(LowerMotorPWMB, OUTPUT);
#endif

    current_state = ALL_CLOSED;
}

void SeatOpener::upperMotorWriting(double v) {
    Serial.print("upperMotorWriting: ");
    Serial.println(v);

#ifndef DEBUG
    if (v >= 0) {
        Serial.println("uppermMotorWriting with v>0");
        analogWrite(UpperMotorPWMA, v);
        digitalWrite(UpperMotorAIN1, LOW);
        digitalWrite(UpperMotorAIN2, HIGH);
    } else {
        analogWrite(UpperMotorPWMA, -v);
        digitalWrite(UpperMotorAIN1, HIGH);
        digitalWrite(UpperMotorAIN2, LOW);
    }
#endif
}

void SeatOpener::lowerMotorWriting(double v) {
    Serial.print("lowerMotorWriting: ");
    Serial.println(v);

#ifndef DEBUG
    if (v >= 0) {
        Serial.println("lowerMotorWriting with v>0");
        analogWrite(LowerMotorPWMB, v);
        digitalWrite(LowerMotorBIN1, LOW);
        digitalWrite(LowerMotorBIN2, HIGH);
    } else {
        analogWrite(LowerMotorPWMB, -v);
        digitalWrite(LowerMotorBIN1, HIGH);
        digitalWrite(LowerMotorBIN2, LOW);
    }
#endif
}

void SeatOpener::openFirstLayer() {
    Serial.println("SeatOpener: openFirstLayer called.");
    //if (current_state == SeatState::ALL_CLOSED) { 
    if (true) {
        upperMotorWriting(255);
        delay(FirstLayerOpenTime);
        upperMotorWriting(0);
    //    current_state = FIRST_LAYER_OPENED;
    } else {
        // TODO: need to handle wrong state called
        Serial.print("SeatOpener: Current state ain't ALL_CLOSED.");
        Serial.print("It's");
        Serial.print(current_state);
    }
}
void SeatOpener::openSecondLayer() {
    Serial.println("SeatOpener: openSecondLayer called.");

    //if (current_state == SeatState::FIRST_LAYER_OPENED) { 
    if (true) {
        lowerMotorWriting(255);
        delay(SecondLayerOpenTime);
        lowerMotorWriting(0);
        // current_state = SECOND_LAYER_OPENED;
    } else {
        // TODO: need to handle wrong state called
    }
}

void SeatOpener::closeFirstLayer() {
    Serial.println("SeatOpener: closeFirstLayer called.");
    //if (current_state == SeatState::FIRST_LAYER_OPENED) { 
    if (true) {
        Serial.println("SeatOpener: Closing first layer.");
        upperMotorWriting(-100);
        delay(FirstLayerCloseTime);
        upperMotorWriting(0);
        // current_state = ALL_CLOSED;    } else {
        // TODO: need to handle wrong state called
    }
}

void SeatOpener::closeSecondLayer() {
    Serial.println("SeatOpener: closeSecondLayer called.");
    // if (current_state == SeatState::SECOND_LAYER_OPENED) { 
    if (true) {
        Serial.println("SeatOpener: Closing second layer.");
        lowerMotorWriting(-100);
        delay(SecondLayerCloseTime);
        lowerMotorWriting(0);
        //current_state = FIRST_LAYER_OPENED;
    } else {
        // TODO: need to handle wrong state called
    }
}

void SeatOpener::openAll() {
    Serial.println("SeatOpener: openAll called.");
    bool state_correct = true;
    if (current_state == SeatState::ALL_CLOSED) { 
        openFirstLayer();
        delay(DelayBetweenTwoOpening);
        if (current_state == SeatState::FIRST_LAYER_OPENED) { 
            openSecondLayer();
        } else {
            state_correct = false;
        }
    } else {
        state_correct = false;
    }

    if (!state_correct) {
        // TODO: need to handle wrong state called
    }
}

void SeatOpener::closeAll() {
    Serial.println("SeatOpener: closeAll called.");
    bool state_correct = true;
    if (current_state == SeatState::SECOND_LAYER_OPENED) { 
        closeSecondLayer();
        delay(DelayBetweenTwoClosing);
        if (current_state == SeatState::FIRST_LAYER_OPENED) { 
            closeFirstLayer();
        } else {
            state_correct = false;
        }
    } else {
        state_correct = false;
    }
    
    if (!state_correct) {
        // TODO: need to handle wrong state called
    }
}

SeatOpener seat_opener = SeatOpener();