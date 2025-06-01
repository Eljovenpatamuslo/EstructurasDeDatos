#include "Gbtree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define max(a,b) (((a) > (b)) ? (a) : (b))

#define min(a,b) (((a) < (b)) ? (a) : (b))
/*int pow(int x , int y){
  if(y == 0){
    return 1;
  }
  return x*pow(x,y-1);
}*/

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

//Ejercicio 3//
BTree btree_mirror(BTree raiz){
  //Si el nodo es NULL o es hoja retorna el mismo valor
  if(raiz == NULL || (raiz->right == NULL  && raiz->left == NULL))
    return raiz;
  
  //Si el nodo tiene hijos, entonces swapea derecho e izquierdo 
  // y hace el llamado recursivo a los lados derecho e izquierdo
  else{
    BTree aux = raiz->left;
    raiz->left = btree_mirror(raiz->right);
    raiz->right = btree_mirror(aux);
    return raiz;
  }
}

//Ejercicio 4//
int btree_altura(BTree arbol){
  if(arbol == NULL) return -1;
  return max(1+btree_altura(arbol->left),1+btree_altura(arbol->right));
}

int btree_nnodos_profundidad(BTree arbol, int profundidad){
  if(arbol == NULL) return 0;
  if(profundidad == 0) return 1;
  return btree_nnodos_profundidad(arbol->left,profundidad-1)+btree_nnodos_profundidad(arbol->right,profundidad-1);
}

int btree_hojacompleta(BTree raiz){
  if(raiz == NULL || (raiz->left != NULL && raiz->right == NULL)){
    return 1;
  }
  if(raiz->right != NULL && raiz->left == NULL)
    return 0;
  else{
    return btree_hojacompleta(raiz->left) && btree_hojacompleta(raiz->right);
  }

}

int btree_escompleto(BTree raiz){
  int nivel_ant = btree_altura(raiz)-1;
  int cond = btree_nnodos_profundidad(raiz, nivel_ant) == pow(2,nivel_ant);
  return cond && btree_hojacompleta(raiz);
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