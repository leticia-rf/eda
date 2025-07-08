#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

MinHeap* inicializarHeap(int max) {
    MinHeap* h = malloc(sizeof(MinHeap));
    h->vetor = malloc(sizeof(int) * max);
    h->max = max;
    h->qntd = 0;
    return h;
}

void destruirHeap(MinHeap *h) {
    free(h->vetor);
    free(h);
}

int heapCheia(MinHeap *h) {
    return h->qntd == h->max;
}

int heapVazia(MinHeap *h) {
    return h->qntd == 0;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void inserirHeap(MinHeap *h, int dado) {
    if (heapCheia(h)) return;

    int iFilho = h->qntd;
    h->vetor[iFilho] = dado;
    h->qntd++;

    // sobe o elemento para a posição correta 
    while (iFilho > 0) {
        int iPai = (iFilho - 1) / 2;
        if (h->vetor[iFilho] < h->vetor[iPai]) {
            swap(&h->vetor[iPai], &h->vetor[iFilho]);
            iFilho = iPai;
        } else {
            break;
        }
    }
}

int removerHeap(MinHeap* h) {
    int min = h->vetor[0];
    h->vetor[0] = h->vetor[h->qntd-1];
    h->qntd--;

    int iPai = 0; 
    while (1) {
        int iEsq = (iPai * 2) + 1;
        int iDir = (iPai * 2) + 2;
        int menor = iPai;

        if (iEsq < h->qntd && h->vetor[iEsq] < h->vetor[menor])
            menor = iEsq;
        if (iDir < h->qntd && h->vetor[iDir] < h->vetor[menor])
            menor = iDir;
        if (menor == iPai)
            break;

        swap(&h->vetor[iPai], &h->vetor[menor]);
        iPai = menor;
    }

    return min;
}