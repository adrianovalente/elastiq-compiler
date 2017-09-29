typedef enum {
  INITIAL_STATE,
  STATE_Q1,
  STATE_Q2,
  ERROR_STATE
} State;


char *getStateDescription(State state);
void processChar(int a);
void resetStateMachine();
State getCurrentState();
