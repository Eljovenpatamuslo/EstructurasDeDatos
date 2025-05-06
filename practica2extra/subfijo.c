#include <stdio.h>
#include <stdlib.h>

typedef struct _DNodo {
    char dato;
    struct _DNodo* sig;
    struct _DNodo* ant;
} DNodo;

typedef struct {
    DNodo* primero;
    DNodo* ultimo;
} DList;

DList slist_crear() {
    DList lista;
    lista.primero = NULL;
    lista.ultimo = NULL;
    return lista;
}

DList slist_agregar_inicio(DList list, int dato) {
    DNodo *newNode = malloc(sizeof(DNodo));
    assert(newNode != NULL);
    newNode->dato = dato;
    if(list.primero == NULL){
        list.primero = newNode;
        list.ultimo = newNode;
        newNode->sig = NULL;
    }else{
        newNode->sig = list.primero;
        list.primero->ant = newNode;
        list.primero = newNode;
    }

    return list;
}

DList slist_agregar_final(DList list, int dato) {
    DNodo *newNode = malloc(sizeof(DNodo));
    assert(newNode != NULL);
    newNode->dato = dato;
    newNode->sig = NULL;
    if(list.ultimo == NULL){
        list.ultimo = newNode;
    }else{
        list.ultimo->sig = newNode;
    }

    return list;
}

DList encontrar_subfijo(DList lista1,DList lista2){
    DNodo* temp1 = lista1.ultimo;
    DNodo* temp2 = lista2.ultimo;
    DList retorno = slist_crear(); 
    int bandera = 0;
    for(;temp1!= NULL && temp2 != NULL && !bandera; temp1 = temp1->ant,temp2 = temp2->ant){
        if(temp1->dato == temp2->dato){
            retorno = slist_agregar_inicio(retorno,temp1->dato);
        }else{
            bandera = 1;
        }
    }   
    return retorno;
}
