
#include <stdio.h>

int main()
{


	int a[] =  {5, 9, 7, 6, 4, 0, 2, 3, 8, 1};
	int tamanho = 10;

	for (int i = 0; i < tamanho - 1; i++) {
		int min_pos = i;

		for (int j = i + 1; j < tamanho; j++)
			if (a[j] < a[min_pos]) min_pos = j;

		if (min_pos != i) {

			int temp = a[i];
			a[i] = a[min_pos];
			a[min_pos] = temp;

		}
	}

	for (int i = 0; i < tamanho; i++)
		printf("a[%d] = %d\n", i, a[i]);

}