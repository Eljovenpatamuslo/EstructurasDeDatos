#include "btree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "GPilaList.h"
#include <math.h>


typedef struct _BTNodo {
  int dato;
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
void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
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
BTree btree_unir(int dato, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->dato = dato;
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
    visit(&arbol->dato);
    break;

  case BTREE_RECORRIDO_PRE:
    visit(&arbol->dato);
    btree_recorrer(arbol->left,orden,visit);
    btree_recorrer(arbol->right,orden,visit);
    break;
    
  case BTREE_RECORRIDO_POST:
    btree_recorrer(arbol->right,orden,visit);
    visit(&arbol->dato);
    btree_recorrer(arbol->left,orden,visit);
    break;

  default:
    assert(0);
    break;
  }
}

void* copiar_arbol(void* dato){
  return dato;
}

void* no_copia (void* dato){
  return dato;
}

void no_destruir (void* dato){
  return;
}

/*
void btree_recorrer_pre_it(BTree arbol, FuncionVisitante visit) {
  if (btree_empty(arbol))
    return;

  Pila pila_de_nodos = pila_crear();

  pila_de_nodos = pila_apilar(pila_de_nodos, arbol, no_copia);

  while(!pila_es_vacia(pila_de_nodos)) {
    BTree nodo_actual = pila_tope(pila_de_nodos);
    visit(&nodo_actual->dato);

    pila_desapilar(pila_de_nodos, no_destruir);

    if (!btree_empty(nodo_actual->right)){
      pila_de_nodos = pila_apilar(pila_de_nodos, nodo_actual->right, no_copia);
      printf("jaffre");
    }
    if (!btree_empty(nodo_actual->left)){
      pila_de_nodos = pila_apilar(pila_de_nodos, nodo_actual->left, no_copia);
      printf("apta");
    }
  }
  pila_destruir(pila_de_nodos, no_destruir);  
}*/


#define max(a,b) (((a) > (b)) ? (a) : (b))

#define min(a,b) (((a) < (b)) ? (a) : (b))

int btree_nnodos(BTree arbol){
  if(arbol == NULL) return 0;
  return 1+btree_nnodos(arbol->right)+btree_nnodos(arbol->left);
}
int btree_buscar(BTree arbol, int dato){
  if(arbol == NULL) return 0;
  if(arbol->dato == dato) return 1;
  return btree_buscar(arbol->left,dato) || btree_buscar(arbol->right,dato);
}

BTree btree_copiar(BTree arbol){
  if(arbol == NULL) return NULL;
  BTree nuevoArbol = malloc(sizeof(BTNodo));
  nuevoArbol->dato = arbol->dato;
  nuevoArbol->left = btree_copiar(arbol->left);
  nuevoArbol->right = btree_copiar(arbol->right);
  return nuevoArbol;
}

int btree_altura(BTree arbol){
  if(arbol == NULL) return -1;
  return max(1+btree_altura(arbol->left),1+btree_altura(arbol->right));
}

int btree_nnodos_profundidad(BTree arbol, int profundidad){
  if(arbol == NULL) return 0;
  if(profundidad == 0) return 1;
  return btree_nnodos_profundidad(arbol->left,profundidad-1)+btree_nnodos_profundidad(arbol->right,profundidad-1);
}

int btree_profundidad_aux(BTree arbol, int dato,int recursion){
  if(arbol == NULL) return -1;
  if(arbol->dato == dato) return recursion;
  return max(btree_profundidad_aux(arbol->left,dato,recursion+1), btree_profundidad_aux(arbol->right,dato,recursion+1));
}
//intentar fusionar estas dos funciones
int btree_profundidad(BTree arbol, int dato){
  return btree_profundidad_aux(arbol,dato,0);
}

int btree_sumar(BTree arbol){
  if(arbol == NULL) return 0;
  return arbol->dato+btree_sumar(arbol->left)+btree_sumar(arbol->right);
}


//4
void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden,FuncionVisitanteExtra visit, void *extra){
  if(arbol == NULL) return;
  switch (orden)
  {
  case BTREE_RECORRIDO_IN:
    btree_recorrer_extra(arbol->left,orden,visit,extra);
    btree_recorrer_extra(arbol->right,orden,visit,extra);
    visit(arbol->dato,extra);
    break;

  case BTREE_RECORRIDO_PRE:
    visit(arbol->dato,extra);
    btree_recorrer_extra(arbol->left,orden,visit,extra);
    btree_recorrer_extra(arbol->right,orden,visit,extra);
    break;
    
  case BTREE_RECORRIDO_POST:
    btree_recorrer_extra(arbol->right,orden,visit,extra);
    visit(arbol->dato,extra);
    btree_recorrer_extra(arbol->left,orden,visit,extra);
    break;
    
  default:
    assert(0);
    break;
  }
}
//Piense cu´ales de las funciones del ejercicio anterior se podr´ıan definir de manera compacta llamando
//a btree recorrer extra con un orden, una funci´on visitante y un dato extra apropiados
/*
void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit){
  if(arbol == NULL) return;
  visit(&arbol->dato);
  return btree_busqueda_por_extension(arbol->left,visit);
  return btree_busqueda_por_extension(arbol->right,visit);
}*/