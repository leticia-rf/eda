// atividade 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float nota; // nota média
    float horas; // horas de estudo
    int resultado; // aprovado (1) ou reprovado (0)
    float distancia; // distancia euclidiana
} Aluno;

float Distancia (float q1, float q2, float p1, float p2);
void swap(Aluno *a, Aluno *b);

int main () {

    int n_amostras, n_alunos, k;

    scanf ("%d %d %d", &n_amostras, &n_alunos, &k);

    Aluno *amostra = malloc(n_amostras * sizeof(Aluno));
    
    for (int i = 0; i < n_amostras; i++) {
        scanf ("%f %f %d", &amostra[i].nota, &amostra[i].horas, &amostra[i].resultado);
    }

    for (int j = 0; j < n_alunos; j++) {

        float nota, horas;

        scanf ("%f %f", &nota, &horas);

        // calcula e atribui o campo da distancia de cada amostra
        for (int i = 0; i < n_amostras; i++) {
            amostra[i].distancia = Distancia(amostra[i].nota, amostra[i].horas, nota, horas);
        }

        // selection sort das k menores distancias
        for (int i = 0; i < k; i++) {
            int menor_indice = i; 

            for (int l = i; l < n_amostras; l++) {
                if (amostra[l].distancia < amostra[menor_indice].distancia)
                    menor_indice = l;
            }

            swap(&amostra[i], &amostra[menor_indice]);
        }

        // calcula a maior frequencia
        int freq_aprovado = 0, freq_reprovado = 0;

        for (int i = 0; i < k; i++) {
            if (amostra[i].resultado) freq_aprovado++;
            else freq_reprovado++;
        }

        if (freq_aprovado >= freq_reprovado)
            printf ("Aluno %d: (%.2f, %.2f) = Aprovado\n", j, nota, horas);
        else 
            printf ("Aluno %d: (%.2f, %.2f) = Reprovado\n", j, nota, horas);

    }

    free(amostra);

    return 0;
}

// 1: nota  /  2: horas
float Distancia (float q1, float q2, float p1, float p2) {
    return sqrt(pow((q1-p1), 2) + pow((q2-p2), 2));
}

void swap(Aluno *a, Aluno *b) {
    Aluno temp = *a;
    *a = *b;
    *b = temp;
}