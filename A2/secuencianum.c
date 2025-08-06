#include <stdlib.h>
#include <stdio.h>
#include "secuencianum.h"

// Funciones auxiliares

secuenciaNum crear_secuenciaNum(){
    secuenciaNum secuencia_devolver = malloc(sizeof(struct _secuenciaNum));
    secuencia_devolver->cantidad_nodos = 0;
    secuencia_devolver->num = NULL;
    return secuencia_devolver;
}

void añadir_inicio_aux_a(secuenciaNum secuencia, int i, int j){
    menoresNodo* nuevo_nodo = malloc(sizeof(menoresNodo));
    if (secuencia->num != NULL && secuencia->num->dato > i)
        secuencia->num->cantidadMenores++;
    nuevo_nodo->dato = i;
    nuevo_nodo->cantidadMenores = j;
    nuevo_nodo->sig = secuencia->num;
    secuencia->num = nuevo_nodo;
    secuencia->cantidad_nodos+=1;
}

// a)


// Devuelve una secuencia de numeros que tengan n cantidad de menores
// ESTA FUNCION DEVUELVE UNA LISTA CON LOS ELEMENTOS, NO MODIFICA SU CANTIDAD DE MENORES
secuenciaNum buscar_por_cantidadMenores(secuenciaNum secuencia, int n){
    secuenciaNum secuencia_n = crear_secuenciaNum();
    // Recorremos la lista chequeando nodo por nodo
    for (menoresNodo* temp = secuencia->num; temp != NULL; temp = temp->sig){
        if (temp->cantidadMenores == n){
            añadir_inicio_aux_a(secuencia_n,temp->dato,temp->cantidadMenores);
        }
    }
    return secuencia_n;
}

// b)

int buscar_dato_en_secuencia(secuenciaNum sec, int dato){
    int encontrado = 0;
    for(menoresNodo* temp = sec->num; temp != NULL && !
        encontrado;temp= temp->sig){
        if (temp->dato == dato)
            encontrado = 1;
    }
    return encontrado;
}

// Dada una posicion , inserta dato en la n-esima posicion de la lista
void insertar_en_posicion(secuenciaNum secuencia,int dato, int posicion){
    // posiciones no validas
    if (posicion < 1 || (posicion > secuencia->cantidad_nodos && secuencia->cantidad_nodos) || buscar_dato_en_secuencia(secuencia,dato))
        return;
    // Si hay que añadirlo al principio, lo añadimso al principio (lol)
    if (posicion == 1){
        añadir_inicio_aux_a(secuencia,dato,0);
    }
    else{
        // Inicializamos variables
        menoresNodo* posterior = secuencia->num;
        menoresNodo* anterior = NULL;
        int cant_menores = 0;

        // Mientras que no estemos en la posicion en la que queramos meter el dato, nos movemos en la secuencia;
        while(posicion-1){
            if (posterior->dato < dato)
                cant_menores++;
            anterior = posterior;
            posterior = posterior->sig;
            posicion--;
        }
        menoresNodo* nuevo_nodo = malloc(sizeof(menoresNodo));
        nuevo_nodo->dato = dato;
        nuevo_nodo->cantidadMenores = cant_menores;
        nuevo_nodo->sig = posterior;
        anterior->sig = nuevo_nodo;
        secuencia->cantidad_nodos+=1;
    }
}

// b)

// Devuelve 1 si el dato está en la secuencia, 0 si no


void borrar_en_posicion(secuenciaNum secuencia, int posicion){
    if (secuencia == NULL || posicion < 1 || (posicion > secuencia->cantidad_nodos && secuencia->cantidad_nodos))
        return;
    else{
        int dato_auxiliar;
        menoresNodo* puntero_auxiliar = NULL;
        // Si el dato a eliminar es el inicial, liberamos el nodo y ahora secuencia->num apunta al siguiente del inicial
        if (posicion == 1){
            puntero_auxiliar = secuencia->num->sig;
            dato_auxiliar = secuencia->num->dato;
            menoresNodo* temp = secuencia->num;
            secuencia->num = temp->sig;
            free(temp);
        }
        else{
            menoresNodo* puntero_auxiliar = secuencia->num;
            menoresNodo* anterior = NULL;
            // puntero auxiliar va a apuntar al siguiente del dato a eliminar, anterior al anterior a eliminar.
            while(posicion-1){
                anterior = puntero_auxiliar;
                puntero_auxiliar = puntero_auxiliar->sig;
                posicion--;
            }
            puntero_auxiliar = puntero_auxiliar->sig;
            //Borramos el posterior del anterior (el nodo a eliminar)
            menoresNodo* temp = anterior->sig;
            dato_auxiliar = temp->dato;
            anterior->sig = puntero_auxiliar;
            free(temp);
        }
        // Recorremos los posteriores al dato eliminado para modificar (si corresponde) cantidadMenores
        for(;puntero_auxiliar != NULL;puntero_auxiliar = puntero_auxiliar->sig){
            if (puntero_auxiliar->dato > dato_auxiliar)
                puntero_auxiliar->cantidadMenores-=1;
        }
        secuencia->cantidad_nodos-=1;
    }
}

// d)

menoresNodo* separar(menoresNodo* nodo) {
    menoresNodo* dosPasos = nodo;
    menoresNodo* unPaso = nodo;

    // Mueve dosPasos dos nodos a la vez, unPaso uno a la vez, asegurando que cuando dosPasos sea nulo, unPaso 
    // esté apuntando a la mitad de la cadena
    while (dosPasos != NULL && dosPasos->sig != NULL) {
        dosPasos = dosPasos->sig->sig;
        if (dosPasos != NULL) {
            unPaso = unPaso->sig;
        }
    }

    // Separamos la lista de la siguiente forma
    // [inicio ->... unPaso] [unPaso->next ->... NULL]
    menoresNodo* temp = unPaso->sig;
    unPaso->sig = NULL;
    return temp;
}

// Mezcla dos listas ordenadas
menoresNodo* merge(menoresNodo* lista1, menoresNodo* lista2) {
  
    if (lista1 == NULL) return lista2;
    if (lista2 == NULL) return lista1;

    if (lista1->cantidadMenores <= lista2->cantidadMenores) {
        // Mergeamos recursivamente el resto de la lista
        // y enlazamos el resultado a lista1;
        lista1->sig = merge(lista1->sig, lista2);
        return lista1;
    }
    else {
        // Mergeamos recursivamente el resto de la lista
        // y enlazamos el resultado a lista2;
        lista2->sig = merge(lista1, lista2->sig);
        return lista2;
    }
}


menoresNodo* MergeSort_lista(menoresNodo* lista) {
  
    // Si la lista está vacía o tiene un solo elemento
    if (lista == NULL || lista->sig == NULL) {
        return lista;
    }

    // Partimos a la lista en dos mitades
    menoresNodo* lista_segunda_mitad = separar(lista);

    // Recursivamente llamamos a cada mitad
    lista = MergeSort_lista(lista);
    lista_segunda_mitad = MergeSort_lista(lista_segunda_mitad);

    // Mezlcamos las dos mitades ordenadas
    return merge(lista, lista_segunda_mitad);
}

// Ahora si, ordenamos la secuencia
void ordenar_por_cantidadMenores(secuenciaNum secuencia){
    secuencia->num = MergeSort_lista(secuencia->num);
}


void print_secuencia(secuenciaNum secuencia){
    printf("La secuencia tiene %d elementos\n",secuencia->cantidad_nodos);
    for (menoresNodo* temp = secuencia->num; temp != NULL; temp = temp->sig){
        printf("El nodo actual tiene de dato %d y %d elementos menores a el\n",temp->dato,temp->cantidadMenores);
    }
}


    void destruirSecuencia(secuenciaNum s) {
    if (s == NULL) return;
    menoresNodo* actual = s->num;
    while (actual != NULL) {
        menoresNodo* temp = actual;
        actual = actual->sig;
        free(temp);
    }
    free(s);
}

int main(){
    secuenciaNum sec = crear_secuenciaNum();
    insertar_en_posicion(sec,4,1);
    insertar_en_posicion(sec,3,1);
    insertar_en_posicion(sec,8,2);
    print_secuencia(sec);
    borrar_en_posicion(sec,1);
    borrar_en_posicion(sec,2);
    print_secuencia(sec);
    insertar_en_posicion(sec,8,1);
    insertar_en_posicion(sec,4,1);
    insertar_en_posicion(sec,12,2);
    insertar_en_posicion(sec,1,3);
    print_secuencia(sec);
    ordenar_por_cantidadMenores(sec);
    print_secuencia(sec);
    destruirSecuencia(sec);
}