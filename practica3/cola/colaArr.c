#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "colaArr.h"



typedef struct ColaArr* ColaArr;

// Crear una nueva cola
ColaArr cola_crear(int largo) {
    ColaArr nuevaCola = malloc(sizeof(struct ColaArr));
    assert(nuevaCola != NULL);  // Verificar que la memoria fue asignada
    
    nuevaCola->arr = malloc(sizeof(int) * (largo+1));
    assert(nuevaCola->arr != NULL);  // Verificar que la memoria fue asignada
    
    nuevaCola->largo = largo+1;
    nuevaCola->posAgregar = 0;  // Inicialmente, la cola está vacía
    nuevaCola->posEliminar = -1;  // No hay elementos en la cola
    return nuevaCola;
}

// Verificar si la cola está vacía
int cola_es_vacia(ColaArr cola) {
    return cola->posEliminar == -1;
}

// Verificar si la cola está llena
int cola_llena(ColaArr cola) {
    return (cola->posAgregar + 1) % cola->largo == cola->posEliminar;
}

// Obtener el primer elemento de la cola
int cola_primero(ColaArr cola) {
    assert(!cola_es_vacia(cola));  // Asegurarse de que la cola no esté vacía
    return cola->arr[cola->posEliminar];
}

// Encolar un elemento en la cola
void cola_encolar(ColaArr cola, int dato) {
    printf("\n%i",cola->posAgregar);
    printf("\n%i",cola->posEliminar);
    if (cola_llena(cola)) {
        printf("Error: La cola está llena.\n");
        return;
    }
    
    // Insertar el nuevo elemento en la posición libre
    cola->arr[cola->posAgregar] = dato;
    cola->posAgregar = (cola->posAgregar + 1) % cola->largo;  // Avanzar circularmente
    
    // Si la cola estaba vacía, actualizar `posEliminar`
    if (cola->posEliminar == -1) {
        cola->posEliminar = 0;
    }
}

// Desencolar un elemento de la cola
void cola_desencolar(ColaArr cola) {
    if (cola_es_vacia(cola)) {
        printf("Error: No se puede desencolar una cola vacía.\n");
        return;
    }
    
    // Avanzar el índice del primer elemento
    if (cola->posEliminar == cola->posAgregar - 1) {
        // Si la cola queda vacía después de desencolar
        cola->posEliminar = -1;
        cola->posAgregar = 0;
    } else {
        cola->posEliminar = (cola->posEliminar + 1) % cola->largo;
    }
}

// Imprimir los elementos de la cola
void cola_imprimir(ColaArr cola) {
    if (cola_es_vacia(cola)) {
        printf("La cola está vacía.\n");
        return;
    }
    
    printf("Cola: ");
    int i = cola->posEliminar;
    while (i != cola->posAgregar) {
        printf("%d ", cola->arr[i]);
        i = (i + 1) % cola->largo;  // Avanzar circularmente
    }
    printf("\n");
}

// Destruir la cola y liberar memoria
void cola_destruir(ColaArr cola) {
    free(cola->arr);
    free(cola);
}