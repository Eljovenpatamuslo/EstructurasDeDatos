#include "GPilaList.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Pila pila_crear(){
    return glist_crear();
}
/*
void destruir2(void* dato){
    free(dato);
}
*/
void pila_destruir(Pila pila,FuncionDestructora destroy){
    glist_destruir(pila, destroy);
}

int pila_es_vacia(Pila pila){
    return glist_vacia(pila);
}

void* pila_tope(Pila pila){
    void* dato = pila->data;
    return dato;
}
/*
void* copiar(void* dato){
    int* data = malloc(sizeof(int));
    *data = *(int*)dato;
    return (void*)data;
}
*/

Pila pila_apilar(Pila pila, void* dato, FuncionCopia copy ){
    return glist_agregar_inicio(pila,dato,copy);
}

void pila_desapilar(Pila pila, FuncionDestructora destroy){
    slist_eliminar_primero(pila,destroy);
}
/*
void visitar(void* dato){
    printf("%i\n",*((int*)dato));
}
*/
void pila_imprimir(Pila pila,FuncionVisitante visit){
    glist_recorrer(pila,visit);
}
