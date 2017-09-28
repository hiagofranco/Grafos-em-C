#include <stdio.h>
#include <stdlib.h>
#include "GrafosListaAdjacencia.h"

/* Descricao das funcoes utilizadas */
void inicializaGrafo(tgrafo *grafo, int num_vertices)
{
    int i;
	if(num_vertices > MAXNUMVERTICES)
	{
		printf("Erro: numero de vertices supera o maximo!\n");
		return;
	}
	else
	{
		grafo->num_vertices = num_vertices;

		for (i = 0; i < num_vertices; i++)
		{

			grafo->vet[i] = (tvertice*)malloc(sizeof(tvertice));                    //controi o vetor de vertices com suas informacoes

			if(!grafo->vet[i])
			{
				printf("Erro: espaco insuficiente na memoria!\n");
				return;
			}
			else
			{
				//Vertices com inicio em 0
				grafo->vet[i]->id= i;
				grafo->vet[i]->prox = NULO;
			}
		}
	}
}

void insere_aresta(tgrafo *grafo, svertice v, svertice u, tpeso peso)
{
	taresta* new1 = (taresta*)malloc(sizeof(taresta));
	taresta* new2 = (taresta*)malloc(sizeof(taresta));

	if(new1 == NULO || new2 == NULO)
	{
		printf("Erro: Espaco insuficiente!\n");
		return;
	}

	else
	{
	    tapontador aux;
	    //Insercao dos elementos no bloco novo
		aux = grafo->vet[v]->prox;
		new1->peso = peso;
		new1->id = u;
		new1->prox = aux;
		grafo->vet[v]->prox = new1;

        aux = grafo->vet[u]->prox;
		new2->peso = peso;
		new2->id = v;
		new2->prox = aux;
		grafo->vet[u]->prox = new2;


	}
}

void retira_aresta(tgrafo *grafo, svertice v, svertice u)
{
	/*Aqui vou precisar de dois ponteiros para poder organizar os ponteiros da
	 aresta quando exclui-la*/
	tapontador aux = grafo->vet[v]->prox;

	if(aux->id == u){                       //se o procurado for o primeiro elemento da lista
        grafo->vet[v]->prox = aux->prox;
        free(aux);
        return;
	}

	tapontador aux2 = aux->prox;

	while(aux2 != NULO)
	{
		if(aux2->id == u)
			break;
		else
		{
			aux = aux2;
			aux2 = aux2->prox;
		}
	}

	if(!aux)
	{
		printf("Erro: vertice nao existe!\n");
		return;
	}

	else
	{
		aux->prox = aux2->prox;
		free(aux2);
	}
}

int existe_aresta(tgrafo *grafo, svertice v, svertice u)
{
	tapontador aux = grafo->vet[v]->prox;
    if(aux == NULO)
    {
        return 0;
    }
	while(aux->prox != NULO)
	{
		if(aux->id == u)
        {
            return 1;
		}
        aux = aux->prox;
	}
	return 0;
}

void libera_grafo(tgrafo *grafo)
{
    int i;
    tapontador_vertice aux;
	tapontador aux2, aux3;
	for (i= 0; i < grafo->num_vertices; i++)
	{
		aux = grafo->vet[i];
		aux2 = grafo->vet[i]->prox;
		aux3 = aux2->prox;
		while(aux2 != NULO)
		{
			free(aux2);
			aux2 = aux3;
			aux3 = aux3->prox;
		}
		free(aux);
	}
}

int existe_adj(tgrafo *grafo, svertice v)
{
	if(!grafo->vet[v]->prox)
		return 1;
	else
		return 0;
}

tapontador primeiro_adj(tgrafo *grafo, svertice v)
{
	if(existe_adj(grafo, v))
		return grafo->vet[v]->prox;
	else
		return NULO;
}

tapontador prox_adj(tgrafo *grafo, svertice v)
{
	return grafo->vet[v]->prox;
}

void insere_egressos(tgrafo *grafo,svertice v,int egressos)
{
    grafo->vet[v]->egressos = egressos;
}

void printaGrafo(tgrafo *grafo,int num_vertices)
{
    int i;
    tapontador aux;
    tapontador_vertice aux2;
    for(i = 0; i < num_vertices; i++)
    {
            aux2 = grafo->vet[i];
            printf(" Cidades conectadas com %d de %d habitantes: ", aux2->id, aux2->egressos);
            aux = aux2->prox;
            while(aux != NULL)
            {
                    printf("(Peso: %.2f  Cidade: %d   )  ", aux->peso, aux->id);
                    aux = aux->prox;
            }
            printf("\n");
    }
}
