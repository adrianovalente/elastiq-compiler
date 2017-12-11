#include <string.h>
#include <stdlib.h>

#include "../utils/strings.h"

int tempVars = 0;

char *getTempVar() {
  char *str = intToString(tempVars); strcat(str, "temp");

  tempVars++;
  return str;
}
