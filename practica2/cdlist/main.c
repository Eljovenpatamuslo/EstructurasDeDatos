#include "cdlist.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    DListOrdenDeRecorrido hola = DLIST_RECORRIDO_HACIA_ATRAS;
    DList* lista = malloc(sizeof(DList));
    DNodo* nodo1 = malloc(sizeof(DNodo));
    DNodo* nodo2 = malloc(sizeof(DNodo));
    DNodo* nodo3 = malloc(sizeof(DNodo));
    nodo1->dato = 1;
    nodo2->dato = 2;
    nodo3->dato = 3;
    nodo1->sig = nodo2;
    nodo1->ant = nodo3;
    nodo2->sig = nodo3;
    nodo2->ant = nodo1;
    nodo3->sig = nodo1;
    nodo3->ant = nodo2;
    lista->primero = nodo1;
    lista->ultimo = nodo3;
    cdlist_recorrer(lista,hola);
    return 0;
}