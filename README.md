# BatteryMonitor Library for ESP8266

## 📌 คำอธิบาย
ไลบรารีนี้ใช้สำหรับอ่านค่าแบตเตอรี่ 3.7V โดยใช้ ESP8266 ผ่าน ADC (A0)

## 🚀 วิธีติดตั้ง
1. ดาวน์โหลดไลบรารีจาก [GitHub](https://github.com/YourGithub/BatteryMonitor)
2. ใน Arduino IDE ไปที่ `Sketch > Include Library > Add .ZIP Library...`
3. เลือกไฟล์ `BatteryMonitor.zip`
4. ใช้งานได้เลย!

## 🛠 วิธีใช้งาน esp8266
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
```

## 📟 แสดงผลบน LCD (I2C)

### การเชื่อมต่อ ESP8266 กับ LCD (I2C)
| LCD | ESP8266 |
|------|--------|
| GND  | GND    |
| VCC  | 3.3V   |
| SDA  | D2 (GPIO4) |
| SCL  | D1 (GPIO5) |

### ตัวอย่างโค้ด
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <BatteryMonitor.h>

#define BATTERY_PIN A0  // ขาอ่านแรงดันแบตเตอรี่

LiquidCrystal_I2C lcd(0x27, 16, 2);  // กำหนดที่อยู่ I2C ของ LCD
BatteryMonitor battery(BATTERY_PIN);

void setup() {
    lcd.begin();
    lcd.backlight();
}

void loop() {
    float voltage = battery.getVoltage();
    int percentage = battery.getPercentage();
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Battery: ");
    lcd.print(voltage);
    lcd.print("V");
    
    lcd.setCursor(0, 1);
    lcd.print("Charge: ");
    lcd.print(percentage);
    lcd.print("%");
    
    delay(2000);  // อัปเดตค่าทุก ๆ 2 วินาที
}
```

## 🛠 วิธีใช้งาน Arduino Uno
```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BATTERY_PIN A0
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(115200);
    lcd.begin();
    lcd.backlight();
}

void loop() {
    int raw = analogRead(BATTERY_PIN);
    float voltage = raw * (5.0 / 1023.0) * ((100.0 + 220.0) / 100.0); // คำนวณแรงดันจริง

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Battery: ");
    lcd.print(voltage);
    lcd.print("V");

    delay(2000);
}
```

Arduino Uno ใช้ได้ แต่ต้องระวังเรื่องแรงดันไฟฟ้า! 🚨

🔹 ปัญหาที่ต้องระวัง
Arduino Uno ใช้แรงดัน 5V

แต่แบตเตอรี่ลิเธียม 3.7V มีแรงดัน 3.0V - 4.2V

ข้อควรระวัง: พิน A0 ของ Uno รับค่าได้แค่ 0-5V

ถ้าต่อแบตฯ ตรง ๆ ค่าอ่านอาจผิดพลาด ❌

ต้องใช้ตัวแบ่งแรงดัน (Voltage Divider)

ใช้ ตัวต้านทาน 2 ตัว ลดแรงดันให้อยู่ในช่วง 0-5V

ตัวอย่างค่า:

R1 = 100kΩ

R2 = 220kΩ

แรงดันที่ A0 จะอยู่ในช่วง 0-4.2V (ปลอดภัย ✅)

🔹 การเชื่อมต่อกับ LCD I2C
LCD	Arduino Uno
GND	GND
VCC	5V
SDA	A4
SCL	A5

## หมายเหตุ
- ค่าแรงดันจะต้องถูกคำนวณตามตัวแบ่งแรงดันที่ใช้ เช่น หากใช้ตัวแบ่งแรงดัน 100K และ 220K ควรใช้สูตรแปลงให้ถูกต้องใน `BatteryMonitor.h`

## License
MIT License
