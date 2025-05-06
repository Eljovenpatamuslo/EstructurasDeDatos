#include "colaArr.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

ColaArr cola_crear(int largo){
    ColaArr nuevaCola = malloc(sizeof(ColaArr));
    assert(nuevaCola != NULL);
    
    nuevaCola->arr = malloc(sizeof(int)*largo);
    nuevaCola->largo = largo;
    nuevaCola->posAgregar = 0;
    nuevaCola->posEliminar = -1;
    return nuevaCola;
}

int cola_es_vacia(ColaArr cola){
    return cola->posLibre == cola->ultimoValor;
}

int cola_primero(ColaArr cola){
    return cola->arr[cola->posLibre-1];
}

void cola_encolar(ColaArr cola, int dato){
    if(cola->ultimoValor != -1){
        cola->arr[cola->ultimoValor] = dato;
        cola->ultimoValor--;
        printf("%i",cola->ultimoValor);
    }else{
        cola->arr[cola->posLibre] = dato;
        cola->posLibre = (cola->posLibre + 1) % cola->largo;  
    }
}

void cola_desencolar(ColaArr cola){
    if(!cola_es_vacia(cola)){
        cola->ultimoValor = (cola->ultimoValor + 1) % cola->largo;
    }else{
        printf("No se puede desencolar una cola vacia");
    }
}

void cola_imprimir(ColaArr cola){
    for(int i = 0; i<cola->largo;i++){
        printf("%i ",cola->arr[i]);
    }
}

void cola_destruir(ColaArr cola){
    free(cola->arr);
    free(cola);
}