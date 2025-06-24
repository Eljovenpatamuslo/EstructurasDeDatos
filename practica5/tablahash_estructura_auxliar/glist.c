#include "glist.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Devuelve una lista vacía.
 */
GList glist_crear() { return NULL; }

/**
 * Destruccion de la lista.
 * destroy es una función que libera el dato almacenado.
 */
void glist_destruir(GList list, FuncionDestructora destroy) {
  GNode *nodeToDelete;
  while (list != NULL) {
    nodeToDelete = list;
    list = list->next;
    destroy(nodeToDelete->data);
    free(nodeToDelete);
  }
}

/**
 * Determina si la lista es vacía.
 */
int glist_vacia(GList list) { return (list == NULL); }

/**
 * Agrega un elemento al inicio de la lista.
 * copy es una función que retorna una copia física del dato.
 */
GList glist_agregar_inicio(GList list, void *data, FuncionCopia copy) {
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = list;
  newNode->data = copy(data);
  return newNode;
}

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void glist_recorrer(GList list, FuncionVisitante visit) {
  for (GNode *node = list; node != NULL; node = node->next)
    visit(node->data);
}

int slist_longitud(GList list){
  if(list == NULL) return 0;
  int longitud = 0;
  for (GNode *node = list; node != NULL; node = node->next,longitud++);
  return longitud;
}

GList slist_concatenar(GList list1,GList list2){
  if(list1 == NULL) return list2;
  if(list2 == NULL) return list1;

  GList aux = list1;
  for (; aux->next != NULL; aux = aux->next);
  aux->next = list2;
  return list1;
}

GList slist_insertar(GList list,int pos,void* data,FuncionCopia copy){
  GNode *newNode = malloc(sizeof(GNode));
  assert(newNode != NULL);
  newNode->next = NULL;
  newNode->data = copy(data);
  if(list == NULL) return newNode;
  GList aux = list;
  for (int i=0; i<pos-1 && aux->next != NULL; aux = aux->next,i++);
  GList aux2 = aux->next;
  aux->next = newNode;
  newNode->next = aux2;
  return list;
}

void slist_eliminar(GList list,int pos,FuncionDestructora destroy){
  GList aux = list;
  for (int i=0; i<pos-1; aux = aux->next,i++);
  GList aux1 = aux->next;
  destroy(aux1->data);
  aux->next = aux1->next;
  free(aux1);
}

GList slist_contiene(GList list, void* data, FuncionComparadora compare){
  GList aux = list;
  for (; aux != NULL && compare(aux->data,data); aux = aux->next);
  return aux;
}

int slist_indice(GList list, void* data, FuncionComparadora compare){
  GList aux = list;
  if(aux == NULL) return -1;
  int i=0;
  for (; aux != NULL && compare(aux->data,data); aux = aux->next,i++);
  if(aux != NULL) return i;
  return -1;
}

GList slist_intersecar_custom(GList list1,GList list2,FuncionComparadora compare,FuncionCopia copy){
  if(list1 == NULL || list2 == NULL) return NULL;
  GList Devolver = glist_crear();
  for (GList aux1 = list1; aux1 != NULL; aux1 = aux1->next){
    int terminar = 0;
    for (GList aux2 = list2; aux2 != NULL && !terminar; aux2 = aux2->next){
      if(compare(aux1->data,aux2->data) == 0){
        Devolver = glist_agregar_inicio(Devolver,aux1->data,copy);
        terminar = 1;
      }
    }
  }
  return Devolver;
}

void slist_ordenar(GList list,FuncionComparadora compare,FuncionCopia copy){
  if(list == NULL) return ;
  int activado = 0;
  while (!activado){
    activado = 1;
    for (GList aux = list; aux->next != NULL; aux = aux->next){
      if(compare(aux->data,aux->next->data) > 0){
        activado = 0;
        void* basura = copy(aux->data);
        aux->data = copy(aux->next->data);
        aux->next->data = copy(basura);
      }
    }
  }
  //return list;
}

GList slist_reverso(GList list,FuncionCopia copy){
  if(list == NULL) return NULL;
  GList Devolver = glist_crear();
  for (GList aux = list; aux != NULL; aux = aux->next){
    Devolver = glist_agregar_inicio(Devolver,aux->data,copy);
  }
  return Devolver;
}

GList slist_intercalar(GList list1,GList list2,FuncionCopia copy){
  if(list1 == NULL) return list2;
  if(list2 == NULL) return list1;
  GList Devolver = glist_crear();
  GList aux1 = list1;
  GList aux2 = list2;
  for (int i = 0; aux2 != NULL && aux1 != NULL;i++){
    if(i%2 == 0){
      Devolver = slist_insertar(Devolver,i,aux1->data,copy);
      aux1 = aux1->next;
    }else{
      Devolver = slist_insertar(Devolver,i,aux2->data,copy);
      aux2 = aux2->next;
    }
  }
  if(aux2 == NULL) return slist_concatenar(Devolver,aux1);
  return slist_concatenar(Devolver,aux2);
}

GList slist_partir(GList list){
  if(list == NULL) return NULL;
  GList aux = list;
  int longitud = slist_longitud(list);
  int medio = longitud % 2 == 0 ? longitud / 2 : (longitud / 2) + 1;  
  for (int i = 0; i<medio-1; aux = aux->next,i++);
  GList list2 = aux->next;
  aux->next = NULL;
  return list2;
}

GList slist_partir_opt(GList list){
  if(list == NULL) return NULL;
  GList aux = list;
  GList list2 = list;
  GList list3;
  for (int i = 0; aux != NULL; aux = aux->next,i++){
    if(i % 2 == 0){
      list3 = list2;
      list2 = list2->next;
    }
  }
  
  list3->next = NULL;
  return list2;
}

GList glist_filtrar(GList lista, FuncionCopia c, Predicado p){
  GList retornar = glist_crear();
  for(GList aux = lista;aux != NULL; aux = aux->next){
    if(p(aux->data)){
      retornar = glist_agregar_inicio(retornar,aux->data,c);
    }
  }
  return slist_reverso(retornar,c);
}

//La función toma una lista y devuelve una lista simbolica(sin crear copias del dato) que cumplan el predicado
GList glist_newfilter(GList lista, Predicado p){
  if(lista == NULL) return NULL;
  if(p(lista->data)){
    GList nodo  = malloc(sizeof(GNode));
    nodo->data = lista->data;
    nodo->next = glist_newfilter(lista->next,p);
    return nodo;
  }
  return glist_newfilter(lista->next,p);
}

//La función toma una lista y devuelve una lista simbolica(sin crear copias del dato) que cumplan el predicado
GList glist_buscar_y_eliminar_dato(GList lista, void* dato, FuncionComparadora comp, FuncionDestructora destroy){
  if(lista == NULL) return NULL;
  if(comp(lista->data,dato) == 0){
    GList aux = lista->next;
    destroy(lista->data);
    free(lista);
    return glist_buscar_y_eliminar_dato(aux,dato,comp,destroy);
  }
  lista->next = glist_buscar_y_eliminar_dato(lista->next,dato,comp,destroy);
  return lista;
}