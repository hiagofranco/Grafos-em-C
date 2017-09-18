#include<stdio.h>

typedef struct node {
    int idvertice;
    int pesoaresta;
} node ;

typedef struct minHeap {
    int size ;
    node *elem ;
} minHeap ;

minHeap initMinHeap(int size);
void swap(node *n1, node *n2);
void heapify(minHeap *hp, int i);
void buildMinHeap(minHeap *hp, int *arr, int size);
void insertNode(minHeap *hp, int v, int peso);
void deleteNode(minHeap *hp);
void deleteMinHeap(minHeap *hp);
