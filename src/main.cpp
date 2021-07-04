#include <Arduino.h>
#include <avr/sleep.h>

#define LED 1
#define LED_TIME 2048

unsigned long lastTime;
unsigned long ledTimer;
volatile bool flag;

void handleInterrupt() {
  flag = true;
}

void initialLedSequence() {
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
}

void setup() {
  // Sleep setup
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  noInterrupts();
  sleep_enable();
  interrupts();

  // Output LED
  ledTimer = 0;
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  // Button interrupt
  flag = false;
  pinMode(2, INPUT);
  attachInterrupt(0, handleInterrupt, LOW);

  initialLedSequence();
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
    delay(100);
    interrupts();
    sleep_cpu();
  } else {
    ledTimer -= delta;
  }
}
