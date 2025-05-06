#ifndef __COLALIST_H__
#define __COLALIST_H__

#include "slist.h"

typedef SList ColaList;

void* copiar(void* dato);

void destruir2(void* dato);

void visitar(void* dato);

ColaList cola_crear();

void cola_destruir(ColaList cola, FuncionDestructora destroy);

int cola_es_vacia(ColaList cola);

void* cola_inicio(ColaList cola);

ColaList cola_encolar(ColaList cola,void* dato, FuncionCopia copy);

ColaList cola_desencolar(ColaList cola, FuncionDestructora destroy);

void cola_imprimir(ColaList cola, FuncionVisitante visit);

#endif