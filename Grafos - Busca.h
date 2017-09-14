/* TAD para implementacao de funcoes de busca em grafos */
/*Comenta uma ou outra para escolher entre um grafo com dinamico ou estatico */
#include "Grafos_Lista_adjacencia.h"
//#include "Grafos - Matriz adjacencia.h"

/* DEFINES */
#define BRANCO 0
#define CINZA 1
#define PRETO 2

/* VARIAVEIS */

/* FUNCOES UTILIZADAS */
void busca_profundidade(tgrafo *grafo);
void visita_dfs(tvertice v, int cor[], tgrafo *grafo);
void busca_largura(tgrafo *grafo);
void visita_bfs(tvertice v, int cor[], tgrafo *grafo);
int Floydinho(tgrafo *grafo);
