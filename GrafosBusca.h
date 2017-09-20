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
int Floydinho(tgrafo *grafo);
void Dijkstra(tgrafo *grafo);
void Operacao_Dijkstra(tgrafo *grafo,int numv,int matriz_antecessores[][numv]);
void guardar(int tam, int matriz_guardada[][tam],int i, int j,int valor);
int quantidadeDeVertices(tgrafo *grafo);
void betwenness(tgrafo *grafo);
void operacao_betweenness(int numv,int ant[][numv]);

