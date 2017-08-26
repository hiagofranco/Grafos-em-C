/* TAD para grafos criados a partir de uma lista de adjacencia. */

/* Defines */
#define MAXNUMVERTICES 100
#define NULO NULL

/* Variaveis */
typedef int tpeso;
typedef int tvertice;

typedef struct taresta
{
	tpeso peso;
	tvertice vertice;
	struct taresta *prox;
} taresta;

typedef taresta* tapontador;

typedef struct tgrafo
{
	taresta* vet[MAXNUMVERTICES];
	int num_vertices;
} tgrafo;

/* Funcoes utilizadas */
void inicializaGrafo(tgrafo *grafo, int num_vertices);
void insere_aresta(tgrafo *grafo, tvertice v, tvertice u, tpeso peso);
void retira_aresta(tgrafo *grafo, tvertice v, tvertice u);
int existe_aresta(tgrafo *grafo, tvertice v, tvertice u);
void libera_grafo(tgrafo *grafo);
int existe_adj(tgrafo *grafo, tvertice v);
tapontador primeiro_adj(tgrafo *grafo, tvertice v);
tapontador prox_adj(tgrafo *grafo, tvertice v);
