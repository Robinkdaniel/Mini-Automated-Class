# Automated Bell System with LED Display

An Arduino-based classroom automation system that automatically rings a bell according to a daily schedule and displays the real-time clock, weekday, and class period on a P10 LED matrix display.

---

## **Features**

- **Automatic bell ringing** using RTC DS3231
- **Time and day display** on P10 LED matrix
- **Current class period** display based on daily schedule
- **Manual bell override** button support
- **Optional Bluetooth control** for updating schedule remotely
- **Relay control** to operate an electric bell or buzzer

---

## **Components Used**

| **Component**               | **Quantity** | **Description**                                  |
|-----------------------------|--------------|--------------------------------------------------|
| Arduino Uno                 | 1            | Main microcontroller                             |
| RTC Module (DS3231)         | 1            | Real-time clock for precise scheduling           |
| P10 LED Display Panel       | 1 or more    | For displaying time, day, and period             |
| Bluetooth Module (HC-05/HC-06) | 1         | Optional wireless interface                      |
| Relay Module                | 1            | Switches the bell or buzzer                      |
| Buzzer / Electric Bell      | 1            | Output for bell notification                     |
| Power Supply (12V, 5V Reg.) | 1            | Powers the display and Arduino                   |
| Jumper Wires                | As needed    | For all wiring connections                       |
| Diode (1N4007 or similar)   | Optional     | Flyback protection for relay                     |
| Capacitor (e.g., 100µF)     | Optional     | Stabilization for relay trigger                  |

---

## **Circuit Diagram**

**Location:** `circuit_diagram/circuit.png`

### **Main Connections**

**RTC DS3231 → Arduino**
- SDA → A4  
- SCL → A5

**P10 Display → Arduino (SPI Interface)**
- CLK → Pin 11  
- DATA → Pin 12  
- CS (LOAD) → Pin 10  

**Relay Module → Arduino**
- IN → Pin 4  
- VCC & GND → Power Supply (use diode across coil for safety)

**Bluetooth Module → Arduino (Optional)**
- TX → Pin 2 (SoftwareSerial RX)  
- RX → Pin 3 (via voltage divider, SoftwareSerial TX)

**Power**
- Arduino + RTC: 5V  
- P10 Display: 12V regulated (shared ground with Arduino)

**Note:** For inductive components like relays or bells, always use a **flyback diode** (e.g., 1N4007) across the relay coil to protect the Arduino.

---

## **Future Enhancements**

- EEPROM or SD card-based schedule storage
- Mobile app for live configuration via Bluetooth
- LCD fallback display
- Multi-day or exam-mode schedules
- Attendance or RFID integration
