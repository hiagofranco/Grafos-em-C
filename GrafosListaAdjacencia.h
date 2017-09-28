/* TAD para grafos criados a partir de uma lista de adjacencia. */
#include<stdio.h>
#include<stdlib.h>
#ifndef GRAFOSLISTAADJACENCIA_H
#define GRAFOSLISTAADJACENCIA_H

/* Defines */
#define MAXNUMVERTICES 50
#define NULO NULL

/* Variaveis */
typedef float tpeso;
typedef int svertice;

//Bloco onde sao alocados o elementos da aresta
typedef struct taresta
{
	tpeso peso;
	int id;
	struct taresta *prox;
} taresta;
//Bloco onde sao alocados o conteudo de cada vertice
typedef struct tvertice
{
    int egressos;
    int id;
    struct taresta *prox;
} tvertice;

typedef taresta* tapontador;
typedef tvertice* tapontador_vertice;

//Bloco do grafo
typedef struct tgrafo
{
	tvertice* vet[MAXNUMVERTICES];
	int num_vertices;
} tgrafo;

/* Funcoes utilizadas */
void inicializaGrafo(tgrafo *grafo, int num_vertices);
void insere_aresta(tgrafo *grafo, svertice v,svertice u, tpeso peso);
void insere_egressos(tgrafo *grafo,svertice v,int egressos);
void printaGrafo(tgrafo *grafo,int num_vertices);
int quantidadeDeVertices(tgrafo *grafo);

#endif // GRAFOSLISTAADJACENCIA_H
