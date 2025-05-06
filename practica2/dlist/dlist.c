#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

void dlist_recorrer(DList* list, DListOrdenDeRecorrido sentido){
    DNodo* aux = sentido ? list->ultimo : list->primero; 
    for(;aux != NULL; aux = sentido ? aux->ant : aux->sig){
        printf("%i",aux->dato);
    }
    /*
    if(sentido){
        for(;aux != NULL; aux = aux->ant){
            printf("%i",aux->dato);
        }
    }
    else{
        for(; aux != NULL; aux = aux->sig){
            printf("%i",aux->dato);
        }    
    }
    */
}