#ifndef UFABC_COIN
#define UFABC_COIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


#define STR_SIZE 32

typedef struct {
  char * nome;
  float saldo;
} Carteira;

struct listaEncadeada {
    char chave[STR_SIZE];
    Carteira valor;
    listaEncadeada *proximo;
};

struct hashEncadeada {
    listaEncadeada *primeiro;
};

struct hashTable {
  union {
      hashEncadeada *encadeada;
  } tabela;
  int tamanho;
};

typedef struct {
  char * remetente;
  char * destinatario;
  float valor;
} Transacao;

typedef struct pendente {
  Transacao transacao;
  struct pendente * prox;
} Pendentes;

typedef struct Block {
  int timestamp;
  char *hash;
  Pendentes * transacoes;
  int nounce;
  struct Block * prox;
} Block;

typedef struct MineracaoParams {
  char * minerador; 
  Block * b; 
  Pendentes * transacoes;
  int valor_inicial;
  hashTable * t;
} MineracaoParams;

typedef struct MineracaoRetorno {
  char * minerador; 
  int nounce;
  Pendentes * transacoes;
} MineracaoRetorno;


Block * adicionar_bloco(char *hash_anterior, Pendentes * transacoes, int nounce, Block * b);

Pendentes * adicionar_transacao(char * remetente, char * destinatario, float valor, Pendentes * p);

void imprimir_lista(Pendentes * p);

void * minerar_bloco(void * args);

int hash(const char chave[STR_SIZE], int tamanho, int tentativa = 0);

hashTable criar_hash_table (int tamanho);

void destruir_hash_table (hashTable hash);

void inserir_hash_table (hashTable hash, char chave[STR_SIZE], Carteira valor);

void retornar_saldo(hashTable hash, char chave[STR_SIZE]);



// DECLARAÇOES PARA O SHA256
#define SHA256_BLOCK_SIZE 32
#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))
#define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define EP1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SIG0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

typedef unsigned char BYTE;
typedef unsigned int WORD;

typedef struct {
  BYTE data[64];
  WORD datalen;
  unsigned long long bitlen;
  WORD state[8];
} SHA256_CTX;

void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const BYTE data[], size_t len);
void sha256_final(SHA256_CTX *ctx, int hash[]);
char *sha256(const char *data);

#endif