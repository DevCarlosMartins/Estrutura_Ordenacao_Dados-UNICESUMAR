#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Troca dois valores via ponteiro
void swap(int *x, int *y);

// Funções principais do algoritmo
void quicksort(int array[], int length);
void quicksort_recursion(int array[], int low, int high);
int partition(int array[], int low, int high);

int main()
{
    int a[] = {10,11,23,44,8,15,3,9,12,45,56,45,45};
    int length = 13;

    // Ordena o array
    quicksort(a, length);

    // Imprime o resultado
    for (int i = 0; i < length; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}

// Troca os valores apontados por x e y
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Inicializa o algoritmo
void quicksort(int array[], int length)
{
    // Inicializa gerador de números aleatórios (usado no pivot)
    srand(time(NULL));

    quicksort_recursion(array, 0, length - 1);
}

// Divide recursivamente o array
void quicksort_recursion(int array[], int low, int high)
{
    // Condição de parada: subarray com 0 ou 1 elemento
    if (low < high)
    {
        // Particiona o array e pega posição final do pivot
        int pivot_index = partition(array, low, high);

        // Ordena lado esquerdo do pivot
        quicksort_recursion(array, low, pivot_index - 1);

        // Ordena lado direito do pivot
        quicksort_recursion(array, pivot_index + 1, high);
    }
}

// Particiona o array em torno de um pivot
int partition(int array[], int low, int high)
{
    // Escolhe pivot aleatório dentro do intervalo
    int pivot_index = low + (rand() % (high - low));

    // Move o pivot para o final (posição padrão)
    if (pivot_index != high)
        swap(&array[pivot_index], &array[high]); // <-- remover ']' extra aqui

    // Define valor do pivot
    int pivot_value = array[high];

    // i marca a posição onde menores que o pivot serão colocados
    int i = low;

    // Percorre o array reorganizando os elementos
    for (int j = low; j < high; j++)
    {
        // Se elemento atual <= pivot, traz para a esquerda
        if (array[j] <= pivot_value)
        {
            swap(&array[i], &array[j]);
            i++;
        }
    }

    // Coloca o pivot na posição correta
    swap(&array[i], &array[high]);

    // Retorna posição final do pivot
    return i;
}