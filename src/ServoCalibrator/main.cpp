/*
 * Copyright (C) 2023 Renan S Silva (aka h3nnn4n)
 *
 */

#include <stdint.h>

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h>

int           ledState       = LOW;
const int32_t interval       = 100;
uint32_t      previousMillis = 0;
const int     ledPin         = LED_BUILTIN;

const int servo_pin               = 6;
const int servo_potentiometer_pin = A3;

const int lcd_d4 = 2;
const int lcd_d5 = 3;
const int lcd_d6 = 4;
const int lcd_d7 = 5;
const int lcd_en = 11;
const int lcd_rs = 12;

uint16_t servo_microseconds = 1500;

char buffer[256];

LiquidCrystal lcd(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7);

Servo servo;

void blinkenlights();

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(servo_potentiometer_pin, INPUT);

#ifdef __DEBUG
    Serial.begin(9600);
    Serial.println("starting");
#endif

    lcd.begin(16, 2);
}

void loop() {
    blinkenlights();

    delay(100);

    uint16_t potentiometer_value = analogRead(servo_potentiometer_pin);
    servo_microseconds           = map(potentiometer_value, 0, 1023, 0, 2500);
    servo_microseconds           = (servo_microseconds / 10) * 10;

    snprintf(buffer, sizeof(buffer), "%4d", potentiometer_value);
    lcd.setCursor(0, 0);
    lcd.print(buffer);

    snprintf(buffer, sizeof(buffer), "%4d", servo_microseconds);
    lcd.setCursor(0, 1);
    lcd.print(buffer);

    servo.writeMicroseconds(servo_microseconds);
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
