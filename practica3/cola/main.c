#include <stdio.h>
#include <stdlib.h>
#include "colaArr.h"

int main(){
    ColaArr cola1 = cola_crear(5);
    printf("%i\n",cola_es_vacia(cola1));
    cola_encolar(cola1,1);
    cola_encolar(cola1,2);
    cola_encolar(cola1,3);
    cola_encolar(cola1,4);
    cola_desencolar(cola1);
    cola_desencolar(cola1);
    cola_encolar(cola1,5);
    cola_encolar(cola1,6);
    cola_encolar(cola1,7);
    cola_imprimir(cola1);
    printf("\n%i",cola1->posLibre);
    printf("\n%i",cola1->ultimoValor);
    return 0;
}