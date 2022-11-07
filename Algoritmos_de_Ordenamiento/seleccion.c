/*
seleccion.c
V 1.0 Octubre 2022
Autor: Juan L. Molina Acuña

Implementación del ordenamiento por selección en C basada en el pseudo=código
proporcionado por el profesor. Toma n números enteros de la entrada estándar
en la forma:
> seleccion.exe n n0 n1 n2 n3 n4 ...  (en windows)
Imprime estos valores de forma ordenada, junto al tiempo que tomó la ejecución
del algoritmo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Seleccion(int *A, int n);

int main(int argc, char *argv[])
{
	// Variables para la medición de tiempos
	clock_t t_inicio, t_final;
	double t_intervalo;
	// Variables para el algoritmo
	int i, j, n, *A;

	// Recibir por argumento el tamaño de n y el valor a buscar
	if (argc != 2)
	{
		printf("\nIndique el tamanio de n - Ejemplo: [user@equipo]$ %s 100\n", argv[0]);
		exit(1);
	}

	// Tomar el argumento del main
	n = atoi(argv[1]);
	A = malloc(n * sizeof(int));
	if (A == NULL)
	{
		printf("\nError al intentar reservar memoria para %d elementos\n", n);
		exit(1);
	}

	// Leer de la entrada estándar los n valores y colocarlos en el arreglo de números
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);

	// Inicia medición del tiempo
	t_inicio = clock();
	Seleccion(A , n);
	t_final = clock();
	t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);

	printf("\nArreglo Ordenado:\n");
	for (i = 0; i < n; i++)
		printf("\nA[%d]=%d", i, A[i]);

	printf("\n\nTiempo medido: %.8f segundos.\n", t_intervalo);
	return 0;
}

/*
void Seleccion(int *A, int n)
Recibe:*A: Dirección al arreglo a ordenar
		n: Tamaño del arreglo
Realiza los cambios en el arreglo A para ordenarlo de menor a mayor
Complejidad: O(n^2)
*/
void Seleccion(int *A, int n)
{
	int i,k,p,temp;

	for(k=0; k<=n-2; k++)
	{
		//printf("%d ",k);
		p=k;
		for(i=k+1; i<=n-1; i++)
		{
			if(A[i]<A[p])
			{
				p=i;
			}
		}
		temp = A[p];
		A[p] = A[k];
		A[k] = temp;
	}
}
