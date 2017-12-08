#include <stdio.h>
#include "./code-generator.h"

void consumeTransition(Token *token, char *submachine, char *state) {
  printf("Consuming transition: %s %s, Token: %s", submachine, state, token ->value);
}
