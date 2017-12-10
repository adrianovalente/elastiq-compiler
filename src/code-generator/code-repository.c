#include <stdio.h>
#include "../../lib/utarray.h"

UT_array *dataArea, *codeArea = NULL;

void initCode() {
  utarray_new(dataArea, &ut_str_icd);
  utarray_new(codeArea, &ut_str_icd);
}

void printCode() {
  char **p = NULL;
  while ((p=(char**)utarray_next(dataArea, p))) {
    printf("\n%s",*p);
  }

  printf("\n;------- Code Area\n\n");

  while ((p=(char**)utarray_next(codeArea, p))) {
    printf("%s\n",*p);
  }

}

void addToDataArea(char *line) {
  utarray_push_back(dataArea, &line);
}

void addToCodeArea(char *line) {
  utarray_push_back(codeArea, &line);
}
