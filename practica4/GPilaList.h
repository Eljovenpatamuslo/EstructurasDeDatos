#ifndef __GPILALIST_H__
#define __GPILALIST_H__

#include "glist.h"

typedef GList Pila;

void* copiar(void* dato);
void visitar(void* dato);
void destruir2(void* dato);

Pila pila_crear();

void pila_destruir(Pila pila,FuncionDestructora destroy);

int pila_es_vacia(Pila pila);

void* pila_tope(Pila pila); 

Pila pila_apilar(Pila pila, void* dato, FuncionCopia copy);

void pila_desapilar(Pila pila,FuncionDestructora destroy); 

void pila_imprimir(Pila pila, FuncionVisitante visit); 

#endif