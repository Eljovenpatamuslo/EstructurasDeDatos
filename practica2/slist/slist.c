#include "slist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

SList slist_crear() {
    SList lista;
    lista.primero = NULL;
    lista.ultimo = NULL;
    return lista;
}

SList slist_agregar_inicio(SList list, void* dato, FuncionCopia copy) {
    SNodo *newNode = malloc(sizeof(SNodo));
    assert(newNode != NULL);
    newNode->dato = copy(dato);
    newNode->sig = NULL;
    if(list.primero == NULL){
        list.primero = newNode;
        list.ultimo = newNode;
        return list;
    }
    newNode->sig = list.primero;
    list.primero = newNode;

    return list;
}

SList slist_agregar_final(SList list, void* dato,FuncionCopia copy) {
    SNodo *newNode = malloc(sizeof(SNodo));
    assert(newNode != NULL);
    newNode->dato = copy(dato);
    newNode->sig = NULL;
    if(list.ultimo == NULL){
        list.primero = newNode;
        list.ultimo = newNode;
        return list;
    }
    list.ultimo->sig = newNode;
    list.ultimo = newNode;

    return list;
}