#include <stdio.h>
#include <stdlib.h>

#ifndef HEAP_H
#define HEAP_H

typedef int (*FuncionComparadora)(void *dato1, void *dato2);
typedef void (*FuncionDestructora)(void *dato);
typedef void *(*FuncionCopia)(void *dato);
typedef void (*FuncionVisitante)(void *dato);


typedef struct _BHeap{
    void **arr;
    int capacidad;
    int ultimo;
    FuncionComparadora comp;
    FuncionCopia copy;
    FuncionDestructora destr;
 } *BHeap;

typedef BHeap PriorityQueue;
// Crea un BHeap binario vacío
BHeap bheap_crear(FuncionComparadora comp, FuncionCopia copy, FuncionDestructora destr);

// Determina si el BHeap es vacio
int bheap_es_vacio(BHeap heap);

// Inserta un elemento en un BHeap
void bheap_insertar(void* data, BHeap heap);

// Retorna y elimina el elemento en el tope del BHeap
void* bheap_pop(BHeap heap);

// Recorre el BHeap
void bheap_recorrer(FuncionVisitante visit, BHeap heap);

// Elimina un elemento dado del BHeap
void bheap_eliminar(void* dato, BHeap heap);

// Destruye un BHeap
void bheap_destruir(BHeap heap);

// Crea un BHeap desde un array.
// No crea una copia del array, utiliza la misma referencia.
BHeap bheap_crear_desde_arr(void **arr, int largo,FuncionComparadora comp, FuncionCopia copiar, FuncionDestructora destr);

// Heapsort
void heapSort(void** arr, int largo, FuncionComparadora comp);

//crear una Priority queue
PriorityQueue cola_prioridad_crear(FuncionComparadora comp, FuncionCopia copy,FuncionDestructora destr);

void cola_prioridad_destruir(PriorityQueue pq);

//retorne 1 si la cola esta vacia y 0 en caso contrario
int cola_prioridad_es_vacia(PriorityQueue pq);

//  inserta un elemento en la cola con una determinada prioridad.
void cola_prioridad_insertar(void* dato, PriorityQueue pq);

// retorna el elemento prioritario de la cola
void* cola_prioridad_maximo(PriorityQueue pq);

//elimina el elemento prioritario de la cola
void cola_prioridad_eliminar_maximo(PriorityQueue pq);

#endif