typedef enum {
  INITIAL_STATE,
  STATE_Q1,
  STATE_Q2,
  STATE_Q3,
  STATE_Q4,
  STATE_Q5,
  STATE_Q6,
  STATE_Q7,
  STATE_Q8,
  STATE_Q9,
  ERROR_STATE
} State;


char *getStateDescription(State state);
void processChar(int a);
void resetStateMachine();
State getCurrentState();
