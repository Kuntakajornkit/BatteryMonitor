#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BatteryMonitor.h>

// กำหนดที่อยู่ I2C ของจอ LCD (ปกติเป็น 0x27 หรือ 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ตั้งค่าขา ADC และค่า R1, R2 ของ Voltage Divider
BatteryMonitor battery(A0, 100.0, 330.0);

void setup() {
    Serial.begin(115200);
    
    // เริ่มต้นการทำงานของ LCD
    lcd.init();
    lcd.backlight();

    // แสดงข้อความเริ่มต้น
    lcd.setCursor(0, 0);
    lcd.print("Battery Monitor");
    delay(2000);
}

void loop() {
    // อ่านค่าแรงดันแบตเตอรี่
    float voltage = battery.readVoltage();

    // แสดงผลบน Serial Monitor
    Serial.print("Battery Voltage: ");
    Serial.print(voltage);
    Serial.println("V");

    // เคลียร์จอและอัปเดตค่าแบตเตอรี่
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Battery: ");
    lcd.print(voltage);
    lcd.print("V");

    // แจ้งเตือนเมื่อแบตเตอรี่ต่ำ
    if (voltage < 3.3) {
        lcd.setCursor(0, 1);
        lcd.print("Low Battery!");
    }

    delay(1000); // อ่านค่าทุก 1 วินาที
}
