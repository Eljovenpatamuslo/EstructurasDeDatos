#ifndef __SECUENCIA_NUM_H__
#define __SECUENCIA_NUM_H__

typedef struct _menoresNodo{
    int dato;
    int cantidadMenores;
    struct _menoresNodo* sig;
}menoresNodo;

typedef struct _secuenciaNum{
    menoresNodo* num;
    int cantidad_nodos;
}*secuenciaNum;

secuenciaNum crear_secuenciaNum();

void añadir_inicio_aux_a(secuenciaNum secuencia, int i, int j);

secuenciaNum buscar_por_cantidadMenores(secuenciaNum secuencia,int n);

void insertar_en_posicion(secuenciaNum secuencia,int dato, int posicion);

void borrar_en_posicion(secuenciaNum secuencia, int posicion);

menoresNodo* separar(menoresNodo* nodo);

menoresNodo* merge(menoresNodo* lista1, menoresNodo* lista2);

menoresNodo* MergeSort_lista(menoresNodo* lista);

void ordenar_por_cantidadMenores(secuenciaNum secuencia);

#endif
