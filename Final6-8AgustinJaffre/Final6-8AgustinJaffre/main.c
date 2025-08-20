#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tablahash.h"
#define TAM 30
typedef struct {
char * nombre , * direccion , * dni ;
int edad ;
} Persona ;

Persona* crear_persona(char* nombre, char* direccion, char* dni, int edad){
    Persona* p = malloc(sizeof(Persona));
    p->nombre =malloc(sizeof(char)*TAM);
    p->direccion =malloc(sizeof(char)*TAM);
    p->dni =malloc(sizeof(char)*TAM);
    strcpy(p->nombre,nombre);
    strcpy(p->direccion,direccion);
    strcpy(p->dni,dni);
    p->edad = edad;
    return p;
}

void* copy(void* dato){
    Persona* p1 = (Persona*)dato;
    Persona* p = crear_persona(p1->nombre,p1->direccion,p1->dni,p1->edad);
    return p;
}

void delete(void* dato){
    Persona* p1 = (Persona*)dato;
    free(p1->nombre);
    free(p1->direccion);
    free(p1->dni);
    free(p1);
}

unsigned hash(void* dato){
    Persona* a_hashear = (Persona*)dato;
    unsigned hashvalue = atoi(a_hashear->dni);
    return hashvalue;
}

int comp(void* dato1, void* dato2){
    Persona* p1 = (Persona*)dato1;
    Persona* p2 = (Persona*)dato2;
    int dni1 = atoi(p1->dni);
    int dni2 = atoi(p2->dni);
    return dni1 - dni2;
}
int main(){
    Persona* p1 = crear_persona("agustin","chacabuco","46367818",18);
    Persona* p2 = crear_persona("pata","SanMartin","28967647",32);
    Persona* p3 = crear_persona("Lucas","Cochabamba","18658134",75);
    Persona* p4 = crear_persona("Daniel","Juarez","52367489",15);
    //printf("%s %s %s %i", p1->nombre, p1->direccion, p1->dni, p1->edad);

    TablaHash tabla = tablahash_crear(1,copy,comp, delete,hash);
    tablahash_insertar(tabla,p1);
    tablahash_insertar(tabla,p2);
    tablahash_insertar(tabla,p3);
    tablahash_insertar(tabla,p4);
    assert(tablahash_buscar(tabla,p1) != NULL);
    assert(tablahash_buscar(tabla,p2) != NULL);
    assert(tablahash_buscar(tabla,p3) != NULL);
    assert(tablahash_buscar(tabla,p4) != NULL);

    tablahash_eliminar(tabla,p2);
    assert(tablahash_buscar(tabla,p2) == NULL);

    delete(p1);
    delete(p2);
    delete(p3);
    delete(p4);
    tablahash_destruir(tabla);
}