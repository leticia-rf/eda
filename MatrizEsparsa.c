// atividade 2

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int linha;
    int coluna;
    int numero;
} Coordenadas;

void ConverterCSR (Coordenadas m[], int A[], int C[], int R[], int k, int n);
int RecuperarValor (int A[], int C[], int R[], int a, int b);
int CompararCoordenadas (const void *a, const void *b);

int main () {

    int k;
    scanf("%d", &k);

    Coordenadas *m = (Coordenadas *)malloc(k * sizeof(Coordenadas));

    int n_linhas = 0, n_colunas = 0;

    for (int i = 0; i < k; i++) {
        scanf("%d %d %d", &m[i].linha, &m[i].coluna, &m[i].numero);
        if (m[i].linha > n_linhas) n_linhas = m[i].linha;
        if (m[i].coluna > n_colunas) n_colunas = m[i].coluna;
    }
    n_linhas++; 
    n_colunas++;
    
    qsort(m, k, sizeof(Coordenadas), CompararCoordenadas);

    int *A = (int *)malloc(k * sizeof(int));
    int *C = (int *)malloc(k * sizeof(int));
    int *R = (int *)malloc((n_linhas + 1) * sizeof(int));

    ConverterCSR (m, A, C, R, k, n_linhas);
    free(m);

    while (1) {
        int a, b;

        scanf("%d %d", &a, &b);
        if (a == -1 && b == -1) break;

        int valor;

        if (a < 0 || a >= n_linhas || b < 0 || b >= n_colunas) {
            valor = 0;
        }
        else {
            valor = RecuperarValor (A, C, R, a, b);
        }

        printf("(%d,%d) = %d\n", a, b, valor);
    }

    free(A);
    free(C);
    free(R);

    return 0;
}

void ConverterCSR (Coordenadas m[], int A[], int C[], int R[], int k, int n) {

    for (int i = 0; i <= n; i++) {
        R[i] = 0;
    }
    
    for (int i = 0; i < k; i++) {
        A[i] = m[i].numero;       
        C[i] = m[i].coluna;       
        R[m[i].linha + 1]++; // conta os elementos por linha
    }

    // calcula os índices acumulados no vetor R
    for (int i = 1; i <= n; i++) {
        R[i] += R[i - 1];
    }
}

int RecuperarValor (int A[], int C[], int R[], int a, int b) {

    int diferenca = R[a+1] - R[a];

    if (!diferenca || a < 0 || b < 0) return 0; // se a linha não tem elementos, retorna 0

    // se não, procura b na linha
    for (int i = R[a]; i < R[a+1]; i++) {
        if (C[i] == b) return A[i]; // se achar, retorna o valor
    }
    return 0; // se não encontrar, retorna 0
    
}

int CompararCoordenadas (const void *a, const void *b) {
    // convertem os ponteiros a e b para o tipo Coordenadas (minha struct)
    Coordenadas *elem1 = (Coordenadas *) a;
    Coordenadas *elem2 = (Coordenadas *) b;

    // se a linha (i) for igual, compara pela coluna (j)
    if (elem1->linha == elem2->linha) {
        return elem1->coluna - elem2->coluna; 
    } 
    else {
        return elem1->linha - elem2->linha;
    }
}