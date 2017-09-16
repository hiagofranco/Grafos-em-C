#include<stdio.h>
#include<stdlib.h>
#include"heap.h"

#define TRUE 1
#define FALSE 0

int filho_Esquerda(int i)
{
    return 2i+1;
}

int filho_Direita(int i)
{
    return 2i+2;
}

struct Heap_node* new_Min_Heap_Node(int v, int peso)
{
    struct Heap_node* min_Heap_Node = (struct Heap_node*) malloc(sizeof(struct Heap_node));
    min_Heap_Node->vertice = v;
    min_Heap_Node->peso = peso;
    return min_Heap_Node;
}
struct Heap* create_Min_Heap(int tam_max)
{
    struct Heap* minHeap =(struct Heap*) malloc(sizeof(struct Heap));
    minHeap->pos = (int *)malloc(tam_max * sizeof(int));
    minHeap->tam_atual = 0;
    minHeap->tam_max = tam_max;
    minHeap->matriz =(struct Heap_node**) malloc(tam_max * sizeof(struct Heap_node*));
    return minHeap;
}
int is_In_MinHeap(struct Heap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->tam_atual)
   {
       return TRUE;
   }
   else
   {
        return FALSE;
   }
}
int isEmpty(struct Heap* minHeap)
{
    if(minHeap->tam_atual == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
void swap_MinHeap_Node(struct Heap_node** matriz_a, struct Heap_node** matriz_b)
{
    struct Heap_node* matriz_temp = *matriz_a;
    *matriz_a = *matriz_b;
    *matriz_b = matriz_temp;
}
void min_Heapify(struct Heap* minHeap, int i)
{
    int menor, esq, dir;
    menor = i;
    esq = filho_Esquerda(i);
    dir = filho_Direita(i);

    if (esq < minHeap->tam_atual && minHeap->matriz[esq]->peso < minHeap->matriz[menor]->peso)
    {
        menor = esq;
    }
    if (dir < minHeap->tam_atual &&minHeap->matriz[dir]->peso < minHeap->matriz[menor]->peso)
    {
        menor = dir;
    }
    if (menor!=i)
    {
        //Nós a serem trocados na minheap
        Heap_node *menor_Node = minHeap->matriz[menor];
        Heap_node *i_Node = minHeap->matriz[i];

        //trocar Posições
        minHeap->pos[menor_Node->vertice] = i;
        minHeap->pos[i_Node->vertice] = menor;

        // Trocar Nós
        swap_MinHeap_Node(&minHeap->matriz[menor], &minHeap->matriz[i]);

        min_Heapify(minHeap, menor);
    }
}
struct Heap_node* retirar_Min(struct Heap* minHeap)
{
    if (isEmpty(minHeap))
    {
        return NULL;
    }
    // Gurdar a raiz do nó
    struct Heap_node* raiz = minHeap->matriz[0];

    // Troca o nó raiz com o ultímo nó
    struct Heap_node* ultimo_Node = minHeap->matriz[minHeap->tam_atual - 1];
    minHeap->matriz[0] = ultimo_Node;

    // Atualizar a posicao do ultimo nó
    minHeap->pos[raiz->vertice] = minHeap->tam_atual-1;
    minHeap->pos[ultimo_Node->vertice] = 0;

    // Reduz tamanho atual  heap e da raiz heapify
    minHeap->tam_atual = minHeap->tam_atual-1;
    min_Heapify(minHeap,0);

    return raiz;
}

