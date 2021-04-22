#include "projeto.h"
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  // CRIANDO GENESIS BLOCK DA REDE
  Block * blockchain =  NULL;
  printf("OLA REDE BLOCKCHAN 2.0\n");
  
  blockchain = adicionar_bloco(NULL, NULL, 0, NULL);
  // Lista de transações pendentes no bloco atual
  Pendentes * pendente = NULL;

  // CRIANDO HASH TABLE
  int tamanho_hash;

  scanf("%d", &tamanho_hash);

  hashTable tabela_hash = criar_hash_table(tamanho_hash);


  // 
  char nomes[tamanho_hash][STR_SIZE + 1];

  // miner
  //MineracaoParams m_params[tamanho_hash]; 


  for (int i = 0; i < tamanho_hash; i++) {
    char nome[STR_SIZE];
    scanf("%s", nome);

    strcpy(nomes[i], nome);

    Carteira carteira;

    carteira.nome = nome;
    carteira.saldo = 100.00;

    inserir_hash_table(tabela_hash, nome, carteira);


  }

  // Iniciar transação
  char pagador[30];
  char recebidor[30];
  float valor_transacionado;

  scanf("%s %s %f", pagador, recebidor, &valor_transacionado);


  pendente = adicionar_transacao(pagador, recebidor, valor_transacionado, pendente);


  /*
  pendente = adicionar_transacao(pagador, recebidor, 16.0, pendente);
  pendente = adicionar_transacao(pagador, recebidor, 48.0, pendente);
  pendente = adicionar_transacao(pagador, recebidor, 50.99, pendente);
  */


  printf("LISTA DE PENDENTES \n");

  imprimir_lista(pendente);

  printf("INICIO MINERACAO \n");
  // criando pthread
  pthread_t thread[tamanho_hash];

  // MINERAR BLCOCOS
  for (int j = 0; j < tamanho_hash; j++) {
    
    MineracaoParams * m1 = (MineracaoParams *) malloc(sizeof (MineracaoParams));
    m1->minerador = nomes[j];
    m1->b = blockchain;
    m1->transacoes = pendente;
    m1->valor_inicial = rand() % 10;


    pthread_create(&thread[j], NULL, minerar_bloco, m1);
  }
  /*
  MineracaoParams * m1 = (MineracaoParams *) malloc(sizeof (MineracaoParams));
  MineracaoParams * m2 = (MineracaoParams *) malloc(sizeof (MineracaoParams));


  m1->minerador = pagador;
  m1->b = blockchain;
  m1->transacoes = pendente;
  m1->valor_inicial = rand() % 10;

  m2->minerador = recebidor;
  m2->b = blockchain;
  m2->transacoes = pendente;
  m2->valor_inicial = rand() % 1000;
  */




  /*
  pthread_create(&thread[0], NULL, minerar_bloco, m1);
  pthread_create(&thread[1], NULL, minerar_bloco, m2);
  */ 

  for(int i = 0; i < tamanho_hash; i++) {
    pthread_join( thread[i], NULL);
  }

  printf("LISTA DE PENDENTES \n");

  imprimir_lista(pendente);

  return 0;
}
