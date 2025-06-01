#ifndef __BTREE_H__
#define __BTREE_H__


typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparadora)(void *dato1,void *dato2);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

typedef struct _BTNodo *BTree;

typedef void (*FuncionVisitanteExtra) (void* dato, void *extra);

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo, FuncionDestructora destroy);

/**
 * Indica si el árbol es vacío.
 */
int btree_empty(BTree nodo);

/**
 * Crea un nuevo arbol, con el dato dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(void* dato, BTree left, BTree right, FuncionCopia copy);

//Ejercicio 3//
BTree btree_mirror(BTree raiz);

//Ejercicio 4//
int btree_altura(BTree arbol);
int btree_nnodos_profundidad(BTree arbol, int profundidad);

//chequea que en las hojas los nodos se encuentren de izq a derecha
int btree_hojacompleta(BTree raiz);

//Chequea si un arbol es completo
int btree_escompleto(BTree raiz);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,FuncionVisitante visit);
#endif /* __BTREE_H__ */
