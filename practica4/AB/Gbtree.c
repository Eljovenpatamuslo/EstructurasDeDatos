#include "btree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "GPilaList.h"
#include <math.h>


typedef struct _BTNodo {
  void* dato;
  struct _BTNodo *left;
  struct _BTNodo *right;
} BTNodo;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear() { return NULL; }

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo, FuncionDestructora destroy) {
  if (nodo != NULL) {
    destroy(nodo->dato);
    btree_destruir(nodo->left,destroy);
    btree_destruir(nodo->right,destroy);
    free(nodo);
  }
}

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo) { return nodo == NULL; }

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(void* dato, BTree left, BTree right, FuncionCopia copy) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = copy(dato);
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,FuncionVisitante visit) {
  if(arbol == NULL) return;
  switch (orden)
  {
  case BTREE_RECORRIDO_IN:
    btree_recorrer(arbol->left,orden,visit);
    btree_recorrer(arbol->right,orden,visit);
    visit(arbol->dato);
    break;

  case BTREE_RECORRIDO_PRE:
    visit(arbol->dato);
    btree_recorrer(arbol->left,orden,visit);
    btree_recorrer(arbol->right,orden,visit);
    break;
    
  case BTREE_RECORRIDO_POST:
    btree_recorrer(arbol->right,orden,visit);
    visit(arbol->dato);
    btree_recorrer(arbol->left,orden,visit);
    break;

  default:
    assert(0);
    break;
  }
}