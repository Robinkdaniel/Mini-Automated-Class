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
