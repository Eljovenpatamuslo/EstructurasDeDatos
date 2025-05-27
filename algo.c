#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <thread>


int buscar_repetido(int arr[], int len) {
	int i, j, terminar = 0;
	int count = 0;
	for (i = 0; i < len && !terminar; i++) {
		for (j = i; j < len && !terminar; j++) {
			count++;
			if (arr[i] == arr[j] && i != j)
				terminar = 1;
		}
	}
	printf("%i",count);
	if(terminar) return i-1;
	return -1;
}


int main(){
	int caca[] = {1,2,3,4,5,6,6};
    printf("%i",buscar_repetido(caca,7));
    return 0;
}