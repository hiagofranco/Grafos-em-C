/* Arquivo de TAD para testes. Testando um TAD para grafos. */

/* Defines */
#define MAXNUMVERTICES 100
#define NULO 0

/* Variaveis */
typedef int tpeso;
typedef int tvertice;
typedef int tapontador;

typedef struct tgrafo
{
	tpeso mat[MAXNUMVERTICES][MAXNUMVERTICES];
	int num_vertices;
} tgrafo;

/* Funcoes utilizadas */

void inicializaGrafo(tgrafo *grafo, int num_vertices);
void insere_aresta(tvertice v, tvertice u, tpeso peso, tgrafo *grafo);
int existe_aresta(tvertice v, tvertice u, tgrafo *grafo);
void retira_aresta(tvertice u, tvertice v, tgrafo *grafo);
int existe_adj(tvertice v, tgrafo *grafo);
tapontador primeiro_adj(tvertice v, tgrafo *grafo);
tapontador prox_adj(tvertice v, tapontador aux, tgrafo *grafo);
void recupera_adjacente(tvertice v, tapontador p, tvertice *u, tpeso *peso, tgrafo *grafo);
