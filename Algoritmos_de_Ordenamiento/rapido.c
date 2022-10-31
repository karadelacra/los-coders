/*
rapido.c
V 1.0 Octubre 2022
Autor: Darío Quiñones

Implementación de QuickSort en C basada en el pseudo=código proporcionado
por el profesor. Toma n números enteros de la entrada estándar en la forma:
> rapido.exe n n0 n1 n2 n3 n4 ...  (en windows)
Imprime estos valores de forma ordenada, junto al tiempo que tomó la ejecución
del algoritmo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void QuickSort(int *A, int p, int r);
int Pivot(int *A, int p, int r);
void Intercambiar(int *A, int i, int j);
void Imprimir(int *A, int desde, int hasta);

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
	QuickSort(A, 0, n - 1);
	t_final = clock();
	t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);

	printf("\nArreglo Ordenado:\n");
	for (i = 0; i < n; i++)
		printf("\nA[%d]=%d", i, A[i]);

	printf("\n\nTiempo medido: %.8f segundos.\n", t_intervalo);
	return 0;
}

/*
void QuickSort(int *A, int p, int r)
Recibe:*A: Dirección al arreglo a ordenar
		p: indice desde donde ordenar
		r: indice hasta donde ordenar
Realiza los cambios en el arreglo original, recursivamente ordena
los elementos de A desde el índice p hasta r de forma ascendente.
Complejidad: O(n log n)
*/
void QuickSort(int *A, int p, int r)
{
    if (p < r)
    {
		//imprimir(A, p, r);
        int j = Pivot(A, p, r);
		//imprimir(A, p, r);
        QuickSort(A, p, j-1);
        QuickSort(A, j+1, r);
    }
}

/*
int Pivot(int *A, int p, int r)
Recibe:*A: Dirección del arreglo
		p: Pivote, el primer elemento de la región a ordenar
		r: Límite de la región a ordenar
Devuelve: El indice del pivote después de ordenar la región
Coloca todos los elementos menores al pivote a la izquierda y
los mayores a la derecha, después intercambia el pivote para que
quede en su lugar correcto, retornando el indice del pivote
*/
int Pivot(int *A, int p, int r)
{
    int piv = A[p], i = p+1, j = r;
    do // <-- Es importante que se ejecute por lo menos una vez
    {
        while (A[i] <= piv && i < j) i++;
        while (A[j] > piv) j--;
		// Intercambiar(A, i, j);
        if (i < j) Intercambiar(A, i, j); // <-- Diferencia respecto al pseudo-código del profe
    } while (i < j);
    Intercambiar(A, p, j);
    return j;
}

/*
void Intercambiar(int *A, int i, int j)
Recibe:*A: Dirección del arreglo
		i: indice elemento a intercambiar con j
		j: indice elemento a intercambiar con i
Realiza el intercambio de los elementos en las posiciones i y j
*/
void Intercambiar(int *A, int i, int j)
{
    int temp = A[j];
    A[j] = A[i];
    A[i] = temp;
}

/*
void imprimir(int *A, int desde, int hasta)
Recibe:*A: Dirección del arreglo
		desde: indice desde donde imprimir
		hasta: indice hasta donde imprimir
Función auxiliar para imprimir el arreglo, usado durante el desarrollo
*/
void Imprimir(int *A, int desde, int hasta)
{
	int i;
	printf("[");
	for (i = desde; i <= hasta; i++)
		printf("%d ", A[i]);
	printf("]\n");
}