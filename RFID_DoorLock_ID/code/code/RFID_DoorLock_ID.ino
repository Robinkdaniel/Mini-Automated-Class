# RFID‑Based Door Lock System with User Identification

## Project Overview
This Arduino-based project allows authorized users to unlock a door using RFID cards. Each card's UID is matched; valid IDs unlock an electric solenoid lock briefly, and user identity is displayed on an LCD and logged to the Serial Monitor.

## Features
- RFID authentication
- Solenoid lock control (via transistor)
- 16×2 I2C LCD feedback
- Serial logging of date/time (from RTC, if added)
- Simple user identification by card UID

## Hardware Components
| Component              | Description                         |
|------------------------|-------------------------------------|
| Arduino Uno             | Main microcontroller                |
| MFRC522 RFID module     | RFID card reader                    |
| Solenoid lock (12 V)    | Door locking mechanism              |
| NPN transistor / MOSFET | To switch high current              |
| Diode (1N4007)          | Flyback protection for solenoid     |
| LCD 16×2 (I2C)          | User feedback display               |
| RTC module (optional)   | For timestamp (DS3231 or DS1307)    |
| Power supply 12 V       | Solenoid power                      |
| Jumper wires, breadboard| Connections                         |

## Wiring Summary
- **MISO** → Pin 12  
- **MOSI** → Pin 11  
- **SCK**  → Pin 13  
- **SS**   → Pin 10  
- **RST**  → Pin 9  
- **Solenoid control** → Arduino Pin 4 → 1 kΩ resistor → transistor  
- **Solenoid** → 12 V → transistor → GND  
- **Diode** across solenoid terminals  
- **LCD** wiring via I2C (SDA to A4, SCL to A5)  
- **RTC (optional)** via I²C as well

## Code (RFID_DoorLock.ino)
```cpp
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
#define SOLENOID_PIN 4

MFRC522 rfid(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

String validUID = "15 75 FE 28"; // Replace with your card UID

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  lcd.init();
  lcd.backlight();

  pinMode(SOLENOID_PIN, OUTPUT);
  digitalWrite(SOLENOID_PIN, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Scan your card");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    uid += String(rfid.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();

  Serial.print("Card UID:");
  Serial.println(uid);
  lcd.clear();

  if (uid == validUID) {
    lcd.setCursor(0, 0);
    lcd.print("Access Granted");
    lcd.setCursor(0, 1);
    lcd.print("Welcome!");

    digitalWrite(SOLENOID_PIN, HIGH);
    Serial.println("Door unlocked");
    delay(3000);

    digitalWrite(SOLENOID_PIN, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door Locked");
    Serial.println("Door locked");
    delay(2000);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    Serial.println("Invalid card");
    delay(2000);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan your card");
  rfid.PICC_HaltA();
}
