#include <stdio.h>
#include <stdlib.h>
#include "colaArr.h"
int main(){
    ColaArr cola1 = cola_crear(4);
    printf("La cola esta vacia? : %i\n",cola_es_vacia(cola1));
    cola_encolar(cola1,1);
    cola_encolar(cola1,2);
    cola_encolar(cola1,3);
    cola_encolar(cola1,4);
    cola_imprimir(cola1);
    cola_desencolar(cola1);
    cola_desencolar(cola1);
    cola_encolar(cola1,5);
    cola_encolar(cola1,6);
    cola_encolar(cola1,7);
    cola_imprimir(cola1);
    printf("\n%i",cola1->posAgregar);
    printf("\n%i",cola1->posEliminar);
    cola_destruir(cola1);
    return 0;
}