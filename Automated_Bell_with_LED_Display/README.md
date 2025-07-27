Automated Bell System with LED Display
An Arduino-based classroom automation system that rings the bell according to a predefined schedule and displays real-time information such as the current time, weekday, and class period on a P10 LED display.

Features
Automatic bell ringing using a Real-Time Clock (RTC DS3231)

Real-time display of time and day on a P10 LED matrix

Shows the current class period based on the schedule

Manual override for triggering the bell

Optional Bluetooth support for updating the schedule remotely

Relay output to drive a bell or buzzer

Components Used
Component	Quantity	Description
Arduino Uno	1	Microcontroller board
RTC Module (DS3231)	1	For accurate timekeeping
P10 LED Display Panel	1 or more	Dot matrix display for time and schedule info
Bluetooth Module (HC-05 or HC-06)	1	Optional wireless control
Relay Module	1	To switch bell or buzzer
Electric Bell / Buzzer	1	Acts as the alarm output
Power Supply (12V)	1	To power P10 display and relay
Jumper Wires	-	For circuit connections
Diode (1N4007 or similar)	Optional	For relay flyback protection
Capacitor	Optional	For stabilizing relay trigger circuit

Circuit Diagram
Detailed Circuit Diagram:

Refer to the image at: circuit_diagram/circuit.png

Key Connections
RTC DS3231 to Arduino

SDA → A4

SCL → A5

P10 Display to Arduino (via SPI)

CLK → Pin 11

DATA → Pin 12

CS → Pin 10

Relay Module to Arduino

IN → Pin 4

VCC/GND as per standard relay connection

Bluetooth Module to Arduino (Optional)

TX → Pin 2 (SoftwareSerial RX)

RX → Pin 3 (SoftwareSerial TX with voltage divider)

Power Supply

5V for Arduino and RTC

12V for P10 panel and Relay (with proper regulators)

Note: When controlling inductive loads such as relays or bells, always use a diode (e.g., 1N4007) in reverse across the coil terminals to prevent back EMF damage.
