// atividade 10

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

typedef struct node {
    int dado;
    struct node *prox;
} Node;

typedef struct {
    int v;
    Node **adj; 
    int *grau;
} Grafo;

void inicializarGrafo (Grafo *G, int n_vertices);
void inserirGrafo (Grafo *G, int v, int dado);
void liberarGrafo (Grafo *G);
int ordemTopologica (Grafo* g, int v, int* ordem);

int main () {
    int vertices, linhas;
    scanf("%d %d", &vertices, &linhas); 

    Grafo grafo;
    inicializarGrafo(&grafo, vertices);

    int a, b;
    while (linhas--) {
        scanf("%d %d", &a, &b);
        inserirGrafo(&grafo, a, b);
    }

    int ordem[vertices];

    if (ordemTopologica(&grafo, vertices, ordem)) 
        for (int i = 0; i < vertices; i++)
            printf("%d\n", ordem[i]);
    else
        printf("*\n");

    liberarGrafo(&grafo);
    return 0;
}

int ordemTopologica (Grafo* g, int v, int* ordem) {
    MinHeap *h = inicializarHeap(v);
    
    for (int i = 0; i < g->v; i++) {
        if (g->grau[i] == 0) // insere vértices sem dependências na fila de prioridade
            inserirHeap(h, i);
    }

    int cont = 0;

    while (!heapVazia(h)) {
        int v = removerHeap(h);

        ordem[cont++] = v;

        Node *aux = g->adj[v];
        while (aux != NULL) {
            int u = aux->dado;
            g->grau[u]--; // reduz grau de entrada dos vizinhos
            if (g->grau[u] == 0)
                inserirHeap(h, u);
            aux = aux->prox;
        }

    }
    destruirHeap(h);
    
    if (cont < g->v) return 0; // se houver ciclo, alguns vértices nunca chegarão ao grau zero
    return 1;
}

void inicializarGrafo (Grafo *G, int n_vertices) {
    G->v = n_vertices;
    
    G->adj = (Node**)malloc(sizeof(Node*) * n_vertices);
    for (int i = 0; i < n_vertices; i++)
        G->adj[i] = NULL;
    
    G->grau = (int*)calloc(n_vertices, sizeof(int)); 
}

void inserirGrafo (Grafo *G, int v, int dado) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->dado = dado;
    n->prox = G->adj[v];
    G->adj[v] = n;
    G->grau[dado]++;
}

void liberarGrafo (Grafo *G) {
    for (int i = 0; i < G->v; i++) {
        Node *aux = G->adj[i];
        while (aux != NULL) {
            Node *temp = aux;
            aux = aux->prox;
            free(temp);
        }
        G->adj[i] = NULL;
    }
    free(G->adj);
    free(G->grau);
    G->adj = NULL;
    G->v = 0;
}