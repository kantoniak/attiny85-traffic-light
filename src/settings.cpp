#include <avr/sleep.h>
#include "settings.hpp"

void init_sleep_mode() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  noInterrupts();
  sleep_enable();
  interrupts();
}

void init_leds() {
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_LED_GREEN, LOW);
}

void attach_button_interrupt(uint8_t pin, void(*handler)(void)) {
  pinMode(pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin), handler, LOW);
}

void detach_button_interrupt(uint8_t pin) {
  detachInterrupt(digitalPinToInterrupt(pin));
}

void enter_sleep() {
  interrupts();
  sleep_cpu();
}
