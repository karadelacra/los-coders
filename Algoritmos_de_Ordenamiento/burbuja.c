/*
burbuja.c
V 1.0 Octubre 2022
Autor: Karel R. Padilla

Implementación del ordenamiento por burbuja en C basada en el pseudo=código
proporcionado por el profesor. Toma n números enteros de la entrada estándar
en la forma:
> burbuja.exe n n0 n1 n2 n3 n4 ...  (en windows)
Imprime estos valores de forma ordenada, junto al tiempo que tomó la ejecución
del algoritmo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Burbuja(int*A,int n);

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
	// Llamar al algoritmo
	Burbuja(A, n);
	t_final = clock();
	t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);

	printf("\nArreglo Ordenado:\n");
	for (i = 0; i < n; i++)
		printf("\nA[%d]=%d", i, A[i]);

	printf("\n\nTiempo medido: %.8f segundos.\n", t_intervalo);
	return 0;
}

/*
void Burbuja(int *A, int n)
Recibe:*A: Dirección al arreglo a ordenar
		n: tamaño del arreglo
Ordena el arreglo A de tamaño n mediante el algoritmo de la burbuja
Complejidad: O(n^2)
*/
void Burbuja(int *A, int n)
{
	int i, j, aux;
	int cambios = 1;
	i=0;
	while (i<= n-2 && cambios != 0)
	{
		cambios = 0;
		for (j=0; j <= (n-2)-i; j++)
		{
			if (A[j] > A[j+1])
			{
				aux = A[j];
				A[j] = A[j+1];
				A[j+1] = aux;
				cambios = 1;
			}
		}
		i++;
	}
}