enum State {
  INIT,
  STOP,
  STOP_END,
  GO,
  GO_END,
  SLEEP
};

struct Automaton;
Automaton* new_automaton(unsigned long current_time);
void delete_automaton(Automaton* automaton);

void enter_state(Automaton & automaton, State state, unsigned long current_time);
void update_state(Automaton & automaton, unsigned long current_time);

void handle_button(Automaton & automaton, unsigned long current_time);
