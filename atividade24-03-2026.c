/******************************************************************************
 * Cria uma Matriz M x N com valores ÚNICOS e aleatórios.
 * Ordena em ordem CRESCENTE e DECRESCENTE (Bubble Sort).
 * Exibe o tempo de execução de cada ordenação.
 * Constrói a melhor árvore de busca (BST balanceada) com os elementos.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ====================== FISHER-YATES SHUFFLE ======================
// Embaralha o array 'a' de tamanho 'n' in-place (sem repetição)
void fisher_yates_shuffle(int a[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j   = rand() % (i + 1);
        int tmp = a[i];
        a[i]    = a[j];
        a[j]    = tmp;
    }
}

// Preenche o array com valores únicos embaralhados dentro do intervalo [0, range)
// Retorna 0 em caso de erro (tamanho maior que o intervalo disponível)
int fill_unique(int dest[], int tamanho, int range) {
    if (tamanho > range) return 0;

    int pool[range];
    for (int i = 0; i < range; i++)
        pool[i] = i;

    fisher_yates_shuffle(pool, range);

    for (int i = 0; i < tamanho; i++)
        dest[i] = pool[i];

    return 1;
}

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
        if (!trocou) break;
    }
}

// ====================== BUBBLE SORT DECRESCENTE ======================
void bubble_sort_desc(int a[], int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < tamanho - 1 - i; j++) {
            if (a[j] < a[j + 1]) {
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

// Constrói BST balanceada a partir do vetor ordenado crescente
Node* build_balanced_tree(int v[], int start, int end) {
    if (start > end) return NULL;
    int mid     = (start + end) / 2;
    Node* root  = create_node(v[mid]);
    root->left  = build_balanced_tree(v, start, mid - 1);
    root->right = build_balanced_tree(v, mid + 1, end);
    return root;
}

// Calcula a altura da árvore
int height(Node* root) {
    if (!root) return 0;
    int le = height(root->left);
    int ri = height(root->right);
    return 1 + (le > ri ? le : ri);
}

// Percurso em ordem (exibe valores em ordem crescente)
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

// ====================== UTILITÁRIOS ======================
void print_matrix(int M, int N, int matrix[M][N]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            printf("%4d", matrix[i][j]);
        printf("\n");
    }
}

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

    printf("=== Matriz com Números Únicos, Ordenação e Árvore Balanceada ===\n\n");

    printf("Qual o valor de M (linhas)?  ");
    scanf("%d", &M);
    printf("Qual o valor de N (colunas)? ");
    scanf("%d", &N);

    if (M <= 0 || N <= 0) {
        printf("Erro: M e N devem ser positivos.\n");
        return 1;
    }

    int tamanho = M * N;

    // O intervalo de valores únicos disponíveis: [0, RANGE)
    // RANGE deve ser >= tamanho para garantir unicidade
    const int RANGE = tamanho < 100 ? 100 : tamanho;

    int v_orig[tamanho];
    int v_asc[tamanho];
    int v_desc[tamanho];
    int matrix[M][N];

    // ---- Gera valores únicos com Fisher-Yates ----
    if (!fill_unique(v_orig, tamanho, RANGE)) {
        printf("Erro: não há valores únicos suficientes para a matriz %dx%d.\n", M, N);
        return 1;
    }

    // Copia para os dois vetores de ordenação
    for (int i = 0; i < tamanho; i++) {
        v_asc[i]  = v_orig[i];
        v_desc[i] = v_orig[i];
    }

    // ---- Exibe matriz original ----
    vec_to_matrix(M, N, matrix, v_orig);
    printf("\nMatriz %d x %d (valores únicos, aleatórios):\n", M, N);
    print_matrix(M, N, matrix);

    // ---- Ordenação CRESCENTE ----
    clock_t ini = clock();
    bubble_sort_asc(v_asc, tamanho);
    clock_t fim = clock();
    double tempo_asc = (double)(fim - ini) / CLOCKS_PER_SEC;

    vec_to_matrix(M, N, matrix, v_asc);
    printf("\nOrdenação CRESCENTE:\n");
    print_matrix(M, N, matrix);
    printf("Tempo de execução (crescente):   %.6f segundos\n", tempo_asc);

    // ---- Ordenação DECRESCENTE ----
    ini = clock();
    bubble_sort_desc(v_desc, tamanho);
    fim = clock();
    double tempo_desc = (double)(fim - ini) / CLOCKS_PER_SEC;

    vec_to_matrix(M, N, matrix, v_desc);
    printf("\nOrdenação DECRESCENTE:\n");
    print_matrix(M, N, matrix);
    printf("Tempo de execução (decrescente): %.6f segundos\n", tempo_desc);

    // ---- Árvore Balanceada ----
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
