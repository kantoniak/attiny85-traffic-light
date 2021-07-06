#include <Arduino.h>
#include <avr/sleep.h>

#define LED_RED 3
#define LED_YELLOW 1
#define LED_GREEN 0
#define LED_TIME 2048

unsigned long lastTime;
unsigned long ledTimer;
volatile bool flag;

void handleInterrupt() {
  flag = true;
}

void initialLedSequence() {
  digitalWrite(LED_RED, HIGH);
  delay(200);
  digitalWrite(LED_RED, LOW);
  delay(100);
  digitalWrite(LED_YELLOW, HIGH);
  delay(200);
  digitalWrite(LED_YELLOW, LOW);
  delay(100);
  digitalWrite(LED_GREEN, HIGH);
  delay(200);
  digitalWrite(LED_GREEN, LOW);
}

void setup() {
  // Sleep setup
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  noInterrupts();
  sleep_enable();
  interrupts();

  // Output LED
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);

  // Button interrupt
  ledTimer = 0;
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
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_RED, HIGH);
  }

  if (delta > ledTimer) {
    ledTimer = 0;
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
    delay(100);
    interrupts();
    sleep_cpu();
  } else {
    ledTimer -= delta;
  }
}
