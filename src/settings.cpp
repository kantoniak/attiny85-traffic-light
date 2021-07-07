#include <avr/sleep.h>
#include "settings.hpp"

#define adc_disable() (ADCSRA &= ~(1<<ADEN))

void setup_power_saving() {
  // Disable ADC
  adc_disable();

  // Set unused pins low so they don't float
  pinMode(PIN_UNUSED_4, OUTPUT);
  pinMode(PIN_UNUSED_5, OUTPUT);
  digitalWrite(PIN_UNUSED_4, LOW);
  digitalWrite(PIN_UNUSED_5, LOW);
}

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
