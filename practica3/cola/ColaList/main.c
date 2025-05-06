#include <stdio.h>
#include "ColaList.h"

int main(){
    int dato1 = 1;
    int dato2 = 2;
    void* data = &dato1;
    void* data2 = &dato2;
    ColaList cola = cola_crear();
    cola = cola_encolar(cola,data,copiar);
    cola = cola_encolar(cola,data2,copiar);
    cola_imprimir(cola,visitar);
    cola = cola_desencolar(cola,destruir2);
    cola_imprimir(cola,visitar);
    cola_destruir(cola,destruir2);
    return 0;
}