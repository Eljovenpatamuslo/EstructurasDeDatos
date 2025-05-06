#include <stdio.h>
#include <stdlib.h>
#include "sglist.h"
#include "contacto.h"

int main(){
    SGList lista = sglist_crear();

    Contacto *contactos[6];
    void** arr = malloc(sizeof(void*)*6);
    
    contactos[0] = contacto_crear("Pepe Argento", "3412695452", 61);
    contactos[1] = contacto_crear("Moni Argento", "3412684759", 60);
    contactos[2] = contacto_crear("Coqui Argento", "3415694286", 32);
    contactos[3] = contacto_crear("Paola Argento", "3416259862", 29);
    contactos[4] = contacto_crear("Maria Elena Fuseneco", "3416874594", 59);
    contactos[5] = contacto_crear("Dardo Fuseneco", "3416894526", 64);
    for (int i = 0; i < 6; ++i) {
        arr[i] = (void*)contactos[i];
    }
    for (int i = 0; i < 6; ++i) {
        lista =
        sglist_insertar(lista, contactos[i], (FuncionCopia)contacto_copia,(FuncionComparadora)contacto_comparar);
        contacto_destruir(contactos[i]);
    }
    sglist_recorrer(lista,(FuncionVisitante)contacto_imprimir);
    printf("%i\n",sglist_buscar(lista,contactos[1],(FuncionComparadora)contacto_comparar));
    //sglist_recorrer(sglist_arr(arr,6,(FuncionCopia)contacto_copia,(FuncionComparadora)contacto_comparar),(FuncionVisitante)contacto_imprimir);
    sglist_destruir(lista,(FuncionDestructora)contacto_destruir);
    return 0;
}