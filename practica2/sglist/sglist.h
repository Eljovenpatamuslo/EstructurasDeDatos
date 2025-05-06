#ifndef __SGLIST_H__
#define __SGLIST_H__

#include <stdlib.h>
#include "glist.h"

typedef GList SGList;

SGList sglist_crear();

void sglist_destruir(SGList list, FuncionDestructora destroy);

int sglist_vacia(SGList list);

void sglist_recorrer(SGList list, FuncionVisitante visit);

SGList sglist_insertar(SGList list, void *data, FuncionCopia copy, FuncionComparadora compare);

int sglist_buscar(SGList list, void *data, FuncionComparadora compare);

SGList sglist_arr(void **arr, int length, FuncionCopia copy, FuncionComparadora compare);

#endif