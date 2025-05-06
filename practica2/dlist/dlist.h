#ifndef __DLIST_H__
#define __DLIST_H__

#include <stdlib.h>

typedef struct _DNodo {
    int dato;
    struct _DNodo* sig;
    struct _DNodo* ant;
} DNodo;

typedef struct {
    DNodo* primero;
    DNodo* ultimo;
} DList;

typedef enum {
    DLIST_RECORRIDO_HACIA_ADELANTE,
    DLIST_RECORRIDO_HACIA_ATRAS
} DListOrdenDeRecorrido;

void dlist_recorrer(DList* list, DListOrdenDeRecorrido sentido);

#endif
