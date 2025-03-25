# BatteryMonitor Library for ESP8266

## 📌 คำอธิบาย
ไลบรารีนี้ใช้สำหรับอ่านค่าแบตเตอรี่ 3.7V โดยใช้ ESP8266 ผ่าน ADC (A0)

## 🚀 วิธีติดตั้ง
1. ดาวน์โหลดไลบรารีจาก [GitHub](https://github.com/YourGithub/BatteryMonitor)
2. ใน Arduino IDE ไปที่ `Sketch > Include Library > Add .ZIP Library...`
3. เลือกไฟล์ `BatteryMonitor.zip`
4. ใช้งานได้เลย!

## 🛠 วิธีใช้งาน
```cpp
#include <BatteryMonitor.h>

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
