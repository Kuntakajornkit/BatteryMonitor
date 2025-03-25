#include "BatteryMonitor.h"

BatteryMonitor::BatteryMonitor(int pin, float r1, float r2) {
    _pin = pin;
    _r1 = r1;
    _r2 = r2;
}

float BatteryMonitor::readVoltage() {
    int analogValue = analogRead(_pin);
    float voltage = (analogValue / 1024.0) * 3.3 * ((_r1 + _r2) / _r1);
    return voltage;
}
