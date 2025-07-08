#ifndef HEAP_H
#define HEAP_H

typedef struct {
    int *vetor;
    int qntd, max;
} MinHeap;

MinHeap* inicializarHeap(int max);
void destruirHeap(MinHeap *h);
int heapCheia(MinHeap *h);
int heapVazia(MinHeap *h);
void inserirHeap(MinHeap *h, int dado);
int removerHeap(MinHeap* h);

#endif 