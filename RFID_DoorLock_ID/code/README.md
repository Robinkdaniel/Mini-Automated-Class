# RFID Door Lock and Attendance System

A simple Arduino-based door access system using RFID and a solenoid lock, designed for classrooms, labs, or secure entry points. Access is granted only to authorized users based on their unique UID (card identity).

---

## 🔒 Features

- ✅ Solenoid lock control via NPN transistor or 5V relay
- ✅ LCD 16x2 (I2C) display for access feedback
- ✅ Authorized RFID UID-based access
- ✅ Serial Monitor logging (for attendance tracking)
- ✅ Beginner-friendly wiring and code

---

## 🧰 Hardware Components

| Component           | Description                         |
|--------------------|-------------------------------------|
| Arduino Uno         | Microcontroller board               |
| MFRC522 RFID Reader | For scanning RFID cards             |
| Solenoid Lock       | Electromechanical lock              |
| TIP120 / IRF540N    | Transistor to control solenoid      |
| 1N4007 Diode        | Flyback protection for solenoid     |
| Relay Module (optional) | For solenoid control if using relay |
| 16x2 LCD (I2C)       | Status display                     |
| Power Supply (12V)  | To drive solenoid                  |
| RFID Tags/Cards     | Mifare Classic 13.56 MHz           |
| Breadboard + Jumper Wires | For prototyping setup         |

---

## ⚙️ How It Works

1. System starts and waits for RFID card.
2. When a card is scanned, the UID is checked.
3. If the UID matches an authorized entry:
   - LCD displays "Access Granted"
   - Solenoid unlocks for 5 seconds
   - UID is logged to Serial Monitor
4. If the UID is **not** authorized:
   - LCD displays "Access Denied"
   - No action on lock

This can double as a basic **attendance log** by reading the Serial Monitor output.

---

## 🖼️ Circuit Diagram

📌 Available in the file:  
**`A_schematic_diagram_of_an_RFID-based_door_lock_sys.png`**

📷 ![Circuit Diagram Preview](./A_schematic_diagram_of_an_RFID-based_door_lock_sys.png)

---

## 📝 Notes

- Replace `validUID` in the code with the UID shown in the Serial Monitor after scanning your card.
- Ensure the solenoid is powered from an external 12V source, not directly from the Arduino.
- Use a transistor or relay to switch high current safely.
- Always use a flyback diode across the solenoid terminals.

---

## 📈 Future Enhancements

- EEPROM or SD card logging of entries
- RTC module for real-time attendance logs
- Multiple authorized cards with user mapping
- Web dashboard for access logs
- Fingerprint or keypad integration for dual-factor access

---

## 👤 Created By

**Robin**  
Electronics & Communication Engineering – Final Year  
Mini Project under `Mini_Automated_Class`  

---

## 📄 License

MIT License — Free to use, modify, and redistribute.

**Built with ❤️ using Arduino**
