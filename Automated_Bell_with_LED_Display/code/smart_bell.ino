#include <Arduino.h>
#include "RTClib.h"
#include <TimerOne.h>
#include <SPI.h>
#include <DMD2.h>
#include "Arial_black_16.h"
#include "SystemFont5x7.h"

#define RELAY_PIN 4
#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1

DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
RTC_DS3231 rtc;
SoftwareSerial BTSerial(10, 11);

bool showPeriod = false;
int lastPeriodNumber = -1;
String btCommand = "";

struct Period {
    int startHour;
    int startMinute;
    int endHour;
    int endMinute;
    char name[12];
    bool isBreak;
};

Period monThuSchedule[] = {
    {8, 55, 9, 58, "EM", false},
    {9, 59, 10, 45, "LAB", false},
    {10, 46, 10, 55, "BREAK", true},
    {10, 56, 11, 50, "LAB", false},
    {12, 46, 13, 30, "LUNCH", true},
    {13, 31, 14, 25, "VLSI", false},
    {14, 26, 15, 25, "ITC", false},
    {15, 26, 16, 15, "COMP", false},
    {16, 16, 16, 25, "OVER", true}
};

void ScanDMD() {
    dmd.scanDisplayBySPI();
}

void setup() {
    Serial.begin(115200);
    BTSerial.begin(9600);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
    }

    Timer1.initialize(5000);
    Timer1.attachInterrupt(ScanDMD);
    dmd.clearScreen(true);
}

void ringBell() {
    Serial.println(" Bell Ringing...");
    digitalWrite(RELAY_PIN, LOW);
    delay(2000);
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Bell Stopped.");
}

String getCurrentPeriod(int hour, int minute, int &periodNumber) {
    int numPeriods = sizeof(monThuSchedule) / sizeof(monThuSchedule[0]);
    int currentMinutes = hour * 60 + minute;
    int actualPeriodCount = 0;

    for (int i = 0; i < numPeriods; i++) {
        if (monThuSchedule[i].isBreak) continue;

        int startMinutes = monThuSchedule[i].startHour * 60 + monThuSchedule[i].startMinute;
        int endMinutes = monThuSchedule[i].endHour * 60 + monThuSchedule[i].endMinute;

        if (currentMinutes >= startMinutes && currentMinutes < endMinutes) {
            periodNumber = ++actualPeriodCount;
            return String(monThuSchedule[i].name);
        }

        actualPeriodCount++;
    }

    periodNumber = -1;
    return "NO CLASS";
}

void scrollTextOnce(const char* text) {
    dmd.clearScreen(true);
    dmd.selectFont(Arial_Black_16);
    dmd.drawMarquee(text, strlen(text), 8, 0);
    while (!dmd.stepMarquee(-1, 0)) {
        delay(50);
    }
}

void displayTime() {
    dmd.clearScreen(true);
    dmd.selectFont(SystemFont5x7);
    DateTime now = rtc.now();

    char dateTimeStr[20];
    sprintf(dateTimeStr, "%02d/%02d/%04d", now.day(), now.month(), now.year());
    dmd.drawString(0, 0, dateTimeStr, strlen(dateTimeStr), GRAPHICS_NORMAL);

    char timeStr[10];
    sprintf(timeStr, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
    dmd.drawString(0, 8, timeStr, strlen(timeStr), GRAPHICS_NORMAL);
}

void loop() {
    DateTime now = rtc.now();
    int periodNumber;
    String currentPeriod = getCurrentPeriod(now.hour(), now.minute(), periodNumber);

    if (periodNumber != -1 && periodNumber != lastPeriodNumber) {
        lastPeriodNumber = periodNumber;
        ringBell();
    }

    if (showPeriod) {
        char periodDisplay[30];
        if (periodNumber != -1) {
            sprintf(periodDisplay, "%d%s Period: %s", periodNumber,
                    (periodNumber == 1 ? "st" :
                     periodNumber == 2 ? "nd" :
                     periodNumber == 3 ? "rd" : "th"),
                    currentPeriod.c_str());
        } else {
            sprintf(periodDisplay, "NO CLASS");
        }
        scrollTextOnce(periodDisplay);
    }

    displayTime();

    if (BTSerial.available()) {
        char c = BTSerial.read();
        if (c == '\n') {
            btCommand.trim();
            if (btCommand == "RING") {
                ringBell();
            } else {
                scrollTextOnce(btCommand.c_str());
            }
            btCommand = "";
        } else {
            btCommand += c;
        }
    }

    showPeriod = !showPeriod;
    delay(3000);
}
