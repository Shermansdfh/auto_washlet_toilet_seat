#include <Arduino.h>

#ifndef SEAT_OPENER_H
#define SEAT_OPENER_H

class SeatOpener {
    public:
        SeatOpener();
        void init();
        void UpperMotorWriting(double v);
        void LowerMotorWriting(double v);
        void FirstLayerOpener();
        void SecondLayerOpener();
        void FirstLayerCloser();
        void SecondLayerCloser();
};

extern SeatOpener seat_opener;

#endif // SEAT_OPENER_H