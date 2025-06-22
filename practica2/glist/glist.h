#ifndef __GLIST_H__
#define __GLIST_H__

typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);
typedef int (*FuncionComparadora)(void *dato1,void *dato2);

typedef int (*Predicado) (void *dato);

typedef struct _GNode {
  void *data;
  struct _GNode *next;
} GNode;

typedef GNode* GList;

/**
 * Devuelve una lista vacía.
 */
GList glist_crear();

/**
 * Destruccion de la lista.
 */
void glist_destruir(GList lista, FuncionDestructora destruir);

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
GList glist_agregar_inicio(GList lista, void *dato, FuncionCopia copiar);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList lista, FuncionVisitante visitar);

int slist_longitud(GList list);

GList slist_concatenar(GList list1,GList list2);

GList slist_insertar(GList list,int pos,void* data,FuncionCopia copy);

void slist_eliminar(GList list,int pos,FuncionDestructora destroy);

int slist_contiene(GList list, void* data, FuncionComparadora compare);

int slist_indice(GList list, void* data, FuncionComparadora compare);

GList slist_intersecar_custom(GList list1,GList list2,FuncionComparadora compare,FuncionCopia copy);

GList slist_intercalar(GList list1,GList list2,FuncionCopia copy);

void slist_ordenar(GList list,FuncionComparadora compare,FuncionCopia copy);

GList slist_reverso(GList list,FuncionCopia copy);

GList slist_partir(GList list);

GList slist_partir_opt(GList list);

GList glist_filtrar(GList lista, FuncionCopia c, Predicado p);

GList glist_newfilter(GList lista, Predicado p);
#endif /* __GLIST_H__ */
