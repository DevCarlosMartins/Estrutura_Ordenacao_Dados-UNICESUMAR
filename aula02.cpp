#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/* Protótipos das funções */
void imprimir(int A[], int n, int tempo);
void delay(int number_of_seconds);
int* criarArranjo(int n);
void troca(int *x, int *y);
void ordenar(int A[], int n);

int main (){
    clock_t t;
    int n = 10;

    // Cria o vetor
    int* A = criarArranjo(n);

    // Marca o tempo inicial
    t = clock();

    // Ordena o vetor
    ordenar(A, n);

    // Calcula o tempo gasto na ordenação
    t = clock() - t;

    // Imprime o tempo de execução em milissegundos
    printf("\nTempo de execucao da ordenacao: %lf ms\n",
           ((double)t / (CLOCKS_PER_SEC / 1000)));
	
	
	
    // Libera a memória
    free(A);

    return 0;
}

/* ---------- Funções auxiliares ---------- */

void imprimir(int A[], int n, int tempo){
    for(int k = 0; k < n; k++){
        printf("%d ", A[k]);
    }
    delay(tempo);
    printf("\n");
}

void delay(int number_of_seconds){
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while(clock() < start_time + milli_seconds);
}

int* criarArranjo(int n){
    int* arranjo = (int*)malloc(n * sizeof(int));

    if(arranjo == NULL){
        printf("Problema na alocacao de memoria!\n");
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < n; i++){
        arranjo[i] = rand() % (n * 2);
    }

    return arranjo;
}

void troca(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
}

/*
  Ordenação por Insertion Sort
*/
void ordenar(int A[], int n){
	imprimir(A,n,1);
    int i, j, chave;

    for (j = 1; j < n; j++){
        chave = A[j];
        i = j - 1;

        while (i >= 0 && A[i] > chave){

            i--;
        }
        A[i + 1] = chave;
        imprimir(A,n,1);
    }
    	
}

