#include "arreglos.h"


ArregloEnteros* arreglo_enteros_crear(int capacidad){
    ArregloEnteros* Arreglo = malloc(sizeof(ArregloEnteros));
    Arreglo->direccion = malloc(sizeof(int)*capacidad);
    Arreglo->capacidad = capacidad;
    return Arreglo;
}

void arreglo_enteros_destruir(ArregloEnteros* arreglo){
    free(arreglo->direccion);
    arreglo->direccion = NULL;
    free(arreglo);
}

int arreglo_enteros_leer(ArregloEnteros* arreglo, int pos){
    return arreglo->direccion[pos];
}

void arreglo_enteros_escribir(ArregloEnteros* arreglo, int pos, int dato){
    arreglo->direccion[pos] = dato;
}

int arreglo_enteros_capacidad(ArregloEnteros* arreglo){
    return arreglo->capacidad;
}

void arreglo_enteros_imprimir(ArregloEnteros* arreglo){
    for(int i=0;i<arreglo->capacidad;i++){
        printf("pos %i:%i\n",i,arreglo->direccion[i]);
    }
}

void arreglo_enteros_ajustar(ArregloEnteros* arreglo, int capacidad){
    if(arreglo->capacidad < capacidad){
        arreglo->direccion = realloc(arreglo->direccion,sizeof(ArregloEnteros)*capacidad);
    }
    arreglo->capacidad = capacidad;
}

void arreglo_enteros_insertar(ArregloEnteros* arreglo, int pos, int dato){
    arreglo_enteros_ajustar(arreglo,arreglo->capacidad*2);
    for(int i = arreglo->capacidad-1;i != pos;i--){
        arreglo->direccion[i] = arreglo->direccion[i-1];
    }
    arreglo->direccion[pos] = dato;
}

void arreglo_enteros_eliminar(ArregloEnteros* arreglo, int pos){
    for(int i = pos;i<arreglo->capacidad-1;i++){
        arreglo->direccion[i] = arreglo->direccion[i+1];
    }
    
    arreglo_enteros_ajustar(arreglo,arreglo->capacidad-1);
}