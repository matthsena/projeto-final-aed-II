#include "projeto.h"

int main() {
  char *resultado = sha256("loremipsumksdjdjfjjgjgjg");

  // CRIANDO GENESIS BLOCK DA REDE
  Block * blockchain =  NULL;
  
  blockchain = adicionar_bloco(NULL, NULL, 0, NULL);

  // Lista de transações pendentes no bloco atual
  Pendentes * pendente = NULL;
  
  // ADICIONAR TRANSACAO A LISTA DE TRANSACOES

  char * pagador = (char *) "Pagador";
  char * recebidor = (char *) "Recebidor";

  pendente = adicionar_transacao(pagador, recebidor, 16.0, pendente);
  pendente = adicionar_transacao(pagador, recebidor, 48.0, pendente);
  pendente = adicionar_transacao(pagador, recebidor, 50.99, pendente);

  printf("LISTA DE PENDENTES \n");

  imprimir_lista(pendente);

  printf("INICIO MINERACAO \n");


  minerar_bloco(pagador, blockchain, pendente);

  printf("\n");

  printf("LISTA DE PENDENTES \n");

  imprimir_lista(pendente);


  return 0;
}