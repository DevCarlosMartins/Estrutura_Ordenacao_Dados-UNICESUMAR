/******************************************************************************

    Criar uma Matrix M x N. M e N sC#o escolhidas pelo usuC!rio.

    Crie um algoritimo de ordenaC'C#o nC#o cresente e nC#o decresente
    e mostr e o tempo de excuC'C#o.

    Contrua a melhor C!vore de busca com os elementos da metriz.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// ============= Bubble Sort =================
void bobble_short (int a[], int tamanho) {
	for (int i = 0 ; i < tamanho; i++) {

		for (int j = 0; j < (tamanho -1); j++) {

			if (a[j] > a[j + 1]) {
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;

			}
		}
	}
}

// ================= CRVORE =================
typedef struct Node {
	int value;
	struct Node *left;
	struct Node *right;
} Node;

// cria nC3
Node* create_node(int value) {
	Node* n = (Node*) malloc(sizeof(Node));
	n->value = value;
	n->left = NULL;
	n->right = NULL;
	return n;
}

// cria C!rvore balanceada a partir de vetor ordenado
Node* build_balanced_tree(int v[], int start, int end) {
	if(start > end) return NULL;

	int mid = (start + end) / 2;

	Node* root = create_node(v[mid]);

	root->left = build_balanced_tree(v, start, mid - 1);
	root->right = build_balanced_tree(v, mid + 1, end);

	return root;
}


// percurso em ordem
void inorder(Node* root) {
	if(root) {
		inorder(root->left);
		printf("%d ", root->value);
		inorder(root->right);
	}
}

int main()
{

	int M, N;

	srand(time(NULL));

	printf("Qual o valor de M? \n M: ");
	scanf("%d", &M);

	printf("Qual o valor de M? \n N: ");
	scanf("%d", &N);

	printf("Definido Matrix %d x %d\n", M,N);

	int matrix[M][N];
	int v[M * N];

	// Prenche altomaticamente a matrix
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			matrix[i][j] = rand() % 51; // 0 atC) 20
		}
	}

	// Exibe matriz
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d|", matrix[i][j]);
		}
		printf("\n");
	}

	// Tranforma a matrix em vetor
	int k = 0;
	for(int i = 0; i < M; i++)
		for(int j = 0; j < N; j++)
			v[k++] = matrix[i][j];


	// medir tempo
	clock_t inicio = clock();

	// Ordena o Array
	bobble_short(v,M*N);

	clock_t fim = clock();

	double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

	// Volta para uma Matrix
	k=0;
	for(int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			matrix[i][j] = v[k++];

	// Printa o Matrix
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}

	// construir C!rvore balanceada
	Node* root = build_balanced_tree(v, 0, M * N - 1);

	printf("\nArvore (inorder):\n");
	inorder(root);

	// tempo
	printf("\n\nTempo de execucao: %f segundos\n", tempo);

}