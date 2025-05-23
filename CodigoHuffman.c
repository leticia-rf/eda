// atividade 6

#include <stdio.h>
#include <stdlib.h>
#define MAX 500001

typedef struct node {
	int freq;
    char caractere;
	struct node *dir, *esq, *prox;
} Node;

typedef struct {
    Node *inicio;
} Fila;

void inicializarNo (Node *n, int f, char c);
void inserirOrdenado (Fila *f, Node *n);
Node* removerInicio (Fila *f);
void totalBits (Node *n, int profundidade, int *soma);
int indice (char c);
char caractere (int i);

int main () {
    char c;
    int tam = 0;

    // indices: [0-25] => 'a'-'z' / [26] => ' ' / [27] → '\n'
    int frequencia[28] = {0};

    while (scanf("%c", &c) != EOF && tam < MAX) {
        frequencia[indice(c)]++;
    }

    // fila de prioridade com nos armazenando as frequencias
    Fila *fila = (Fila*)malloc(sizeof(Fila));
    fila->inicio = NULL;

    for (int i = 0; i < 28; i++) {
        if (frequencia[i] > 0) {
            Node *novo = (Node*)malloc(sizeof(Node));
            inicializarNo(novo, frequencia[i], caractere(i));
            inserirOrdenado(fila, novo);
        }
    }

    // construcao da arvore de huffman
    while (fila->inicio->prox != NULL) {
        Node *menor1 = removerInicio(fila);
        Node *menor2 = removerInicio(fila);
        Node *soma = (Node*)malloc(sizeof(Node));
        inicializarNo(soma, menor1->freq + menor2->freq, '+');
        soma->esq = menor1;
        soma->dir = menor2;
        inserirOrdenado(fila, soma);
    }
    // ao final, a lista tera apenas um elemento, a raiz da arvore

    int soma = 0;
    totalBits(fila->inicio, 0, &soma);
    printf("%d\n", soma);

    free(fila);

    return 0;
}

int indice (char c) {
    if (c == ' ') return 26;
    if (c == '\n') return 27;
    return c - 'a';
}

char caractere (int i) {
    if (i < 26) return 'a' + i;
    else if (i == 26) return ' ';
    else return '\n';
}

void inicializarNo (Node *n, int f, char c) {
    n->caractere = c;
    n->freq = f;
    n->dir = n->esq = n->prox = NULL;
}

void inserirOrdenado (Fila *f, Node *n) {
    if (f->inicio == NULL) {
        f->inicio = n;
    }
    else if (n->freq < f->inicio->freq) {
        n->prox = f->inicio;
        f->inicio = n;
    }
    else {
        Node *atual = f->inicio;

        while (atual->prox != NULL && atual->prox->freq <= n->freq) {
            atual = atual->prox;
        }
        n->prox = atual->prox;
        atual->prox = n;
    }
}

Node* removerInicio (Fila *f) {
    if (f->inicio == NULL) return NULL;

    Node *aux = f->inicio;
    f->inicio = f->inicio->prox;
    aux->prox = NULL;

    return aux;
}

void totalBits (Node *n, int profundidade, int *soma) {
    if (n == NULL) return;

    if (n->esq == NULL && n->dir == NULL) { // quando chega na folha
        *soma += n->freq * profundidade;    // soma ao total a freq*profundidade
        return;
    }

    totalBits(n->esq, profundidade + 1, soma);
    totalBits(n->dir, profundidade + 1, soma);
}