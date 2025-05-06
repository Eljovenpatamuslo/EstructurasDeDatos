#ifndef __PILAARREGLOS_H__
#define __PILAARREGLOS_H__

#include "arreglos.h"

struct _Pila {
    ArregloEnteros *arr;
    int ultimo;
};

typedef struct _Pila *Pila;

Pila pila_crear(int largo);

void pila_destruir(Pila pila);

int pila_es_vacia(Pila pila);

int pila_tope(Pila pila); 

void pila_apilar(Pila pila, int dato);

void pila_desapilar(Pila pila); 

void pila_imprimir(Pila pila); 

#endif