#include "sglist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

SGList sglist_crear(){
    return NULL;
}

void sglist_destruir(SGList list, FuncionDestructora destroy){
    while(list != NULL){
        SGList eliminar = list;
        list = list->next;
        destroy(eliminar->data);
        free(eliminar);       
    }
}

int sglist_vacia(SGList list){
    return list == NULL;
}

void sglist_recorrer(SGList list, FuncionVisitante visit){
    for(SGList aux = list; aux != NULL; aux = aux->next){
        visit(aux->data);
    }
}

SGList sglist_insertar(SGList list, void *data, FuncionCopia copy, FuncionComparadora compare){
    SGList newNodo = malloc(sizeof(GNode));
    assert(newNodo != NULL);

    newNodo->data = copy(data);
    newNodo->next = NULL;
    if(sglist_vacia(list)) return newNodo;

    SGList aux = list;

    if(compare(data,aux->data) <= 0){
        newNodo->next = list;
        return newNodo;
    }

    for(; aux->next != NULL && compare(data,aux->next->data) >= 0 ; aux = aux->next);
    SGList aux2 = aux->next;
    aux->next = newNodo;
    newNodo->next = aux2;
    return list;
}

int sglist_buscar(SGList list, void *data, FuncionComparadora compare){
    int encontrado = 0,noEsta = 0;
    for(SGList aux = list; aux != NULL && !encontrado && !noEsta; aux = aux->next){
        if(compare(aux->data,data) == 0){
            encontrado = 1;
        }else if(compare(aux->data,data) > 0){
            noEsta = 1;
        }
    }
    if(encontrado) return 1;
    return 0;
}

SGList sglist_arr(void **arr, int length, FuncionCopia copy, FuncionComparadora compare) {
    SGList list = sglist_crear();
    for (int i = 0; i < length; i++) {
        list = sglist_insertar(list, arr[i], copy, compare);
    }
    return list;
}