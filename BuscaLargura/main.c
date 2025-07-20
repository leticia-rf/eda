// atividade 9

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct g {
    int v;
    int a;
    int **adj;
} Grafo;

void inicializarGrafo (Grafo *G, int n);
void destruirGrafo (Grafo *G );
void inserirGrafo (Grafo *G, int i, int j);
void bfs_visit (Grafo *g, int vis[], int dist[], int inicial);

int main () {
    int v;
    scanf("%d", &v);

    Grafo grafo;
    inicializarGrafo(&grafo, v);

    int vertice, adjacente, vInicial;

    while (1) {
        scanf("%d,%d", &vertice, &adjacente);
        if (vertice == 0 && adjacente == 0) break;
        inserirGrafo(&grafo, vertice-1, adjacente-1);
        inserirGrafo(&grafo, adjacente-1, vertice-1);
    }
    scanf("%d", &vInicial);

    int distancias[v], visitado[v];
    for (int i = 0; i < v; i++) {
        distancias[i] = -1;
        visitado[i] = 0;
    }

    bfs_visit(&grafo, visitado, distancias, vInicial-1);

    printf("Origem da busca: %d\n", vInicial);
    printf("Vertices alcancados e distancias:\n");

    int max_dist = 0;
    for (int i = 0; i < v; i++) {
        if (visitado[i] && distancias[i] > max_dist)
            max_dist = distancias[i];
    }

    for (int d = 0; d <= max_dist; d++) {
        for (int i = 0; i < v; i++)
            if (visitado[i] && distancias[i] == d)
                printf("%d %d\n", i+1, distancias[i]);
    }

    destruirGrafo(&grafo);
    return 0;
}

void inicializarGrafo (Grafo *G, int n) {
    G->v = n;
    G->a = 0;
    G->adj = (int**)malloc(sizeof(int*) * G->v); // aloca as linhas
    for (int i = 0; i < n; i++) {
        G->adj[i] = (int*)malloc(sizeof(int) * G->v); // para cada linha, aloca uma coluna
        for (int j = 0; j < n; j++) G->adj[i][j] = 0; // inicializa com zero
    }
}

void destruirGrafo (Grafo *G ) {
    for(int i = 0; i < G->v; i++)
        free(G->adj[i]);
    free(G->adj);
    G->v = 0;
    G->a = 0;
}

void inserirGrafo (Grafo *G, int i, int j) {
    if (G->adj[i][j] == 0) { // insere e conta se for uma nova aresta
        G->adj[i][j] = 1;
        G->a++;
    }
}

void bfs_visit (Grafo *g, int vis[], int dist[], int inicial) {
    Fila *f = inicializar(g->v);
    inserirFim(f, inicial);
    vis[inicial] = 1;
    dist[inicial] = 0;

    while (!vazia(f)) {
        int pai = primeiroElemento(f);
        removerInicio(f);

        for (int filho = 0; filho < g->v; filho++) {
            if (g->adj[pai][filho] && !vis[filho]) {
                vis[filho] = 1;
                dist[filho] = dist[pai] + 1; 
                inserirFim(f, filho);
            }
        }
    }
}