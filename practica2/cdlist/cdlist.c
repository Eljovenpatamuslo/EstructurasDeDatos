#include "cdlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void cdlist_recorrer(DList* list, DListOrdenDeRecorrido sentido){
    DNodo* aux = sentido ? list->ultimo : list->primero; 
    for(int i = 0;sentido ? aux != list->ultimo || i == 0 : aux != list->primero || i == 0; aux = sentido ? aux->ant : aux->sig){
        i=1;
        printf("%i",aux->dato);
    }
}