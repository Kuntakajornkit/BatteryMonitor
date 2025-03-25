#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include <Arduino.h>

class BatteryMonitor {
public:
    BatteryMonitor(int pin, float r1, float r2); // กำหนดขา ADC และตัวต้านทาน
    float readVoltage(); // อ่านค่าแรงดันแบตเตอรี่
private:
    int _pin;
    float _r1, _r2;
};

#endif
