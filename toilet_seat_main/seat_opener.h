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
        void lowerMotorWriting(double v);
    private:
        enum SeatState {
            ALL_CLOSED,
            FIRST_LAYER_OPENED,
            SECOND_LAYER_OPENED
        };

        void upperMotorWriting(double v);

        SeatState current_state;
        
        // TODO: test motor pulling time
        const int FirstLayerOpenTime = 2500;
        const int SecondLayerOpenTime = 3500;
        const int FirstLayerCloseTime = 4250;
        const int SecondLayerCloseTime = 5500;
        const int DelayBetweenTwoOpening = 200;
        const int DelayBetweenTwoClosing = 1000;
        
        const int UpperMotorAIN1 = 2;     
        const int UpperMotorAIN2 = 3; 
        const int UpperMotorPWMA = 11;
        const int LowerMotorBIN1 = 4;     
        const int LowerMotorBIN2 = 5; 
        const int LowerMotorPWMB = 12;

        
        //void upperMotorWriting(double v);
        //void lowerMotorWriting(double v);        
};

extern SeatOpener seat_opener;

#endif // SEAT_OPENER_H