//ordenamiento por shell
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(){

    int i, k, b,temp;
    int n=10;
	int A[10] = {8176, 3, 5708, 8533, 1286, 6495, 7554, 4028, 2594, 342};
	
 
    
k=trunc(n/2);
while(k>=1){
    b = 1;
    while (b!=0){
        b=0;
        for (i=k; i<n; i++){
            if (A[i-k] > A[i]){
                temp=A[i];
                A[i]=A[i-k];
                A[i-k]=temp;
                b=b+1;
            }
        }

    }
    k=trunc(k/2);
    }

//imprimimos el arreglo ordenado
    for (i = 0; i < n; i++)
    {
        printf("%d\n", A[i]);

    }

    return 0;
}

