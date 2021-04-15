#include "projeto.h"
#include <stdio.h>

int main()
{

  char *resultado = sha256("loremipsumksdjdjfjjgjgjg");

  Transacao t = criar_transacao("Pagador", "Recebidor", 16.0);

  printf("%s\n", t.toAddress);

  printf("%s", resultado);

  printf("\n");

  return 0;
}