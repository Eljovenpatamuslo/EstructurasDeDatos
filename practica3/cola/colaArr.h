#ifndef __COLAARR_H__
#define __COLAARR_H__

// Definición de la estructura ColaArr
typedef struct ColaArr {
    int *arr;         // Array dinámico para almacenar los elementos
    int largo;        // Capacidad total del array
    int posAgregar;     // Índice del próximo espacio libre
    int posEliminar;  // Índice del primer valor en la cola
}*ColaArr;

ColaArr cola_crear(int largo);

int cola_es_vacia(ColaArr cola);

int cola_primero(ColaArr cola);

void cola_encolar(ColaArr cola, int dato);

void cola_desencolar(ColaArr cola);

void cola_imprimir(ColaArr cola);

void cola_destruir(ColaArr cola);

#endif