#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *intToString(int a) {
  char *str = malloc(4); sprintf(str, "%d", a);
  return str;
}
