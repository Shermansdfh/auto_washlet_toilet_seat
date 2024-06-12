#include <Arduino.h>

#ifndef WATER_PUMP_H
#define WATER_PUMP_H

class WaterPump {
    public:
        WaterPump();
        void init();
        void waterPumpOn();
        void waterPumpOff();

    private:
        const int WaterPumpMotorI1 = 6;     
        const int WaterPumpMotorI2 = 7; 
        const int WaterPumpMotorPWM = 13;
};

extern WaterPump water_pump;

#endif // WATER_PUMP_H