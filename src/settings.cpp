#include "settings.hpp"

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
