#include "PilaList.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

Pila pila_crear(){
    return glist_crear();
}

void destruir2(void* dato){
    free(dato);
}

void pila_destruir(Pila pila){
    glist_destruir(pila, destruir2);
    //free(pila);
}

int pila_es_vacia(Pila pila){
    return glist_vacia(pila);
}

int pila_tope(Pila pila){
    int* dato = (int*)pila->data;
    return *dato;
}

void* copiar(void* dato){
    int* data = malloc(sizeof(int));
    *data = *(int*)dato;
    return (void*)data;
}

Pila pila_apilar(Pila pila, int dato){
    return glist_agregar_inicio(pila,&dato,copiar);
}

void pila_desapilar(Pila pila){
    slist_eliminar_primero(pila,destruir2);
    //slist_eliminar(pila,0,destruir2);
}

void visitar(void* dato){
    printf("%i\n",*((int*)dato));
}

void pila_imprimir(Pila pila){
    glist_recorrer(pila,visitar);
}
