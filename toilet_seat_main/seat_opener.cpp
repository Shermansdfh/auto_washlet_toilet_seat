#include "seat_opener.h"
#include <Arduino.h>

SeatOpener::SeatOpener() {}

void SeatOpener::init() {
    pinMode(UpperMotorI1, OUTPUT);
    pinMode(UpperMotorI2, OUTPUT);
    pinMode(UpperMotorPWM, OUTPUT);
    pinMode(LowerMotorI1, OUTPUT);
    pinMode(LowerMotorI2, OUTPUT);
    pinMode(LowerMotorPWM, OUTPUT);

    current_state = ALL_CLOSED;
}

void SeatOpener::upperMotorWriting(double v) {
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

void SeatOpener::lowerMotorWriting(double v) {
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

void SeatOpener::openFirstLayer() {
    if (current_state == SeatState::ALL_CLOSED) { 
        UpperMotorWriting(200);
        delay(FirstLayerOpenTime);
        current_state = FIRST_LAYER_OPENED;
    } else {
        // TODO: need to handle wrong state called
    }
}
void SeatOpener::openSecondLayer() {
    if (current_state == SeatState::FIRST_LAYER_OPENED) { 
        LowerMotorWriting(200);
        delay(SecondLayerOpenTime);
        current_state = SECOND_LAYER_OPENED;
    } else {
        // TODO: need to handle wrong state called
    }
}

void SeatOpener::closeFirstLayer() {
    if (current_state == SeatState::FIRST_LAYER_OPENED) { 
        UpperMotorWriting(-200);
        delay(FirstLayerCloseTime);
        current_state = ALL_CLOSED;
    } else {
        // TODO: need to handle wrong state called
    }
}

void SeatOpener::closeSecondLayer() {
    if (current_state == SeatState::SECOND_LAYER_OPENED) { 
        LowerMotorWriting(-200);
        delay(SecondLayerOpenTime);
        current_state = FIRST_LAYER_OPENED;
    } else {
        // TODO: need to handle wrong state called
    }
}

void SeatOpener::openAll() {
    bool state_correct = true;
    if (current_state == SeatState::ALL_CLOSED) { 
        OpenFirstLayer();
        oelay(DelayBetweenTwoOpening);
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