#include <stdio.h>
#include <stdlib.h>
#include "GPilaList.h"


int main(){
    int dato1 = 1;
    int dato2 = 2;
    void* data = &dato1;
    void* data2 = &dato2;
    Pila pila1 = pila_crear();
    printf("%i\n",pila_es_vacia(pila1));
    pila1 = pila_apilar(pila1,data,copiar);
    printf("%i\n",pila_es_vacia(pila1));
    
    pila1 = pila_apilar(pila1,data2,copiar);
    pila_imprimir(pila1,visitar);
    /*pila1 = pila_apilar(pila1,data,copiar);
    pila1 = pila_apilar(pila1,data,copiar);
    pila_desapilar(pila1,destruir2);
    //pila_imprimir(pila1,visitar);*/
    
    pila_destruir(pila1,destruir2);
    return 0;
}