#include "matriz.h"

/*
** Implmentacion utilizando un unico arreglo unidimensional
*/

struct Matriz_ {
  float* arreglo;
  size_t numFil;
  size_t numColum;
};


Matriz* matriz_crear(size_t numFilas, size_t numColumnas) {
  Matriz* matrix = malloc(sizeof(Matriz));
  matrix->numFil = numFilas;
  matrix->numColum = numColumnas;
  matrix->arreglo = malloc(sizeof(float)*numFilas*numColumnas);
  return matrix;
}

void matriz_destruir(Matriz* matriz) {
  free(matriz->arreglo);
  free(matriz);
}

double matriz_leer(Matriz* matriz, size_t fil, size_t col) {
 return matriz->arreglo[fil*matriz->numColum + col];
}

void matriz_escribir(Matriz* matriz, size_t fil, size_t col, double val) {
  matriz->arreglo[fil*matriz->numColum + col] = val;
}

size_t matriz_num_filas(Matriz* matriz) {
  return matriz->numFil;
}

size_t matriz_num_columnas(Matriz* matriz) {
  return matriz->numColum;
}
