#include "projeto.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  // Lista de transações pendentes no bloco atual
  TransacaoPendente * pendente = NULL;

  char *resultado = sha256("loremipsumksdjdjfjjgjgjg");
  // INICIAR TRANSAÇAO ENTRE USUARIOS NA REDE
  Transacao transacao = iniciar_transacao("Pagador", "Recebidor", 16.0);
  // ADICIONAR TRANSACAO A LISTA DE TRANSACOES
  Transacao transacao2 = iniciar_transacao("Pagador", "Recebidor", 48.0);

  Transacao transacao3 = iniciar_transacao("Pagador", "Recebidor", 50.99);


  pendente = adicionar_transacao(transacao, pendente);

  pendente = adicionar_transacao(transacao2, pendente);

  pendente = adicionar_transacao(transacao3, pendente);


  imprimir_lista(pendente);

  printf("%s", resultado);

  printf("\n");

  return 0;
}