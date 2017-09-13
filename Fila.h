/* TAD para fila dinamica */

/* DEFINES */

/* VARIAVEIS */
typedef int elem;

typedef struct no
{
  elem info;
  elem prioridade;
  struct no *prox;
} no;

typedef struct {
  int qtd_elementos;
  no *ini, *fim;
} Fila;

/* FUNCOES */
void criaFila(Fila *F);
int entraFila(Fila *F, elem *x, elem *prior);
int saiFila(Fila *F);
int estaVazia(Fila *F);
