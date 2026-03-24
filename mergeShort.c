#include <stdio.h>

// Funções principais do algoritmo
void merge_sort(int a[], int length);
void merge_sort_recursion(int a[], int l, int r);
void merge_sorted_arrays(int a[], int l, int m, int r);

int main()
{
    int array[] = {9, 4, 8, 1, 7, 0, 3, 2, 5, 6};
    int length = 10;

    // Chamada inicial do merge sort
    merge_sort(array, length);

    // Impressão do array ordenado
    for (int i = 0; i < length; i++)
        printf("%d ", array[i]);
    printf("\n");

    return 0;
}

// Função de entrada: apenas inicia a recursão
void merge_sort(int a[], int length)
{
    merge_sort_recursion(a, 0, length - 1);
}

// Divide o array recursivamente
void merge_sort_recursion(int a[], int l, int r)
{
    // Condição de parada: quando há 1 elemento
    if (l < r)
    {
        // Calcula o meio evitando overflow
        int m = l + (r - l) / 2;

        // Divide metade esquerda
        merge_sort_recursion(a, l, m);

        // Divide metade direita
        merge_sort_recursion(a, m + 1, r);

        // Junta (merge) as duas metades ordenadas
        merge_sorted_arrays(a, l, m, r);
    }
}

// Faz o merge de dois subarrays já ordenados
void merge_sorted_arrays(int a[], int l, int m, int r)
{
    // Tamanhos dos subarrays
    int left_length = m - l + 1;
    int right_length = r - m;

    // Arrays temporários
    int temp_left[left_length];
    int temp_right[right_length];

    int i, j, k;

    // Copia dados para o array da esquerda
    for (i = 0; i < left_length; i++)
        temp_left[i] = a[l + i];

    // Copia dados para o array da direita
    for (j = 0; j < right_length; j++)
        temp_right[j] = a[m + 1 + j];

    // Inicializa índices:
    // i -> esquerda
    // j -> direita
    // k -> posição original no array
    i = 0;
    j = 0;
    k = l;

    // Intercala os elementos ordenadamente
    while (i < left_length && j < right_length)
    {
        if (temp_left[i] <= temp_right[j])
        {
            a[k] = temp_left[i];
            i++;
        }
        else
        {
            a[k] = temp_right[j];
            j++;
        }
        k++;
    }

    // Copia elementos restantes da esquerda (se houver)
    while (i < left_length)
    {
        a[k] = temp_left[i];
        i++;
        k++;
    }

    // Copia elementos restantes da direita (se houver)
    while (j < right_length)
    {
        a[k] = temp_right[j];
        j++;
        k++;
    }
}