#include <stdio.h>
#include <stdlib.h>


int binsearch(int a[], int len, int v){
    int largoMedio = (len/2)-1;
    int indiceEncontrado = -1;
    if(a[len-1] == v) return len-1;
    if(a[0] == v) return 0;
    while(largoMedio && indiceEncontrado == -1){
        if(a[largoMedio] == v){
            indiceEncontrado = largoMedio;
        }else if(a[largoMedio] > v){
            largoMedio = largoMedio/2;
        }else{ // a[largoMedio] < v
            largoMedio = (len-1 - largoMedio)/2 + largoMedio;
        }
    }
    return indiceEncontrado;
}
int main(){
    int a[] = {1,2,3,4,5,6,7,8,9};
    printf("%i",binsearch(a,9,8));
    return 0;
}