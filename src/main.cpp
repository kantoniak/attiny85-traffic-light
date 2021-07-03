#include <Arduino.h>

#define LED 1
#define LED_TIME 2048

unsigned long lastTime;
unsigned long ledTimer;
volatile bool flag;

void handleInterrupt() {
  flag = true;
}

void setup() {
  // Output LED
  ledTimer = 0;
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  // Button interrupt
  flag = false;
  attachInterrupt(0, handleInterrupt, CHANGE);

  lastTime = millis();
}

void loop() {
  unsigned long currTime = millis();
  unsigned long delta = currTime - lastTime;
  lastTime = currTime;

  if (flag) {
    flag = false;
    ledTimer = LED_TIME;
    digitalWrite(LED, HIGH);
  }

  if (delta > ledTimer) {
    ledTimer = 0;
    digitalWrite(LED, LOW);
  } else {
    ledTimer -= delta;
  }
}
