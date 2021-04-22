#include "projeto.h"
#include <pthread.h>

int main(int argc, char *argv[]) {
  // CRIANDO GENESIS BLOCK DA REDE
  Block * blockchain =  NULL;
  printf("REDE BLOCKCHAN UFABC COIN\n");
  printf("---------\n");

  blockchain = adicionar_bloco(NULL, NULL, 0, NULL);
  // Lista de transações pendentes no bloco atual
  Pendentes * pendente = NULL;

  // CRIANDO HASH TABLE
  int tamanho_hash;

  scanf("%d", &tamanho_hash);

  hashTable tabela_hash = criar_hash_table(tamanho_hash);
  char nomes[tamanho_hash][STR_SIZE + 1];

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

  printf("---------\n");
  printf("LISTA DE TRANSAÇOES PENDENTES \n");
  imprimir_lista(pendente);

  // criando pthread
  pthread_t thread[tamanho_hash];

  // MINERAR BLCOCOS
  for (int j = 0; j < tamanho_hash; j++) {
    
    MineracaoParams * m1 = (MineracaoParams *) malloc(sizeof (MineracaoParams));
    m1->minerador = nomes[j];
    m1->b = blockchain;
    m1->transacoes = pendente;
    m1->valor_inicial = rand() % 10;
    m1->t = &tabela_hash;

    pthread_create(&thread[j], NULL, minerar_bloco, m1);
  }
  

  for(int i = 0; i < tamanho_hash; i++) {
    pthread_join( thread[i], NULL);
  }

  printf("---------\n");
  printf("SALDOS \n");

   for (int k = 0; k < tamanho_hash; k++) {
    retornar_saldo(tabela_hash, nomes[k]);
  }

  printf("---------\n");
  printf("LISTA DE TRANSAÇOES PENDENTES \n");
  imprimir_lista(pendente);

  return 0;
}
