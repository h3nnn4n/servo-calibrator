/*
 * Copyright (C) 2023 Renan S Silva (aka h3nnn4n)
 *
 */

#include <stdint.h>

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

int           ledState       = LOW;
const int     ledPin         = LED_BUILTIN;
const int32_t interval       = 100;
uint32_t      previousMillis = 0;

const int d4 = 2;
const int d5 = 3;
const int d6 = 4;
const int d7 = 5;

const int en = 11;
const int rs = 12;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void blinkenlights();

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

#ifdef __DEBUG
    Serial.begin(9600);
    Serial.println("starting");
#endif

    lcd.begin(16, 2);
    lcd.print("hello, world!");
}

void loop() {
    blinkenlights();

    lcd.setCursor(0, 1);
    lcd.print(millis() / 1000);
}

void blinkenlights() {
    // TODO(h3nnn4n): Move to a lib
    uint32_t currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        if (ledState == LOW) {
            ledState = HIGH;
        } else {
            ledState = LOW;
        }

        digitalWrite(ledPin, ledState);
    }
}
