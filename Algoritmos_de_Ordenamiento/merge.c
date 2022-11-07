#include <stdio.h>

void MergeSort(int A[], int p, int r);
void Merge(int A[],int p, int q, int r);
void Imprimir(int A[], int desde, int hasta);

int main()
{
	int i, n=100;
	int A[100] = {8176, 3, 5708, 8533, 1286, 6495, 7554, 4028, 2594, 342, 439, 2043, 6596, 9133, 3354, 9168, 1624, 1326, 4603, 3655, 2551, 8190, 6760, 4243, 448, 5277, 5246, 2187, 6583, 988, 3757, 3776, 4142, 8903, 5363, 9912, 8518, 9777, 4875, 6081, 2612, 9142, 6871, 9730, 4005, 119, 1738, 1938, 3552, 9378, 6089, 647, 7119, 7262, 612, 9139, 6435, 5576, 540, 6342, 4957, 1645, 2218, 8128, 1671, 3159, 6695, 5044, 3756, 7666, 4690, 2723, 6656, 1144, 6181, 9675, 7503, 1799, 4878, 3854, 9765, 8468, 1627, 9468, 284, 7872, 6925, 4593, 3508, 6012, 5110, 6055, 8692, 2785, 5785, 3589, 4627, 4713, 2078, 2015};
	/*
	n=10;
	int A[10] = {8176, 3, 5708, 8533, 1286, 6495, 7554, 4028, 2594, 342};
	*/
	MergeSort(A, 0, n-1);
	
	Imprimir(A,0,n-1);
	/*
    printf("[");
    for (i = 0; i < n-1; i++)
    {
        printf("%d, ", A[i]);
    }
    printf("%d]\n", A[n-1]);*/
	return 0;
}

void Imprimir(int A[], int desde, int hasta)
{
	int i;
	printf("[");
	for (i = desde; i <= hasta; i++)
		printf("%d ", A[i]);
	printf("]\n");
}

/*
MergeSort
Recibe:
	A[]: arreglo
	p: posición primer elemento
	r: posición último elemento
	
*/
void MergeSort(int A[], int p, int r)
{
	int q;

	if (p<r)
	{
		q=(p+r)/2;
		MergeSort(A,p,q);
		MergeSort(A,q+1,r);
		Merge(A,p,q,r);
	}
	
	
}

/*
Recibe:
	A[]: Arreglo
	p: posición primer elemento
	q: posición elemento a la mitad
	r: posición final
	
	l: longitud de arreglo
	
*/

void Merge(int A[], int p, int q, int r)
{
	int k, l=r-p+1, i=p, j=q+1;
	int C[l];
	
	for(k=0;k<l;k++)
	{
		if(i<=q&&j<=r)
		{
			if(A[i]<A[j])
			{
				C[k]=A[i];
				i++;
			}
			else
			{
				C[k]=A[j];
				j++;
			}
		}
		else if(i<=q)
		{
			C[k]=A[i];
			i++;
		}
		else
		{
			C[k]=A[j];
			j++;
		}
		//printf("C[%d] = %d\n",k, C[k]);
	}
	for(k=p,i=0;k<=r;k++,i++)
	{
		A[k]=C[i];
	}
}
