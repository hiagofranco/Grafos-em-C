/* TAD para fila dinamica */

/* DEFINES */

/* VARIAVEIS */
typedef int elem;

typedef struct no
{
  elem info;
  struct no *prox;
} no;

typedef struct {
  int qtd_elementos;
  no *ini, *fim;
} Fila;

/* FUNCOES */
void criaFila(Fila *F);
int entraFila(Fila *F, elem *x);
int saiFila(Fila *F, elem *x);
int estaVazia(Fila *F);
