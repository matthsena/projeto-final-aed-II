#ifndef UFABC_COIN
#define UFABC_COIN

#include <stdio.h>
#include <stdlib.h>

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


Block * adicionar_bloco(char *hash_anterior, Pendentes * transacoes, int nounce, Block * b);
Pendentes * adicionar_transacao(char * remetente, char * destinatario, float valor, Pendentes * p);

void imprimir_lista(Pendentes * p);


void minerar_bloco(char * minerador, Block *b, Pendentes * transacoes);

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