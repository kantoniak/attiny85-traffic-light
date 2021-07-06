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
  automaton->global_timeout = current_time + SLEEP_TIMEOUT;
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
      enter_sleep();
      break;
    }
    default: {
      break;
    }
  }
}

void leave_state(Automaton & automaton) {
  switch (automaton.state) {
    case STOP: {
      digitalWrite(PIN_LED_RED, LOW);
      break;
    }
    case STOP_END: {
      digitalWrite(PIN_LED_RED, LOW);
      digitalWrite(PIN_LED_YELLOW, LOW);
      break;
    }
    case GO: {
      digitalWrite(PIN_LED_GREEN, LOW);
      break;
    }
    case GO_END: {
      digitalWrite(PIN_LED_YELLOW, LOW);
      break;
    }
    default: {
      break;
    }
  }
}

void update_state(Automaton & automaton, unsigned long current_time) {

  // Go to sleep if no activity
  if (current_time >= automaton.global_timeout) {
    leave_state(automaton);
    enter_state(automaton, SLEEP, current_time);
    return;
  }

  switch (automaton.state) {
    case STOP: {
      if (current_time >= automaton.state_timeout) {
        leave_state(automaton);
        enter_state(automaton, STOP_END, current_time);
      }
      break;
    }
    case STOP_END: {
      if (current_time >= automaton.state_timeout) {
        leave_state(automaton);
        enter_state(automaton, GO, current_time);
      }
      break;
    }
    case GO: {
      if (current_time >= automaton.state_timeout) {
        leave_state(automaton);
        enter_state(automaton, GO_END, current_time);
      }
      break;
    }
    case GO_END: {
      if (current_time >= automaton.state_timeout) {
        leave_state(automaton);
        enter_state(automaton, STOP, current_time);
      }
      break;
    }
    default: {
      break;
    }
  }
}

void handle_button(Automaton & automaton, unsigned long current_time) {
  automaton.global_timeout = current_time + SLEEP_TIMEOUT;

  switch (automaton.state) {
    case STOP: {
      leave_state(automaton);
      enter_state(automaton, STOP_END, current_time);
      break;
    }
    case STOP_END: {
      leave_state(automaton);
      enter_state(automaton, GO, current_time);
      break;
    }
    case GO: {
      leave_state(automaton);
      enter_state(automaton, GO_END, current_time);
      break;
    }
    case GO_END: {
      leave_state(automaton);
      enter_state(automaton, STOP, current_time);
      break;
    }
    case SLEEP: {
      leave_state(automaton);
      enter_state(automaton, STOP, current_time);
    }
    default: {
      break;
    }
  }
}
