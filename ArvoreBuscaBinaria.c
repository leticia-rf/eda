// atividade 7

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _bst {
    struct _bst* l;
    struct _bst* r;
    char* str;
} bst;

bst* get(bst* root, char* str);
bst* put(bst* root, char* str);
bst* max(bst* root);
bst* min(bst* root);
bst* rem(bst* root, char* str);
void del(bst* root);

int main() {

    char comando[2], palavra[255];
    bst* raiz = NULL;

    while(scanf("%s", comando) != EOF) {
        scanf("%s", palavra);
        if( comando[0] == 'P' ) 
            raiz = put(raiz,palavra);
        else if( comando[0] == 'R' ) 
            raiz = rem(raiz,palavra);
        else if( comando[0] == 'G' ) {
            bst* result = get(raiz,palavra);
            if( result )
                printf("%s encontrada\n", result->str);
            else
                printf("%s nao foi encontrada\n", palavra);
        }
    }

    del(raiz);
    return 0;
}

bst* get(bst* root, char* str) {
    while (root) {
        int cmp = strcmp(root->str, str);
        if (cmp > 0) 
            root = root->l;
        else if (cmp < 0) 
            root = root->r;
        else 
            return root;
    }
    return root;  // root sera NULL se nao encontrar
}

bst* put(bst* root, char* str) {
    if(root) {
        int cmp = strcmp(root->str, str);
        if(cmp > 0)
            root->l = put(root->l,str);
        else if (cmp < 0)
            root->r = put(root->r,str);
        return root;
    } else {
        bst* novo = (bst*)malloc(sizeof(bst));
        novo->str = (char*)malloc(sizeof(char)*(strlen(str)+1));
        strcpy(novo->str,str);
        novo->l = novo->r = NULL;
        return novo;
    }
}

bst* max(bst* root) {
    while (root->r)
        root = root->r;
    return root;
}

bst* min(bst* root) {
    while (root->l)
        root = root->l;
    return root;
}

bst* rem(bst* root, char* str) {
    if (!root) return NULL;

    int cmp = strcmp(root->str, str);

    if (cmp > 0) 
        root->l = rem(root->l, str);

    else if (cmp < 0) 
        root->r = rem(root->r, str);

    else {
        // caso 1: folha
        if (!root->l && !root->r) {
            free(root->str);
            free(root);
            return NULL;
        }
        // caso 2: um filho
        else if (!root->l || !root->r) {
            bst *son;
            if (root->l) son = root->l;
            else son = root->r;

            free(root->str);
            free(root);
            return son;
        } 
        // caso 3: dois filhos
        else {
            bst *max_l = max(root->l);  // encontra o valor maximo na subarvore a esquerda

            free(root->str);  // libera o espaco da string original
            root->str = (char*)malloc(sizeof(char)*(strlen(max_l->str)+1));  // aloca espaco com o tamanho certo da nova string
            strcpy(root->str, max_l->str);  // copia a string na raiz

            root->l = rem(root->l, max_l->str);  // chama recursivamente para remover a string duplicada
            return root;
        }
    }
    return root;
}

void del(bst* root) {
    if(root) {
        del(root->l);
        del(root->r);
        free(root->str);
        free(root);
    }
}