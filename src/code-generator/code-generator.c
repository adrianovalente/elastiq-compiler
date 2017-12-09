#include <stdio.h>
#include "../../lib/utarray.h"

#include "./code-generator.h"

UT_array *varsBeingDeclared = NULL;
UT_array *dataArea, *codeArea;
char *s;

void consumeTransition(CodeGeneratorTransition *transition) {
  char *submachine = transition->submachine;
  char *value = transition->token->value;
  int state = transition->state;

  printf("Consuming transition: %s %d, Token: %s\n", submachine, state, value);

  if (strcmp(submachine, "PROGRAMA") == 0) {
    s = "@ /0000"; utarray_push_back(dataArea, &s);
    s = "ZERO K /0000"; utarray_push_back(dataArea, &s); // zero constant
//    s = "JP INICIO"; utarray_push_back(dataArea, &s);

    s = "INICIO LD ZERO"; utarray_push_back(codeArea, &s);
  }

  if (strcmp(submachine, "declaracoes") == 0 && strcmp(value, "VAR") == 0) {
    utarray_new(varsBeingDeclared, &ut_str_icd);
  }

  if (strcmp(submachine, "id") == 0 && state == 2) {
    if (varsBeingDeclared != NULL) {
      /*
       * Allocating memory as a local array
       * https://stackoverflow.com/questions/8716714/bus-error-10-error
       */
      s = malloc(strlen(value) + 1);
      strcpy(s, value); strcat(s, " K /0000"); utarray_push_back(dataArea, &s);

      // TODO add to symbols table
    }
  }

}

void printCode() {
  char **p = NULL;
  while ( (p=(char**)utarray_next(dataArea ,p))) {
    printf("\n%s",*p);
  }

  printf("\n;------- Code Area\n\n");
  
  while ( (p=(char**)utarray_next(codeArea ,p))) {
    printf("%s\n",*p);
  }

}

/**
 * Inits this module, initializing arrays and setting initial vars.
 */
void initCodeGenerator() {
  utarray_new(dataArea, &ut_str_icd);
  utarray_new(codeArea, &ut_str_icd);

}
