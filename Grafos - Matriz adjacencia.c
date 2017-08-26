#include "Grafos - Matriz adjacencia.h"
#include <stdio.h>
#include <stdlib.h>

/* Descricao das funcoes utilizadas */

void inicializaGrafo(tgrafo *grafo, int num_vertices)
{
	int i, j;

	grafo->num_vertices = num_vertices;
	for (int i = 0; i < grafo->num_vertices; i++)
		for (int j = 0; j < grafo->num_vertices; j++)
			grafo->mat[i][j] = 0;
}

void insere_aresta(tvertice v, tvertice u, tpeso peso, tgrafo *grafo)
{
	grafo->mat[v][u] = peso;
}

tpeso existe_aresta(tvertice v, tvertice u, tgrafo *grafo)
{
	return grafo->mat[v][u];
}

void retira_aresta(tvertice u, tvertice v, tgrafo *grafo)
{
	if(grafo->mat[v][u] == 0)
	{
		printf("Erro: Aresta inexistente!\n");
		return;
	}
	else
		grafo->mat[v][u] = 0;
}

int existe_adjacentes(tvertice v, tgrafo *grafo)
{
	tvertice aux;

	for(aux = 0; aux < grafo->num_vertices; aux++)
	{
		if(grafo->mat[v][aux] != 0)
			return 1;
	}
	return 0;
}

tapontador primeiro_adjacente(tvertice v, tgrafo *grafo)
{
	tapontador aux;

	for (aux = 0; aux < grafo->num_vertices; aux++)
		if(grafo->mat[v][aux] != 0)
			return aux;

	return 0;
}

tapontador prox_adjacente(tvertice v, tapontador aux, tgrafo *grafo)
{
	for(; aux < grafo->num_vertices; aux++)
		if(grafo->mat[v][aux] != 0)
			return aux;

	return 0;
}

void recupera_adjacente(tvertice v, tapontador p, tvertice *u, tpeso *peso, tgrafo *grafo)
{
	*u = p;
	*peso = grafo->mat[v][p];
}
