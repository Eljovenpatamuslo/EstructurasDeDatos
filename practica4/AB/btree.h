#ifndef __BTREE_H__
#define __BTREE_H__

#include "glist.h"

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef struct _BTNodo *BTree;

typedef void (*FuncionVisitanteExtra) (int dato, void *extra);

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int dato, BTree left, BTree right);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,FuncionVisitante visit);

void btree_recorrer_pre_it(BTree arbol,FuncionVisitante visit);

int btree_nnodos(BTree arbol);

int btree_buscar(BTree arbol, int dato);

BTree btree_copiar(BTree arbol);

int btree_altura(BTree arbol);

int btree_nnodos_profundidad(BTree arbol, int profundidad);

int btree_profundidad_aux(BTree arbol, int dato, int recursion);

int btree_profundidad(BTree arbol, int dato);

int btree_sumar(BTree arbol);

void btree_recorrer_extra(BTree arbol, BTreeOrdenDeRecorrido orden,FuncionVisitanteExtra visit, void *extra);

void btree_recorrer_bfs(BTree arbol, FuncionVisitante visit);
#endif /* __BTREE_H__ */
