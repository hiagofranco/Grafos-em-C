#include<stdio.h>

    typedef struct Heap_node
    {
        int vertice;
        int peso;
    }Heap_node;

    typedef struct Heap
    {
        int tam_max;
        int tam_atual;
        int *pos;
        struct Heap_node **matriz;
    }Heap;

int filho_Esquerda(int i);
int filho_Direita(int i);
struct Heap_node* new_Min_Heap_Node(int v, int peso);
struct Heap* create_Min_Heap(int tam_max);
int is_In_MinHeap(struct Heap *minHeap, int v);
int isEmpty(struct Heap* minHeap);
void swap_MinHeap_Node(struct Heap_node** matriz_a, struct Heap_node** matriz_b);
void min_Heapify(struct Heap* minHeap, int i);
struct Heap_node* retirar_Min(struct Heap* minHeap);
