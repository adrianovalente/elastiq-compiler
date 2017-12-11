#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *intToString(int a) {
  char *str = malloc(4 * sizeof(char)); sprintf(str, "%d", a);
  return str;
}

char *stringWithText(char *a) {
  char *str = malloc((strlen(a) + 1) * sizeof(char));
  strcpy(str, a);
  return str;
}
