#include <stdio.h>
#include <stdlib.h>
typedef struct _Tablero{
    int** arr;
    int size;
    int **pos_reinas; // int*[2]
    int cant_reinas;

} Tablero;

void imprimir_tablero(Tablero* tablero){
    for(int i = 0; i<tablero->size; i++){

    for(int x=0; x<tablero->size;x++){
        printf("%i ",tablero->arr[i][x]);
    }
    printf("\n");
    }
}

Tablero *crear_tablero(int size){
    Tablero* tablero = malloc(sizeof(Tablero));
    tablero->size = size;
    tablero->arr = malloc(sizeof(int*)*size);
    for(int i = 0; i<tablero->size;i++){
        tablero->arr[i] = malloc(sizeof(int)*size);
        for(int x=0; x<tablero->size;x++){ 
            tablero->arr[i][x] = 0;
        }
    }
    tablero->cant_reinas = 0;
    tablero->pos_reinas = malloc(sizeof(int*)*size);
    for(int x=0; x<tablero->size;x++){
        tablero->pos_reinas[x] = malloc(sizeof(int)*2);
    }
    return tablero;
}

Tablero* chequar_y_agregar_reina(Tablero* tablero, int fila, int columna){
    int terminar = 0;
    for(int i=0;i<tablero->cant_reinas && !terminar;i++){
        int ry = tablero->pos_reinas[i][0];
        int rx = tablero->pos_reinas[i][1];
        if(ry - fila == 0 || rx-columna == 0 || abs(ry - fila) == abs(rx - columna)) terminar = 1;
    }
    if(terminar) return tablero;
    tablero->pos_reinas[tablero->cant_reinas][0] = fila;
    tablero->pos_reinas[tablero->cant_reinas][1] = columna;

    tablero->cant_reinas++;
    tablero->arr[fila][columna] = 1;
    return tablero;
}
    /*for reinas
    y-ry == 0 o x-rx == 0 o abs x-rx == abs y-ry then not agregar
    si no pasa nada de esto
    agregar_reina(y,x)*/

Tablero* funcion(Tablero *tablero,int reinas){
    int filax = -1;
    int columnax = -1;
    while(tablero->cant_reinas != reinas){
        for(int i = 0; i<tablero->size; i++){

            for(int x=0; x<tablero->size;x++){
                if(i != filax || x != columnax) tablero = chequar_y_agregar_reina(tablero,i,x);
            }
        }

        filax = tablero->pos_reinas[tablero->cant_reinas][0];
        columnax = tablero->pos_reinas[tablero->cant_reinas][1];
        tablero->cant_reinas--;

        imprimir_tablero(tablero);
        printf("\n");
    }
    return tablero;
}

int main(){
    Tablero* tablero = crear_tablero(8);
    tablero = funcion(tablero,8);
    imprimir_tablero(tablero);
    return 0;
}