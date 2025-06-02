#include <stdio.h>
#include <stdlib.h>
#include "Gbtree.h"
#include "bstree.h"

static void imprimir_entero(void* data) {
  printf("%d ", *(int*)data);
}

static void *copiar_int(void* dato){
  int *copia = malloc(sizeof(int));
  *copia = *((int *) dato);
  return copia; 
}

static void destruir_int(void* dato){
  free(dato);
}

int main() {
  int a = 1;
  BTree ll = btree_unir(&a, btree_crear(), btree_crear(),copiar_int);
  a = 2;
  BTree l = btree_unir(&a, ll, btree_crear(),copiar_int);
  a = 3;
  BTree r = btree_unir(&a, btree_crear(), btree_crear(),copiar_int);
  a = 4;
  BTree raiz = btree_unir(&a, l, r,copiar_int);

  btree_recorrer(raiz,BTREE_RECORRIDO_POST,imprimir_entero);
    printf("\narbol completo: %i \n",btree_escompleto(raiz));
  raiz = btree_mirror(raiz);
  printf("\narbol completo: %i \n",btree_escompleto(raiz));
  btree_recorrer(raiz,BTREE_RECORRIDO_POST,imprimir_entero);
  puts("");
  btree_destruir(raiz,destruir_int);

  return 0;
}
/*
  4
 2 3
1  */