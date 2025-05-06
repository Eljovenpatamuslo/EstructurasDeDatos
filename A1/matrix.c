#include <stdio.h>
#include <stdlib.h>

typedef int (*CalcularCosto)(int fila,int columna);

int calcular_costo(int fila, int columna){
    return (fila*2) + columna;
}

int** definir_M(int filas, int columnas, CalcularCosto calcular_costo){
    int** M = malloc(sizeof(int*)*filas);
    for(int i = 0;i < filas; i++){
        M[i] = malloc(sizeof(int)*columnas);
        for(int j = 0;j < columnas; j++){
            M[i][j] = calcular_costo(i,j);
        }
    }
    return M;
}

int costo_min_pasaje(int **M, int filaM, int columnaM){
    int** Maux = M;
    for(int i = 0;i < filaM; i++){
        for(int j = 0;j < columnaM; j++){
            if(i == 0 && j != 0){ 
                Maux[0][j] += Maux[0][j-1]; 
            }else if(i != 0 && j == 0){
                Maux[i][j] += Maux[i-1][j];
            }
            if(i != 0 && j != 0){
                Maux[i][j] = Maux[i][j-1] < Maux[i-1][j] ? Maux[i][j] + Maux[i][j-1] : Maux[i][j] + Maux[i-1][j];
            }
        }
    }
    return Maux[filaM-1][columnaM-1];
}

int main(){
    int filas = 1000;
    int columnas = 1000;
    int** M = definir_M(filas,columnas,(CalcularCosto) calcular_costo);
    /*for(int i = 0;i < filas; i++){
        for(int j = 0;j < columnas; j++){
            printf("%i ", M[i][j]);
        }
        printf("\n");
    }*/

    printf("%i\n",costo_min_pasaje(M,filas,columnas));
}