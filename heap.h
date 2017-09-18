#include<stdio.h>

typedef struct minHeap {
    int size ;
    taresta *elem ;
} minHeap ;

minHeap initMinHeap(int size);
int isEmpty(minHeap *hp);
void swap(taresta *n1, taresta *n2);
void heapify(minHeap *hp, int i);
void insertNode(minHeap *hp, taresta *u);
void deleteNode(minHeap *hp);
void deleteMinHeap(minHeap *hp);
taresta retirar_Min(minHeap* minHeap);
