#include "PilaList.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _colaPila{
    Pila pila1;
    Pila pila2;
} colaPila;

colaPila* cola_crear(){
    colaPila* cola = malloc(sizeof(colaPila));
    cola->pila1 = pila_crear();
    cola->pila2 = pila_crear();
    return cola;
}

Pila pila_invertir(Pila pila){
    if(pila == NULL) return NULL;
    Pila newPila = pila_crear();
    Pila aux = pila;
    while (aux != NULL)
    {
        newPila = pila_apilar(newPila,pila_tope(aux));
        aux = aux->next;  
    }
    //pila_destruir(pila);
    return newPila;
}

colaPila* enqueue(colaPila* cola, int dato){
    cola->pila1 = pila_apilar(cola->pila1,dato);
    if(cola->pila2 != NULL) pila_destruir(cola->pila2);
    cola->pila2 = pila_invertir(cola->pila1);
    return cola;
}

colaPila* dequeue(colaPila* cola){
    if(cola->pila1 != NULL) pila_destruir(cola->pila1);
    if(cola->pila2 != NULL) pila_desapilar(cola->pila2);
    cola->pila1 = pila_invertir(cola->pila2);
    return cola;
}

void cola_destruir(colaPila* cola){
    pila_destruir(cola->pila1);
    pila_destruir(cola->pila2);
    free(cola);
}

int main(){
    colaPila* cola = cola_crear();
    cola = enqueue(cola,1);
    cola = enqueue(cola,2);
    cola = enqueue(cola,3);
    cola = enqueue(cola,4);
    cola = dequeue(cola);
    cola = dequeue(cola);
    cola_destruir(cola);
}
