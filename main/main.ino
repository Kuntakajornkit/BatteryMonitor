#include <BatteryMonitor.h>

// กำหนดขา A0, ตัวต้านทาน R1=100kΩ, R2=330kΩ
BatteryMonitor battery(A0, 100.0, 330.0);

void setup() {
    Serial.begin(115200);
}

void loop() {
    float voltage = battery.readVoltage();
    Serial.print("Battery Voltage: ");
    Serial.print(voltage);
    Serial.println("V");

    if (voltage < 3.3) {
        Serial.println("⚠️ Battery Low! Please recharge.");
    }

    delay(1000);
}
