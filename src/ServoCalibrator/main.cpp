/*
 * Copyright (C) 2023 Renan S Silva (aka h3nnn4n)
 *
 */

#include <stdint.h>

#include <Arduino.h>
#include <Wire.h>

int           ledState       = LOW;
const int     ledPin         = LED_BUILTIN;
const int32_t interval       = 100;
uint32_t      previousMillis = 0;

void blinkenlights();

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

#ifdef __DEBUG
    Serial.begin(9600);
    Serial.println("starting");
#endif
}

void loop() { blinkenlights(); }

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
