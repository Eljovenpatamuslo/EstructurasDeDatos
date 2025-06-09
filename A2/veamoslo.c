#include <stdio.h>
#include <stdlib.h>

void ordenar(int arr[], int largo){
    int suma = 0;
    for(int i = 0;i < largo; i++){
        suma+= arr[i];
    }
    suma = ((largo+1)*(largo+2)/2) - suma;
    for(int i = 1;i <=largo+1; i++){
        if(i == suma){
            i++;
        }
        if(i < suma){
            arr[i-1] = i;
        }
        else{
            arr[i-2] = i;
        }
        
    }
}
void sort(int* arreglo, int tam){
    for(int i=0; i<tam;){
        int dato_a_ubicar = arreglo[i];
        if(dato_a_ubicar != arreglo[dato_a_ubicar-1]){
            int temp = arreglo[dato_a_ubicar-1];
            arreglo[dato_a_ubicar-1] = dato_a_ubicar;
            arreglo[i] = temp;
        }else{
            i++;
        }     
    }
}

int main(){
    int arr[] = {2,3,1,4};
    ordenar(arr,4);
    for(int i = 0;i <5; i++){
        printf("%i\n",arr[i]);
    }
    return 0;
}