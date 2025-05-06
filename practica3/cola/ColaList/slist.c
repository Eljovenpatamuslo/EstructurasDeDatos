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

void slist_destruir(SList list, FuncionDestructora destroy) {
    SNodo *nodeToDelete;
    while (list.primero != NULL) {
      nodeToDelete = list.primero;
      list.primero = list.primero->sig;
      destroy(nodeToDelete->dato);
      free(nodeToDelete);
    }
    //list.ultimo = NULL;
}

int slist_vacia(SList list){
    return list.primero == NULL;
}

SList slist_eliminar_ultimo(SList list,FuncionDestructora destroy){
    SNodo *nodeToDelete;
    nodeToDelete = list.ultimo;
    list.ultimo = list.ultimo->ant; 
    list.ultimo->sig = NULL;
    destroy(nodeToDelete->dato);
    free(nodeToDelete);
    return list;
}

void slist_imprimir(SList cola,FuncionVisitante visit){
    for(SNodo* aux = cola.primero; aux != NULL; aux = aux->sig){
        visit(aux->dato);
    }
}