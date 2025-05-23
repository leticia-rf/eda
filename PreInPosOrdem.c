// atividade 4

#include <stdio.h>

int BuscaIndice (int raiz, int inicio, int fim, char in[]);
void PosOrdem (char pre[], char in[], int inicio, int fim, int *iRaizPre);

int main () {
    int t;
    scanf("%d", &t);

    while (t--) {
        
        int n;
        scanf("%d", &n);

        char pre[n+1], in[n+1];

        scanf("%s", pre);
        scanf("%s", in);

        int iRaizPre = 0;

        PosOrdem (pre, in, 0, n - 1, &iRaizPre);
        printf("\n");

    }

    return 0;
}

int BuscaIndice (int raiz, int inicio, int fim, char in[]) {
    for (int i = inicio; i <= fim; i++) {
        if (in[i] == raiz) return i;
    }
    return -1;
}

void PosOrdem (char pre[], char in[], int inicio, int fim, int *iRaizPre) {
    if (inicio > fim) return;

    char raiz = pre[*iRaizPre];
    (*iRaizPre)++;

    int iRaizIn = BuscaIndice (raiz, inicio, fim, in);
    
    PosOrdem(pre, in, inicio, iRaizIn - 1, iRaizPre); // esquerda
    PosOrdem(pre, in, iRaizIn + 1, fim, iRaizPre); // direita

    printf("%c", raiz);
}