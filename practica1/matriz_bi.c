#include "matriz.h"

/*
** Implementacion utilizando un arreglo bidimensional (arreglo de punteros a arreglo)
*/



Matriz* matriz_crear(size_t numFilas, size_t numColumnas) {
  Matriz* matriz = malloc(sizeof(Matriz));
  matriz->filCol = malloc(sizeof(float*)*numFilas);
  for(int i=0;i<numColumnas;i++){
    matriz->filCol[i] = malloc(sizeof(float)*numColumnas);
  }
  matriz->numColumnas = numColumnas;
  matriz->numFilas = numFilas;
  return matriz;
}

void matriz_destruir(Matriz* matriz) {
  for(int i=0;i<matriz->numColumnas;i++){
    free(matriz->filCol[i]);
  }
  free(matriz->filCol);
  free(matriz);
}

double matriz_leer(Matriz* matriz, size_t fil, size_t col) {
  return matriz->filCol[fil][col];
}

void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val) {
  matriz->filCol[fil][col] = val;
}

size_t matriz_num_filas(Matriz* matriz) {
  return matriz->numFilas;
}

size_t matriz_num_columnas(Matriz* matriz) {
  return matriz->numColumnas;
}

Matriz* matriz_intercambiar_filas(Matriz* matriz, size_t fila1,size_t fila2){
  Matriz* matri = matriz_crear(matriz->numFilas,matriz->numColumnas);
  for(int i=0;i<matriz->numFilas;i++){
    float aux = matriz->filCol[fila1][i];
    matriz_escribir(matri,fila1,i,matriz->filCol[fila2][i]);
    matriz_escribir(matri,fila2,i,aux);
  }
  return matri;
}

Matriz* matriz_insertar_fila(Matriz* matriz, size_t pos){
  Matriz* matrix = realloc(matriz,sizeof(Matriz)*(matriz->numFilas+1)*matriz->numColumnas);
  for(int j = 0;j<matrix->numColumnas;j++){
    matrix->filCol[matrix->numFilas-1][j] = 0;
  }
  /*for(int i = matrix->numFilas-1;i>pos;i--){
    matrix = matriz_intercambiar_filas(matrix,i,i-1);
  }*/
  //matriz_destruir(matriz);
  return matrix;
}


