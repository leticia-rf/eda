// fila com alocacao dinamica e encadeameto simples

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// retorna um ponteiro para a struct fila inicializada com o tam max
Fila* inicializar (int max) {
    Fila* f = malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    f->qntd = 0;
    f->max = max;

    return f;
}

void destruir (Fila* f) {
    while (!vazia(f))
        removerInicio(f);
    free(f);
}

int vazia (Fila *f) {
    return f->qntd == 0;
}

int cheia (Fila *f) {
    return f->qntd == f->max;
}

int inserirFim (Fila *f, T dado) {
    if (cheia(f)) return 0;

    Node *novo = malloc(sizeof(Node));
    novo->dado = dado;        
    novo->proximo = NULL;     

    if (f->inicio == NULL) f->inicio = novo; 
    else f->fim->proximo = novo;

    f->fim = novo;
    f->qntd++;

    return 1;
}

int removerInicio (Fila *f) {
    if (vazia(f)) return 0;

    Node *atual = f->inicio;          
    f->inicio = atual->proximo;    

    if (f->inicio == NULL) f->fim = NULL;

    free(atual);
    f->qntd--;

    return 1;
}

int quantidade (Fila *f) {
    return f->qntd;
}

int primeiroElemento (Fila *f) {
    return f->inicio->dado;
}

void imprimirFila (Fila *f) {
    Node *atual = f->inicio;

    while (atual != f->fim) {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("%d\n", f->fim->dado);
}