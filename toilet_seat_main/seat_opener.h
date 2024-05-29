#include <Arduino.h>

#ifndef SEAT_OPENER_H
#define SEAT_OPENER_H

class SeatOpener {
    public:
        SeatOpener();
        void init();
        void openFirstLayer();
        void openSecondLayer();
        void closeFirstLayer();
        void closeSecondLayer();
        void openAll();
        void closeAll();
    private:
        enum SeatState {
            ALL_CLOSED,
            FIRST_LAYER_OPENED,
            SECOND_LAYER_OPENED
        };

        SeatState current_state;

        // TODO: test motor pulling time
        const int FirstLayerOpenTime = 200;
        const int SecondLayerOpenTime = 200;
        const int FirstLayerCloseTime = 200;
        const int SecondLayerCloseTime = 200;
        const int DelayBetweenTwoOpening = 200;
        const int DelayBetweenTwoClosing = 200;
        
        const int UpperMotorI1 = 2;     
        const int UpperMotorI2 = 3; 
        const int UpperMotorPWM = 11;
        const int LowerMotorI1 = 4;     
        const int LowerMotorI2 = 5; 
        const int LowerMotorPWM = 12;
        
        void upperMotorWriting(double v);
        void lowerMotorWriting(double v);
};

extern SeatOpener seat_opener;

#endif // SEAT_OPENER_H