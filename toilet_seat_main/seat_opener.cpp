#include "seat_opener.h"
#include <Arduino.h>

#define DEBUG

SeatOpener::SeatOpener() {}

void SeatOpener::init() {
#ifdef DEBUG
    Serial.println("SeatOpener: Seat opener initialized.");
#endif

#ifndef DEBUG
    pinMode(UpperMotorI1, OUTPUT);
    pinMode(UpperMotorI2, OUTPUT);
    pinMode(UpperMotorPWM, OUTPUT);
    pinMode(LowerMotorI1, OUTPUT);
    pinMode(LowerMotorI2, OUTPUT);
    pinMode(LowerMotorPWM, OUTPUT);
#endif

    current_state = ALL_CLOSED;
}

void SeatOpener::upperMotorWriting(double v) {
#ifdef DEBUG
    Serial.print("upperMotorWriting: ");
    Serial.println(v);
#endif

#ifndef DEBUG
    if (v >= 0) {
        analogWrite(UpperMotorPWM, v);
        digitalWrite(UpperMotorI1, LOW);
        digitalWrite(UpperMotorI2, HIGH);
    } else {
        analogWrite(UpperMotorPWM, -v);
        digitalWrite(UpperMotorI1, HIGH);
        digitalWrite(UpperMotorI2, LOW);
    }
#endif
}

void SeatOpener::lowerMotorWriting(double v) {
#ifdef DEBUG
    Serial.print("lowerMotorWriting: ");
    Serial.println(v);
#endif

#ifndef DEBUG
    if (v >= 0) {
        analogWrite(LowerMotorPWM, v);
        digitalWrite(LowerMotorI1, LOW);
        digitalWrite(LowerMotorI2, HIGH);
    } else {
        analogWrite(LowerMotorPWM, -v);
        digitalWrite(LowerMotorI1, HIGH);
        digitalWrite(LowerMotorI2, LOW);
    }
#endif
}

void SeatOpener::openFirstLayer() {
#ifdef DEBUG
    Serial.println("SeatOpener: openFirstLayer called.");
#endif
    if (current_state == SeatState::ALL_CLOSED) { 
        upperMotorWriting(200);
        delay(FirstLayerOpenTime);
        current_state = FIRST_LAYER_OPENED;
    } else {
        // TODO: need to handle wrong state called
    }
}
void SeatOpener::openSecondLayer() {
#ifdef DEBUG
    Serial.println("SeatOpener: openSecondLayer called.");
#endif
    if (current_state == SeatState::FIRST_LAYER_OPENED) { 
        lowerMotorWriting(200);
        delay(SecondLayerOpenTime);
        current_state = SECOND_LAYER_OPENED;
    } else {
        // TODO: need to handle wrong state called
    }
}

void SeatOpener::closeFirstLayer() {
#ifdef DEBUG
    Serial.println("SeatOpener: closeFirstLayer called.");
#endif
    if (current_state == SeatState::FIRST_LAYER_OPENED) { 
        upperMotorWriting(-200);
        delay(FirstLayerCloseTime);
        current_state = ALL_CLOSED;
    } else {
        // TODO: need to handle wrong state called
    }
}

void SeatOpener::closeSecondLayer() {
#ifdef DEBUG
    Serial.println("SeatOpener: closeSecondLayer called.");
#endif
    if (current_state == SeatState::SECOND_LAYER_OPENED) { 
        lowerMotorWriting(-200);
        delay(SecondLayerOpenTime);
        current_state = FIRST_LAYER_OPENED;
    } else {
        // TODO: need to handle wrong state called
    }
}

void SeatOpener::openAll() {
#ifdef DEBUG
    Serial.println("SeatOpener: openAll called.");
#endif
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
#ifdef DEBUG
    Serial.println("SeatOpener: closeAll called.");
#endif
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