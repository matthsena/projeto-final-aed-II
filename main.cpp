#include "projeto.h"
#include <stdio.h>

int main()
{

  char *resultado = sha256("loremipsumksdjdjfjjgjgjg");

  printf("%s", resultado);

  printf("\n");

  return 0;
}