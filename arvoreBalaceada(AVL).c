#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó com altura
typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

// Retorna altura
int height(Node *n) {
    return (n == NULL) ? 0 : n->height;
}

// Máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Cria novo nó
Node* create_node(int value) {
    Node* n = (Node*) malloc(sizeof(Node));
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}

// Rotação à direita
Node* right_rotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    // Atualiza alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotação à esquerda
Node* left_rotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    // Atualiza alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Fator de balanceamento
int get_balance(Node *n) {
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

// Inserção com balanceamento
Node* insert(Node* node, int value) {
    // Inserção normal BST
    if (node == NULL)
        return create_node(value);

    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    else
        return node; // não permite duplicados

    // Atualiza altura
    node->height = 1 + max(height(node->left), height(node->right));

    // Calcula balanceamento
    int balance = get_balance(node);

    // Casos de rotação:

    // LL (esquerda-esquerda)
    if (balance > 1 && value < node->left->value)
        return right_rotate(node);

    // RR (direita-direita)
    if (balance < -1 && value > node->right->value)
        return left_rotate(node);

    // LR (esquerda-direita)
    if (balance > 1 && value > node->left->value) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // RL (direita-esquerda)
    if (balance < -1 && value < node->right->value) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

// Busca (mesma lógica da BST)
Node* search(Node* root, int value) {
    if (root == NULL || root->value == value)
        return root;

    if (value < root->value)
        return search(root->left, value);

    return search(root->right, value);
}

// Percurso em ordem
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;

    int valores[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, valores[i]);

    inorder(root);
    printf("\n");

    int chave = 25;
    Node* res = search(root, chave);

    if (res)
        printf("Encontrado: %d\n", chave);
    else
        printf("Nao encontrado\n");

    return 0;
}