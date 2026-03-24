
#include <stdio.h>

void bobble_short (int a[], int tamanho){
    for (int i = 0 ; i < tamanho; i++){
        
        for (int j = 0;j < (tamanho -1); j++){
            
            if (a[j] > a[j + 1]){
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                
            }
        }
    }
}

int main()
{


	int a[] =  {5, 9, 7, 6, 4, 0, 2, 3, 8, 1};
	int tamanho = 10;

    bobble_short(a,tamanho);
    
    for (int i = 0; i < tamanho; i++)
		printf("a[%d] = %d\n", i, a[i]);
}