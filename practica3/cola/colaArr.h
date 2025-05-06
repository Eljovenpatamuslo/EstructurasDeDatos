#ifndef __COLAARR_H__
#define __COLAARR_H__

typedef struct ColaArr{
    int* arr;
    int posLibre;
    int ultimoValor;
    int largo;
} *ColaArr;

ColaArr cola_crear(int largo);

int cola_es_vacia(ColaArr cola);

int cola_primero(ColaArr cola);

void cola_encolar(ColaArr cola, int dato);

void cola_desencolar(ColaArr cola);

void cola_imprimir(ColaArr cola);

void cola_destruir(ColaArr cola);

#endif