#ifdef DEBUG
#define D if(1)
#else
#define D if(0)
#endif

#include <ctype.h>
#include <stdio.h>
#include "states-machine.h"

State currentState = INITIAL_STATE;

void resetStateMachine() {
  currentState = INITIAL_STATE;
}

State getCurrentState() {
  return currentState;
}

/**
 * Returns a string that describes a state.
 *
 * @param {State} state
 * @returns {String} stateDescription;
 */
char *getStateDescription(State state) {
  char *stateDescription;
  switch (state) {
    case INITIAL_STATE: stateDescription = "INITIAL_STATE"; break;
    case STATE_Q1     : stateDescription = "STATE_Q1"; break;
    case STATE_Q2     : stateDescription = "STATE_Q2"; break;
    case STATE_Q3     : stateDescription = "STATE_Q3"; break;
    case STATE_Q4     : stateDescription = "STATE_Q4"; break;
    case STATE_Q5     : stateDescription = "STATE_Q5"; break;
    case STATE_Q6     : stateDescription = "STATE_Q6"; break;
    case STATE_Q7     : stateDescription = "STATE_Q7"; break;
    case STATE_Q8     : stateDescription = "STATE_Q8"; break;
    case STATE_Q9     : stateDescription = "STATE_Q9"; break;
    case ERROR_STATE  : stateDescription = "ERROR_STATE"; break;
  }

  return stateDescription;
}

/**
 * SIDE EFFECTS ALERT!! 💃
 *
 * This function receives a char and sets the next
 * state of the machine according to the current state.
 *
 * @param {int} a
 */
void processChar(int a) {
  State nextState = INITIAL_STATE;

  D printf("Got the character: \"%c\"\n", a);

  switch (currentState) {
    case INITIAL_STATE:
      if (isalpha(a)) nextState = STATE_Q1;
      else if (isdigit(a)) nextState = STATE_Q2;
      else if (a == ';') nextState = STATE_Q3;
      else if (a == '!' || a == '=') nextState = STATE_Q4;
      else if (a == '>' || a == '<') nextState = STATE_Q9;
      else if (a == ':') nextState = STATE_Q6;
      else if (a == '+' || a == '-'|| a == '*' || a == '/') nextState = STATE_Q8;
      break;

    case STATE_Q1:
      if (isalpha(a)) nextState = STATE_Q1;
      else if (isdigit(a)) nextState = STATE_Q1;
      break;

    case STATE_Q2:
      if (isdigit(a)) nextState = STATE_Q2;

      // reading anything but a number is an error in this stage
      else nextState = ERROR_STATE;

      break;

    case STATE_Q9:
      if (a == '=') nextState = STATE_Q5;
      break;


    case STATE_Q4:
      if (a == '=') nextState = STATE_Q5;
      break;

    case STATE_Q6:
      if (a == '=') nextState = STATE_Q7;
      break;

    case ERROR_STATE:
      nextState = ERROR_STATE;
      break;

    default: break;

  }

  D printf(
    "Transitioning from %s to %s\n",
    getStateDescription(currentState),
    getStateDescription(nextState)
  );

  currentState = nextState;
}
