// atividade 5

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct node_ {
	int data;
	struct node_ *dir, *esq;
} node;

node* inserir( node* p, int dados ) {
	if(!p) {
		node* novo = (node*)malloc(sizeof(node));
		novo->data = dados;
		novo->esq = novo->dir = NULL;
		return novo;
	} else if (dados < p->data) {
		p->esq = inserir (p->esq, dados);
	} else if (dados > p->data) {
		p->dir = inserir (p->dir, dados);
	}
	return p;
}

void destruir( node *p ) {
    if (p) {
        destruir(p->esq);
        destruir(p->dir);
        free(p);
    }
}

void pos_order( node *p, void (*process)(int dado) ) {
    if(p) {
		pos_order(p->esq, process);
		pos_order(p->dir, process);
		process( p->data );
	}
	return;
}

void pre_order( node *p, void (*process)(int dado) ) {
    if(p) {
		process( p->data );
		pre_order(p->esq, process);
		pre_order(p->dir, process);
	}
	return;
}

void in_order( node *p, void (*process)(int dado) ) {
	if(p) {
		in_order(p->esq, process);
		process( p->data );
		in_order(p->dir, process);
	}
	return;
}


void in_level(node *p, void (*process)(int dado)) {
    queue *q = (queue*)malloc(sizeof(queue));
    initialize(q);

    push(q, p);

    while (!empty(q)) {
		// pega o primeiro da fila (front retorna um void*)
        node *n = (node*)front(q);

		// imprime o dado e depois remove da fila
        process(n->data);
        pop(q);

		// adiciona os filhos na fila, se existirem
        if (n->esq) push(q, n->esq);
        if (n->dir) push(q, n->dir);
    }
    free(q);
}


void print(int dado) {
	printf(" %d", dado);
}

int main() {

	int n,a;
	scanf("%d", &n);
	
	node* raiz = 0;
	
	for(int i = 0; i < n; i++) {
		scanf("%d", &a);
		raiz = inserir(raiz, a);
	}
	
	printf("Pr.:");
	pre_order(raiz, print);
	printf("\n");
	printf("In.:");
	in_order(raiz, print);
	printf("\n");
	printf("Po.:");
	pos_order(raiz, print);
	printf("\n");
	printf("Ni.:");
	in_level(raiz, print);
	printf("\n");
	
	destruir(raiz);
	
	return 0;
}