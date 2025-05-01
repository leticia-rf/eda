// atividade 3

#include <stdio.h>
#include <string.h>

void link (int tree[], int a, int b);
void cut (int tree[], int a);
int lca (int tree[], int a, int b, int n);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    char op[10];
    int tree[n + 1];

    for (int i = 0; i <= n; i++) {
        tree[i] = i;
    }

    while (m--) {
        int a, b;

        scanf("%s", op);

        if (!strcmp(op, "lca")) {
            scanf("%d %d", &a, &b);            
            printf("%d\n", lca (tree, a, b, n));

        } else if (!strcmp(op, "link")) {
            scanf("%d %d", &a, &b);
            link(tree, a, b);

        } else if (!strcmp(op, "cut")) {
            scanf("%d", &a);
            cut(tree, a);

        }
    }

    return 0;
}

void link (int tree[], int a, int b) {
    tree[a] = b;
}

void cut (int tree[], int a) {
    tree[a] = a;
}

int lca (int tree[], int a, int b, int n) {
    int visited[n+1];
    for (int i = 0; i <= n; i++) visited[i] = 0;

    // enquanto a não chegar na raiz, marca seus ancestrais como visitado
    while (a != tree[a]) {
        visited[a] = 1;
        a = tree[a];
    }
    visited[a] = 1; // marca a raiz como visitada tambem 
    
    // procura o primeiro ancestral de b marcado como visitado, ou seja, que tambem e ancestral de a
    while (!visited[b]) {
        b = tree[b];
    }

    return b;
}