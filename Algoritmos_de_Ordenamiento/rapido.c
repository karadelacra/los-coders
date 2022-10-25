#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void QuickSort(int *A, int p, int r);
int Pivot(int *A, int p, int r);
void Intercambiar(int *A, int i, int j);
void imprimir(int *A, int desde, int hasta);

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
	n = atoi(argv[1]); // n

	// Apartar memoria para n números  enteros
	A = malloc(n * sizeof(int));
	if (A == NULL)
	{
		printf("\nError al intentar reservar memoria para %d elementos\n", n);
		exit(1);
	}

	// Leer de la entrada estandar los n valores y colocarlos en el arreglo de números
	for (i = 0; i < n; i++)
		scanf("%d", &A[i]);

	//*****************************************
	// Algoritmo a medir el tiempo
	//*****************************************
	// Inicia medición del tiempo
	t_inicio = clock();

	// Llamar al algoritmo
	QuickSort(A, 0, n - 1);

	// Termina medición del tiempo
	t_final = clock();

	// Cálculo del tiempo y enviar mensaje a salida estandar con la medición
	t_intervalo = (double)(t_final - t_inicio) / (CLOCKS_PER_SEC);

	// Enviar a la salida estandar el arreglo final
	printf("\n\nArreglo Ordenado:");
	for (i = 0; i < n; i++)
		printf("\nA[%d]=%d", i, A[i]);

	// Mostrar el tiempo medido
	printf("\n\nTiempo medido: %.8f segundos.\n", t_intervalo);
	return 0;
}

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

int Pivot(int *A, int p, int r)
{
    int piv = A[p], i = p+1, j = r;
    do // <-- Es importante que se ejecute por lo menos una vez
    {
        while (A[i] <= piv && i < j) i++;
        while (A[j] > piv) j--;
		// Intercambiar(A, i, j);
        if (i < j) Intercambiar(A, i, j); // <-- Diferencia respecto al pseudocódigo del profe
    } while (i < j);
    Intercambiar(A, p, j);
    return j;
}

void Intercambiar(int *A, int i, int j)
{
    int temp = A[j];
    A[j] = A[i];
    A[i] = temp;
}

void imprimir(int *A, int desde, int hasta)
{
	int i;
	printf("[");
	for (i = desde; i <= hasta; i++)
		printf("%d ", A[i]);
	printf("]\n");
}