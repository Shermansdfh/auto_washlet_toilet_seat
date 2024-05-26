#include <Arduino.h>

#ifndef WATER_PUMP_H
#define WATER_PUMP_H

class WaterPump {
    public:
        WaterPump();
        void init();
        void WaterPumpOn();
        void WaterPumpOff();
};

extern WaterPump water_pump;

#endif // WATER_PUMP_H