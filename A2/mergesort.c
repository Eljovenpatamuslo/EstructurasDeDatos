#include <stdio.h>
#include <stdlib.h>

// Mergea dos subarrays del arreglo
//el primer subarray es [izq...medio]
// Segundo subarray es [medio+1...derecha]
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Creo arrays temporales
    int leftArr[n1], rightArr[n2];

    // Copio la data en los temporales
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Mergeo los arreglos temporales devuelta en arr[left...right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copio restantes de leftArr
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copio restantes de rightArr
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// The subarray to be sorted is in the index range [left-right]
void mergeSort2(int arr[], int left, int right) {
    if (left < right) {
      
        // calculo punto medio
        int mid = left + (right - left) / 2;

        // ordeno las primeras y segundas mitades
        mergeSort2(arr, left, mid);
        mergeSort2(arr, mid + 1, right);

        // junto las mitades ordenadas
        merge(arr, left, mid, right);
    }
}

int* mergeSort(int arr[],int principio,int final){
    int* newarr = malloc(sizeof(int)* (final+1));
    for(int i=0; i<=final; i++){
        newarr[i] = arr[i];
    }
    mergeSort2(newarr,principio,final);
    return newarr;
}

int main(){
    int arr[] = {10,5,43,34,77,35,2,18,96,65};
    int* nuevo = mergeSort(arr,0,9);
    for(int i=0; i<10; i++){
        printf("%i\n",nuevo[i]);
    }
    free(nuevo);
}