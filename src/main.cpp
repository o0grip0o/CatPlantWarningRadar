/*
 * Proximity Alert - Active Buzzer
 * 
 * HARDWARE:
 *   Ultrasonic TRIG   → Pin 12
 *   Ultrasonic ECHO   → Pin 8
 *   Active Buzzer (+) → Pin 11
 *   Active Buzzer (-) → GND
 */

#include <Arduino.h>

const int TRIG_PIN = 12;
const int ECHO_PIN = 8;
const int BUZZER_PIN = 11;

const float TRIGGER_DISTANCE = 8.0;  // inches

float readDistanceInches() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    unsigned long duration = pulseIn(ECHO_PIN, HIGH, 25000);

    if (duration == 0) {
        return -1.0;
    }

    return duration * 0.00665;
}

void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
    float distance = readDistanceInches();

    if (distance > 0 && distance <= TRIGGER_DISTANCE) {
        digitalWrite(BUZZER_PIN, HIGH);
    } else {
        digitalWrite(BUZZER_PIN, LOW);
    }

    delay(100);
}