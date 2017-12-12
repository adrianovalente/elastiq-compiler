#include <stdio.h>
#include "../../lib/utarray.h"

UT_array *dataArea, *codeArea = NULL;

void initCode() {
  utarray_new(dataArea, &ut_str_icd);
  utarray_new(codeArea, &ut_str_icd);
}

void printCode() {
  printf("\n\n;------- Data Area");
  char **p = NULL;
  while ((p=(char**)utarray_next(dataArea, p))) {
    printf("\n%s",*p);
  }

  printf("\n\n;------- Code Area\n");

  while ((p=(char**)utarray_next(codeArea, p))) {
    printf("%s\n",*p);
  }

}

void saveCodeToFile(char *outputPath) {
  FILE *fp = fopen(outputPath, "w");
  char **p = NULL;

  fprintf(fp, "\n\n;------- Data Area");
  while ((p=(char**)utarray_next(dataArea, p))) {
    fprintf(fp, "\n%s",*p);
  }

  fprintf(fp, "\n\n;------- Code Area\n");

  while ((p=(char**)utarray_next(codeArea, p))) {
    fprintf(fp, "%s\n",*p);
  }

  fclose(fp);
}

void addToDataArea(char *line) {
  utarray_push_back(dataArea, &line);
}

void addToCodeArea(char *line) {
  utarray_push_back(codeArea, &line);
}
