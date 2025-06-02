#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char*pais;
    char*ciudad;
    int cantidadHabitantes;
    int importancia;
} Objetivo;

typedef struct nodo{
    Objetivo dato;
    struct nodo*anterior;
    struct nodo*siguiente;
} Nodo;

Nodo* agregaObjetivo(Nodo* inicio, Objetivo o){
    Nodo* newNodo = malloc(sizeof(Nodo));
    newNodo->dato = o;
    newNodo->anterior = newNodo;
    newNodo->siguiente = newNodo;
    if(inicio == NULL) return newNodo;

    newNodo->anterior = inicio->anterior;
    inicio->anterior->siguiente = newNodo;
    inicio->anterior = newNodo;
    newNodo->siguiente = inicio;
    //aux->anterior->siguiente = newNodo;
    return newNodo;
}

void muestraCantidadHabitantesPorPais(Nodo*inicio, char*pais){
    Nodo* aux = inicio;
    for(int i = 0;aux != inicio || i==0; aux = aux->siguiente,i++){
        if(!strcmp(aux->dato.pais,pais)) printf("%i\n",aux->dato.cantidadHabitantes);
    }
}

int main(){
    Objetivo objetivo;
    objetivo.cantidadHabitantes = 2;
    objetivo.ciudad = "tutu";
    objetivo.importancia = 5;
    objetivo.pais = "arg";

    Objetivo objetivo2;
    objetivo2.cantidadHabitantes = 220;
    objetivo2.ciudad = "tutu1";
    objetivo2.importancia = 53;
    objetivo2.pais = "arg";

    Objetivo objetivo3;
    objetivo3.cantidadHabitantes = 2203;
    objetivo3.ciudad = "tutu12";
    objetivo3.importancia = 532;
    objetivo3.pais = "arg23";


    Nodo* newNodo = agregaObjetivo(NULL,objetivo);
    newNodo = agregaObjetivo(newNodo,objetivo2);
    newNodo = agregaObjetivo(newNodo,objetivo3);
    printf("%i\n",newNodo->dato.cantidadHabitantes);
    muestraCantidadHabitantesPorPais(newNodo,"arg");
}