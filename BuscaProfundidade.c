// atividade 8

#include <stdio.h>
#include <stdlib.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2

typedef struct node {
    int dado;
    struct node *prox;
} Node;

typedef struct {
    int v;
    Node **adj; // vetor de vértices onde cada item é uma lista de seus vértices adjacentes
} Grafo;

void inicializar (Grafo *G, int n_vertices);
void inserir (Grafo *G, int v, int dado);
void liberar (Grafo *G);
void dfs_visit (Grafo *G, int u, int cor[], int desc[], int final[], int *tempo, int *aciclico);

int main () {
    int v;
    scanf("%d", &v);

    Grafo grafo;
    inicializar(&grafo, v);

    int vertice, adjacente;

    while (1) {
        scanf("%d,%d", &vertice, &adjacente);
        if (vertice == 0 && adjacente == 0) break;
        inserir(&grafo, vertice-1, adjacente-1);
    }

    int desc[v], final[v];   // armazena o tempo de descoberta e de finalizacao de cada vertice
    int cor[v];              // BRANCO (0) = não visitado / CINZA (1) = em processamento / PRETO (2) = finalizado
    int tempo = 0;
    int aciclico = 1;

    for (int i = 0; i < v; i++) {
        cor[i] = BRANCO;
        desc[i] = 0;
        final[i] = 0;
    }

    for (int i = 0; i < v; i++) {
        if (cor[i] == BRANCO) 
            dfs_visit(&grafo, i, cor, desc, final, &tempo, &aciclico);
    }

    // imprime na ordem crescente de tempo de descoberta
    for (int tempoAtual = 1; tempoAtual <= 2 * v; tempoAtual++) {
        for (int i = 0; i < v; i++) {
            if (desc[i] == tempoAtual)
                printf("%d [%d,%d]\n", i + 1, desc[i], final[i]);
        }
    }

    printf("aciclico: %s", aciclico ? "sim" : "nao");

    liberar(&grafo);

    return 0;
}

// busca em profundidade
void dfs_visit (Grafo *G, int u, int cor[], int desc[], int final[], int *tempo, int *aciclico) {
    cor[u] = CINZA;
    (*tempo)++;
    desc[u] = *tempo;

    for (Node *aux = G->adj[u]; aux != NULL; aux = aux->prox) {
        int v = aux->dado;
        if (cor[v] == BRANCO)
            dfs_visit(G, v, cor, desc, final, tempo, aciclico);
        else if (cor[v] == CINZA) // encontra um vertice ja processado
            *aciclico = 0;
    }
    
    cor[u] = PRETO; // marca como finalizado
    (*tempo)++;
    final[u] = *tempo;
}

void inicializar (Grafo *G, int n_vertices) {
    G->v = n_vertices;
    
    // aloca um vetor de nodes da quantidade de vertices
    G->adj = (Node**)malloc(sizeof(Node*) * n_vertices); 

    // inicializa a lista de adjacencia de cada vertice como null
    for (int i = 0; i < n_vertices; i++)
        G->adj[i] = NULL;
}

void inserir(Grafo *G, int v, int dado) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->dado = dado;
    n->prox = G->adj[v];
    G->adj[v] = n;
}

void liberar (Grafo *G) {
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
    G->adj = NULL;
    G->v = 0;
}