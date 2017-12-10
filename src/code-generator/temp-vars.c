#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int tempVars = 0;

char *getTempVar() {
  // TODO improve it!
  int length = 2 * sizeof(char);
  char *str = malloc(length);
  sprintf(str, "%d", tempVars);
  strcat(str, "temp");

  tempVars++;
  return str;

}
