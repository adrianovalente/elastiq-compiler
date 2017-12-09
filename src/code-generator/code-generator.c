#include <stdio.h>
#include "../../lib/utarray.h"

#include "./code-generator.h"

UT_array *dataArea, *codeArea;

void consumeTransition(Token *token, char *submachine, char *state) {
  printf("Consuming transition: %s %s, Token: %s", submachine, state, token ->value);
}

/**
 * Inits this module, initializing arrays and setting initial vars.
 */
void initCodeGenerator() {
  utarray_new(dataArea, &ut_str_icd);
  utarray_new(codeArea, &ut_str_icd);

}

