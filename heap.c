#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

int isEmpty(minHeap *hp){
    if(hp->size == 0) return 1;
    else return 0;
}

minHeap initMinHeap(int size) {
    minHeap hp ;
    hp.size = 0 ;
    return hp ;
}

void swap(node *n1, node *n2) {
    node temp = *n1 ;
    *n1 = *n2 ;
    *n2 = temp ;
}

void heapify(minHeap *hp, int i) {
    int smallest = (LCHILD(i) < hp->size && hp->elem[LCHILD(i)].pesoaresta < hp->elem[i].pesoaresta) ? LCHILD(i) : i ;
    if(RCHILD(i) < hp->size && hp->elem[RCHILD(i)].pesoaresta < hp->elem[smallest].pesoaresta) {
        smallest = RCHILD(i) ;
    }
    if(smallest != i) {
        swap(&(hp->elem[i]), &(hp->elem[smallest])) ;
        heapify(hp, smallest) ;
    }
}

void buildMinHeap(minHeap *hp, int *arr, int size) {
    int i ;

    // Insertion into the heap without violating the shape property
    for(i = 0; i < size; i++) {
        if(hp->size) {
            hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node)) ;
        } else {
            hp->elem = malloc(sizeof(node)) ;
        }
        node nd ;
        nd.pesoaresta = arr[i] ;
        hp->elem[(hp->size)++] = nd ;
    }

    // Making sure that heap property is also satisfied
    for(i = (hp->size - 1) / 2; i >= 0; i--) {
        heapify(hp, i) ;
    }
}

void insertNode(minHeap *hp, int v, int peso) {
    if(hp->size) {
        hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node)) ;
    } else {
        hp->elem = malloc(sizeof(node)) ;
    }

    node nd ;
    nd.idvertice = v;
    nd.pesoaresta = peso;

    int i = (hp->size)++ ;
    while(i && nd.pesoaresta < hp->elem[PARENT(i)].pesoaresta) {
        hp->elem[i] = hp->elem[PARENT(i)] ;
        i = PARENT(i) ;
    }
    hp->elem[i] = nd ;
}

void deleteNode(minHeap *hp) {
    if(hp->size) {
        printf("Deleting node %d\n\n", hp->elem[0].idvertice) ;
        hp->elem[0] = hp->elem[--(hp->size)] ;
        hp->elem = realloc(hp->elem, hp->size * sizeof(node)) ;
        heapify(hp, 0) ;
    } else {
        printf("\nMin Heap is empty!\n") ;
        free(hp->elem) ;
    }
}

void deleteMinHeap(minHeap *hp) {
    free(hp->elem) ;
}

node retirar_Min(minHeap* minHeap)
{
    // Gurdar a raiz do nó
    node raiz = minHeap->elem[0];

    // Troca o nó raiz com o ultímo nó
    node ultimo_Node = minHeap->elem[minHeap->size-1];
    minHeap->elem[0] = ultimo_Node;

    // Reduz tamanho atual  heap e da raiz heapify
    minHeap->size = minHeap->size-1;
    heapify(minHeap,0);

    return raiz;
}
