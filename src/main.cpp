#include <Arduino.h>

#include "settings.hpp"
#include "states.hpp"

Automaton* automaton;
volatile bool interrupt_active = false;
volatile bool interrupt_flag = false;

void handleInterrupt() {
  interrupt_flag = true;
  detach_button_interrupt(PIN_BUTTON);
  interrupt_active = false;
}

void setup() {
  init_sleep_mode();
  init_leds();

  interrupt_active = true;
  attach_button_interrupt(PIN_BUTTON, handleInterrupt);

  automaton = new_automaton(millis());
}

void loop() {
  if (interrupt_flag) {
    interrupt_flag = false;
    handle_button(*automaton, millis());
  }

  if (!interrupt_active && digitalRead(PIN_BUTTON) == HIGH) {
    interrupt_active = true;
    attach_button_interrupt(PIN_BUTTON, handleInterrupt);
  }

  update_state(*automaton, millis());
}
