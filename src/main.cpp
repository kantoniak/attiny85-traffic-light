#include <Arduino.h>

#include "settings.hpp"
#include "states.hpp"

Automaton* automaton;

void setup() {
  init_leds();
  automaton = new_automaton(millis());
}

void loop() {
  update_state(*automaton, millis());
}
