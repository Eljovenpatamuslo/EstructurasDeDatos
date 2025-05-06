#include <stdio.h>
#include <stdlib.h>
#include "pilaArreglos.h"

Pila pila_crear(int largo){
    Pila pila = malloc(sizeof(Pila));
    pila->ultimo=0;
    pila->arr = malloc(sizeof(ArregloEnteros));
    pila->arr->capacidad = largo;
    pila->arr->direccion = malloc(sizeof(int)*largo);
    return pila;
}

void pila_destruir(Pila pila){
    free(pila->arr->direccion);
    free(pila->arr);
    free(pila);
}

int pila_es_vacia(Pila pila){
    return pila->ultimo == 0;
}

int pila_tope(Pila pila){
    return pila->arr->direccion[pila->ultimo];
}

void pila_apilar(Pila pila, int dato){
    if(pila->ultimo + 1 >= pila->arr->capacidad){
        arreglo_enteros_ajustar(pila->arr, pila->arr->capacidad*2);
    }
    pila->ultimo++;
    pila->arr->direccion[pila->ultimo] = dato;
}

void pila_desapilar(Pila pila){
    if(pila->ultimo != 0) pila->ultimo--;
}

void pila_imprimir(Pila pila){
    for(int i = pila->ultimo;i>0;i--){
        printf("%i\n",pila->arr->direccion[i]);
    }
}
