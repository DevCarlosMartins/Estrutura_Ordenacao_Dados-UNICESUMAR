#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó
typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

// Cria um novo nó
Node* create_node(int value) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Insere um valor na árvore
Node* insert(Node* root, int value) {
    // Se a árvore está vazia, cria o nó
    if (root == NULL)
        return create_node(value);

    // Vai para esquerda se menor
    if (value < root->value)
        root->left = insert(root->left, value);
    else
        // Vai para direita se maior ou igual
        root->right = insert(root->right, value);

    return root;
}

// Busca um valor na árvore
Node* search(Node* root, int value) {
    // Caso base: não encontrou ou encontrou
    if (root == NULL || root->value == value)
        return root;

    // Busca na esquerda
    if (value < root->value)
        return search(root->left, value);

    // Busca na direita
    return search(root->right, value);
}

// Percurso em ordem (imprime ordenado)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;

    // Inserção
    int valores[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, valores[i]);

    // Impressão ordenada
    inorder(root);
    printf("\n");

    // Busca
    int chave = 7;
    Node* resultado = search(root, chave);

    if (resultado != NULL)
        printf("Valor %d encontrado\n", chave);
    else
        printf("Valor %d nao encontrado\n", chave);

    return 0;
}