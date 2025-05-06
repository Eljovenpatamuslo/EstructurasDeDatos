#ifndef __PILALIST_H__
#define __PILALIST_H__

#include "glist.h"

typedef GList Pila;

void* copiar(void* dato);
void visitar(void* dato);
void destruir2(void* dato);

Pila pila_crear();

void pila_destruir(Pila pila);

int pila_es_vacia(Pila pila);

int pila_tope(Pila pila); 

Pila pila_apilar(Pila pila, int dato);

void pila_desapilar(Pila pila); 

void pila_imprimir(Pila pila); 

#endif