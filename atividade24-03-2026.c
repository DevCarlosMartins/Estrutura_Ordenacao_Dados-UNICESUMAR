/******************************************************************************
 * Cria uma Matriz M x N com valores aleatórios.
 * Ordena em ordem CRESCENTE e DECRESCENTE (Bubble Sort).
 * Exibe o tempo de execução de cada ordenação.
 * Constrói a melhor árvore de busca (BST balanceada) com os elementos.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ====================== BUBBLE SORT CRESCENTE ======================
void bubble_sort_asc(int a[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < tamanho - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j]     = a[j + 1];
                a[j + 1] = temp;
                trocou   = 1;
            }
        }
        if (!trocou) break; // early exit se já ordenado
    }
}

// ====================== BUBBLE SORT DECRESCENTE ======================
void bubble_sort_desc(int a[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < tamanho - 1 - i; j++) {
            if (a[j] < a[j + 1]) {   // inverte a comparação
                int temp = a[j];
                a[j]     = a[j + 1];
                a[j + 1] = temp;
                trocou   = 1;
            }
        }
        if (!trocou) break;
    }
}

// ====================== ÁRVORE BINÁRIA ======================
typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node* create_node(int value) {
    Node* n  = (Node*) malloc(sizeof(Node));
    n->value = value;
    n->left  = NULL;
    n->right = NULL;
    return n;
}

// Constrói BST balanceada a partir do vetor ordenado (crescente)
Node* build_balanced_tree(int v[], int start, int end) {
    if (start > end) return NULL;
    int mid       = (start + end) / 2;
    Node* root    = create_node(v[mid]);
    root->left    = build_balanced_tree(v, start, mid - 1);
    root->right   = build_balanced_tree(v, mid + 1, end);
    return root;
}

// Calcula a altura da árvore
int height(Node* root) {
    if (!root) return 0;
    int le = height(root->left);
    int ri = height(root->right);
    return 1 + (le > ri ? le : ri);
}

// Percurso em ordem (in-order): exibe os valores ordenados
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

// Libera a memória da árvore
void free_tree(Node* root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

// ====================== EXIBIÇÃO DA MATRIZ ======================
void print_matrix(int M, int N, int matrix[M][N]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            printf("%3d ", matrix[i][j]);
        printf("\n");
    }
}

// Copia vetor de volta para a matriz
void vec_to_matrix(int M, int N, int matrix[M][N], int v[]) {
    int k = 0;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = v[k++];
}

// ====================== MAIN ======================
int main() {
    int M, N;
    srand((unsigned int) time(NULL));

    printf("=== Matriz com Ordenação e Árvore Balanceada ===\n\n");

    printf("Qual o valor de M (linhas)? ");
    scanf("%d", &M);
    printf("Qual o valor de N (colunas)? ");
    scanf("%d", &N);

    if (M <= 0 || N <= 0) {
        printf("Erro: M e N devem ser positivos.\n");
        return 1;
    }

    int tamanho = M * N;
    int matrix[M][N];
    int v_asc[tamanho];
    int v_desc[tamanho];

    // ---- Preenche a matriz aleatoriamente ----
    printf("\nMatriz %d x %d gerada aleatoriamente:\n", M, N);
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = rand() % 51;   // valores de 0 a 50

    print_matrix(M, N, matrix);

    // ---- Converte para vetores ----
    int k = 0;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) {
            v_asc[k]  = matrix[i][j];
            v_desc[k] = matrix[i][j];
            k++;
        }

    // ---- Ordenação CRESCENTE ----
    clock_t ini = clock();
    bubble_sort_asc(v_asc, tamanho);
    clock_t fim = clock();
    double tempo_asc = (double)(fim - ini) / CLOCKS_PER_SEC;

    vec_to_matrix(M, N, matrix, v_asc);
    printf("\nOrdenação CRESCENTE (não decrescente):\n");
    print_matrix(M, N, matrix);
    printf("Tempo de execução (crescente): %.6f segundos\n", tempo_asc);

    // ---- Ordenação DECRESCENTE ----
    ini = clock();
    bubble_sort_desc(v_desc, tamanho);
    fim = clock();
    double tempo_desc = (double)(fim - ini) / CLOCKS_PER_SEC;

    vec_to_matrix(M, N, matrix, v_desc);
    printf("\nOrdenação DECRESCENTE (não crescente):\n");
    print_matrix(M, N, matrix);
    printf("Tempo de execução (decrescente): %.6f segundos\n", tempo_desc);

    // ---- Árvore Balanceada (usa vetor crescente) ----
    Node* root = build_balanced_tree(v_asc, 0, tamanho - 1);

    printf("\n=== Árvore BST Balanceada ===\n");
    printf("Percurso em ordem (in-order):\n");
    inorder(root);
    printf("\nAltura da árvore: %d\n", height(root));

    free_tree(root);

    printf("\n=== Resumo de Tempos ===\n");
    printf("Bubble Sort crescente:   %.6f s\n", tempo_asc);
    printf("Bubble Sort decrescente: %.6f s\n", tempo_desc);

    return 0;
}
