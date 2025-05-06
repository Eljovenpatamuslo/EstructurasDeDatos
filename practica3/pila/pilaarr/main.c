#include "pilaArreglos.h"


int main(){
    Pila pila = pila_crear(5);

    printf("%i\n",pila_es_vacia(pila));

    pila_apilar(pila,8);
    pila_apilar(pila,2);

    printf("%i\n",pila_tope(pila));

    pila_apilar(pila,4);
    pila_apilar(pila,3);
    pila_apilar(pila,1);

    pila_desapilar(pila); 
    pila_desapilar(pila); 

    pila_imprimir(pila); 

    pila_destruir(pila);
    return 0;
}