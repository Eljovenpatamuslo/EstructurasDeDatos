#include <stdio.h>
#include <stdlib.h>

int pico_encontrar(int *arr,int largo){
    if(arr[0] >= arr[1]) return arr[0];
    if(arr[largo-1] >= arr[largo-2]) return arr[largo-1];

    int bandera = 0;
    int pico = -1;
    for(int i=1;i < largo-1 && !bandera;i++){
        if(arr[i-1] <= arr[i] && arr[i] >= arr[i+1]){
            bandera = 1;
            pico = i;
        }
    }
    return pico;
}

int pico_encontrar_rec(int *arr, int indice, int largoMenosUno){
    int mid = indice + (largoMenosUno - indice) / 2;
    if(arr[mid-1] <= arr[mid] && arr[mid] >= arr[mid+1]) return arr[mid];

    if(arr[mid] <= arr[mid-1]){
        largoMenosUno = mid - 1;
        pico_encontrar_rec(arr,indice,largoMenosUno);
    }
    if(arr[mid] <= arr[mid + 1]){
        indice = mid + 1;
        pico_encontrar_rec(arr,indice,largoMenosUno);
    }
}


int pico_encontrar_while(int *arr, int largo){
    if(arr[0] >= arr[1]) return arr[0];
    if(arr[largo-1] >= arr[largo-2]) return arr[largo-1];
    int terminar = 0;
    int indice = -1;
    int mid = largo / 2;
    while(!terminar){
        if(arr[mid-1] <= arr[mid] && arr[mid] >= arr[mid+1]){
            terminar = 1;
            indice = mid;
        }
        if(arr[mid + 1] > arr[mid]){
            mid++;
        }else{
            mid--;
        }
    }
    return indice;
}



int main(){
    int arr[] = {0,6,3,2,1,0};
    printf("%i",pico_encontrar_while(arr,6));
    return 0;
}