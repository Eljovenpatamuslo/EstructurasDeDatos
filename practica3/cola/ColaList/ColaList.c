#include "ColaList.h"
#include <stdio.h>
#include <stdlib.h>
void* copiar(void* dato){
    int* data = malloc(sizeof(int));
    *data = *(int*)dato;
    return (void*)data;
}

void destruir2(void* dato){
    free(dato);
}

void visitar(void* dato){
    printf("%i\n",*((int*)dato));
}

ColaList cola_crear(){
    return slist_crear();
}

void cola_destruir(ColaList cola, FuncionDestructora destroy){
    slist_destruir(cola,destroy);
}

int cola_es_vacia(ColaList cola){
    return slist_vacia(cola);
}

void* cola_inicio(ColaList cola){
    return cola.primero->dato;
}

ColaList cola_encolar(ColaList cola,void* dato, FuncionCopia copy){
    return slist_agregar_inicio(cola,dato,copy);
}

ColaList cola_desencolar(ColaList cola, FuncionDestructora destroy){
    return slist_eliminar_ultimo(cola,destroy);
}

void cola_imprimir(ColaList cola, FuncionVisitante visit){
    slist_imprimir(cola,visit);
}