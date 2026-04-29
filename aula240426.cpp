#include <stdio.h>
#include <stdlib.h>

int ma[9][9] = {
//    A B C D E F G H I
/*A*/{0,1,1,1,0,1,0,0,0},   
/*B*/{1,0,0,1,1,1,0,0,0},
/*C*/{1,0,0,1,0,0,0,0,0},
/*D*/{1,1,1,0,1,1,1,1,0},
/*E*/{0,1,0,1,0,1,1,1,0},
/*F*/{1,1,0,1,1,0,0,0,0},
/*G*/{0,0,0,1,1,0,0,0,0},
/*H*/{0,0,0,1,1,0,0,0,0},
/*I*/{0,0,0,0,0,0,0,0,0},
};

int diagonal_principal();   // Quantos loops tem na matriz
int numero_arestas();      // Quantas arestas tem na matriz
int maior_grau();         // Quandos ventecis chegam nela  
int menor_grau(); 

int main()
{
    printf("Loop(s) : %d", diagonal_principal());
    printf("\nAresta(s): %d", numero_arestas());
    printf("\nMaior Grau: %d", maior_grau());
    printf("\nMenor Grau: %d", menor_grau());
    return 0;
}

int diagonal_principal() {
    int loop = 0;
    for(int i=0; i<9; i++) {
        loop = loop + (ma[i][i]);
    }
    return loop;
}

int numero_arestas() {
    int arestas = 0;
    for(int i=0; i<9;i++) {
        for(int j=0; j<9;j++) {
            arestas += ma[i][j];
        }
    }
    return arestas/2;
}

int maior_grau(){
	int maior = 0;
	
	for(int i=0; i< 9;i++) {
		
		int n = 0;
		
        for(int j=0; j<9;j++) {
            n += ma[i][j];
        }
        
        if(n > maior) maior = n;
    }
    
    return maior;
}

int menor_grau(){
	int maior = 0;
	
	for(int i=0; i< 9;i++) {
		
		int n = 0;
		
        for(int j=0; j<nb             9;j++) {
            n += ma[i][j];
        }
        
        if(n < maior) maior = n;
    }
    
    return maior;
}



