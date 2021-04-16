#include "projeto.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  char *resultado = sha256("loremipsumksdjdjfjjgjgjg");

  // CRIANDO GENESIS BLOCK DA REDE
  Block * blockchain =  NULL;
  
  blockchain = adicionar_novo_bloco(NULL, NULL, 0, NULL);

  //printf("%d\n", blockchain->timestamp);

  // Lista de transações pendentes no bloco atual
  T_Pendente * pendente = NULL;
  
  // ADICIONAR TRANSACAO A LISTA DE TRANSACOES
  pendente = adicionar_transacao("Pagador", "Recebidor", 16.0, pendente);
  pendente = adicionar_transacao("Pagador", "Recebidor", 48.0, pendente);
  pendente = adicionar_transacao("Pagador", "Recebidor", 50.99, pendente);


  imprimir_lista(pendente);

  minerar_transacoes("Pagador", blockchain);
  //printf("%s", resultado);

  printf("\n");

  return 0;
}