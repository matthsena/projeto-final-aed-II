#include "projeto.h"
#include <pthread.h>
#include <math.h>

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
  // blocos
  MineracaoParams * m1 = (MineracaoParams *) malloc(sizeof (MineracaoParams));
  MineracaoParams * m2 = (MineracaoParams *) malloc(sizeof (MineracaoParams));

  m1->minerador = pagador;
  m1->b = blockchain;
  m1->transacoes = pendente;
  m1->vencedor = NULL;
  m1->valor_inicial = rand() % 10;

  m2->minerador = recebidor;
  m2->b = blockchain;
  m2->transacoes = pendente;
  m2->vencedor = NULL;
  m2->valor_inicial = rand() % 1000;

  // criando pthread
  pthread_t thread[2];

  pthread_create(&thread[0], NULL, minerar_bloco, m1);
  pthread_create(&thread[1], NULL, minerar_bloco, m2);



  printf("Waiting for all threads...\n");
  
  for(int i = 0; i < 2; i++) {
    pthread_join( thread[i], NULL);
  }


  
  printf("All thread finished!\n");


  //minerar_bloco(pagador, blockchain, pendente);

  printf("\n");

  printf("LISTA DE PENDENTES \n");

  imprimir_lista(pendente);


  return 0;
}
