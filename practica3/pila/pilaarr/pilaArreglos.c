#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pilaArreglos.h"

Pila pila_crear(int largo) {
    if (largo <= 0) return NULL;

    Pila pila = malloc(sizeof(*pila));
    if (!pila) return NULL;

    pila->ultimo = 0;
    pila->arr = malloc(sizeof(ArregloEnteros));
    if (!pila->arr) {
        free(pila);
        return NULL;
    }

    pila->arr->capacidad = largo;
    pila->arr->direccion = malloc(sizeof(int) * largo);
    if (!pila->arr->direccion) {
        free(pila->arr);
        free(pila);
        return NULL;
    }

    return pila;
}

void pila_destruir(Pila pila) {
    if (!pila) return;

    free(pila->arr->direccion);
    free(pila->arr);
    free(pila);
}

int pila_es_vacia(Pila pila) {
    if (!pila) return 1;
    return pila->ultimo == 0;
}

int pila_tope(Pila pila) {
    assert(!pila_es_vacia(pila));
    return pila->arr->direccion[pila->ultimo - 1];
}

void pila_apilar(Pila pila, int dato) {
    if (!pila) return;

    if (pila->ultimo >= pila->arr->capacidad) {
        arreglo_enteros_ajustar(pila->arr, pila->arr->capacidad * 2);
    }
    pila->arr->direccion[pila->ultimo] = dato;
    pila->ultimo++;
}

void pila_desapilar(Pila pila) {
    if (pila_es_vacia(pila)) return;
    pila->ultimo--;
}

void pila_imprimir(Pila pila) {
    if (!pila) return;

    for (int i = pila->ultimo - 1; i >= 0; i--) {
        printf("%i\n", pila->arr->direccion[i]);
    }
}