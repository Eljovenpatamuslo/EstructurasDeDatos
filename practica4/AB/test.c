#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

static void imprimir_entero(void* data) {
  printf("%d ", *(int*)data);
}

int main() {
  BTree ll = btree_unir(1, btree_crear(), btree_crear());
  BTree l = btree_unir(2, ll, btree_crear());
  BTree r = btree_unir(3, btree_crear(), btree_crear());
  BTree raiz = btree_unir(4, l, r);

  BTree raiz2 = btree_copiar(raiz);
  puts("");
  //btree_recorrerPRE_iter(raiz, imprimir_entero);
  //printf("%i\n",btree_nnodos(raiz));//4
  printf("%i\n",btree_buscar(raiz,3));//1
  printf("%i\n",btree_buscar(raiz,5));//0
  /*btree_recorrer(raiz,BTREE_RECORRIDO_PRE,imprimir_entero);
  printf("altura:%i\n",btree_altura(raiz));
  printf("nodos a profundidad 2:%i\n",btree_nnodos_profundidad(raiz,0));
  printf("suma de todos los nodos :%i\n",btree_sumar(raiz));
  printf("profundidad :%i\n",btree_profundidad(raiz,3));
  printf("%i\n",btree_busqueda_por_extension(raiz,3));*/
  //btree_recorrer_pre_it(raiz,imprimir_entero);
  btree_destruir(raiz);
  btree_destruir(raiz2);

  return 0;
}
/*
  4
 2 3
1  */