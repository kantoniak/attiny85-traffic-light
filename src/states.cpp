#include "states.hpp"
#include "settings.hpp"

struct Automaton {
  State state;
  unsigned long state_timeout;
  unsigned long global_timeout;
};

void initialLedSequence() {
  digitalWrite(PIN_LED_RED, HIGH);
  delay(200);
  digitalWrite(PIN_LED_RED, LOW);
  delay(100);
  digitalWrite(PIN_LED_YELLOW, HIGH);
  delay(200);
  digitalWrite(PIN_LED_YELLOW, LOW);
  delay(100);
  digitalWrite(PIN_LED_GREEN, HIGH);
  delay(200);
  digitalWrite(PIN_LED_GREEN, LOW);
}

Automaton* new_automaton(unsigned long current_time) {
  Automaton* automaton = new Automaton;
  automaton->global_timeout = 0;
  enter_state(*automaton, INIT, current_time);
  return automaton;
}

void delete_automaton(Automaton* automaton) {
  delete automaton;
}

void enter_state(Automaton & automaton, State state, unsigned long current_time) {
  automaton.state = state;
  automaton.state_timeout = 0;
  switch (automaton.state) {
    case INIT: {
      initialLedSequence();
      enter_state(automaton, STOP, current_time);
      break;
    }
    case STOP: {
      digitalWrite(PIN_LED_RED, HIGH);
      automaton.state_timeout = current_time + STOP_TIMEOUT;
      break;
    }
    case STOP_END: {
      digitalWrite(PIN_LED_RED, HIGH);
      digitalWrite(PIN_LED_YELLOW, HIGH);
      automaton.state_timeout = current_time + STOP_END_TIMEOUT;
      break;
    }
    case GO: {
      digitalWrite(PIN_LED_GREEN, HIGH);
      automaton.state_timeout = current_time + GO_TIMEOUT;
      break;
    }
    case GO_END: {
      digitalWrite(PIN_LED_YELLOW, HIGH);
      automaton.state_timeout = current_time + GO_END_TIMEOUT;
      break;
    }
    case SLEEP: {
      break;
    }
    default: {
      break;
    }
  }
}

void update_state(Automaton & automaton, unsigned long current_time) {
  switch (automaton.state) {
    case INIT: {
      break;
    }
    case STOP: {
      if (current_time >= automaton.state_timeout) {
        digitalWrite(PIN_LED_RED, LOW);
        enter_state(automaton, STOP_END, current_time);
      }
      break;
    }
    case STOP_END: {
      if (current_time >= automaton.state_timeout) {
        digitalWrite(PIN_LED_RED, LOW);
        digitalWrite(PIN_LED_YELLOW, LOW);
        enter_state(automaton, GO, current_time);
      }
      break;
    }
    case GO: {
      if (current_time >= automaton.state_timeout) {
        digitalWrite(PIN_LED_GREEN, LOW);
        enter_state(automaton, GO_END, current_time);
      }
      break;
    }
    case GO_END: {
      if (current_time >= automaton.state_timeout) {
        digitalWrite(PIN_LED_YELLOW, LOW);
        enter_state(automaton, STOP, current_time);
      }
      break;
    }
    case SLEEP: {
      break;
    }
    default: {
      break;
    }
  }
}
