#include <stdio.h>
#include <stdlib.h>

int* bubbleSort(int* arr, int largo){
    int seguir = 1;
    while(seguir){
        seguir = 0;
        for(int i = 0 ;i<largo-1; i++){
            if(arr[i] > arr[i+1]){
                seguir = 1;
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }
        }
    }
    return arr;
}

int* insertionSort(int* arr, int largo){
    int seguir = 1;
    while(seguir){
        seguir = 0;
        for(int j = 0 ;j<largo-1; j++){
            int terminar = 0;
            for(int i = 0 ;i<largo-1 && !terminar; i++){
                if(arr[i] > arr[i+1]){
                    seguir = 1;
                    int temp = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = temp;
                }else{
                    terminar = 1;
                }
            }
        }
    }
    return arr;
}

int* selectionSort(int* arr, int largo){
    for(int j = 0 ;j<largo-1; j++){
        int minPos = j;
        for(int i = 0 ;i<largo-1; i++){
            if(arr[i] < arr[minPos]) minPos = j;
        }
        int temp = arr[j];
        arr[j] = arr[minPos];
        arr[minPos] = temp;
    }
    return arr;
}

int* mergeSort(int* arr, int largo){
    for(int j = 0 ;j<largo-1; j++){
        int minPos = j;
        for(int i = 0 ;i<largo-1; i++){
            if(arr[i] < arr[minPos]) minPos = j;
        }
        int temp = arr[j];
        arr[j] = arr[minPos];
        arr[minPos] = temp;
    }
    return arr;
}

int main(){
    
}