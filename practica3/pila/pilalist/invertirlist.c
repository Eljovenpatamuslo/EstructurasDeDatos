#include "GPilaList.h"
#include <stdio.h>

GList slist_invertir(GList lista,FuncionCopia copy, FuncionDestructora destroy){
    Pila pila = pila_crear();
    for(GList aux = lista; aux != NULL; aux = aux->next){
        pila = pila_apilar(pila,aux->data,copy);
    }
    return pila;
}

int main(){

    return 0;
}
