/* TAD para implementacao de funcoes de busca em grafos */
/*Comenta uma ou outra para escolher entre um grafo com dinamico ou estatico */
#include "GrafosListaAdjacencia.h"
//#include "Grafos - Matriz adjacencia.h"

/* DEFINES */
#define BRANCO 0
#define CINZA 1
#define PRETO 2

/* VARIAVEIS */

/* FUNCOES UTILIZADAS */
void betwenness(tgrafo *grafo);
void vertice_central(tgrafo *grafo);
