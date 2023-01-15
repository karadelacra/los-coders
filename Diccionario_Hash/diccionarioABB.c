/*
diccionario.c
V 1.0 Enero 2023
Autores:
    Juan Luis Molina
    Karel Román Padilla
    Danna Lizbeth Matías
    Darío Quiñones

Con base en un arbol binario de busqueda, implementa un diccionario de palabras, donde
se puede agregar, buscar, modificar y consultar.

Es opcional incluir:

1. Poder buscar todas las palabras que empiecen con una letra, frase o subcadena dada.
2. Poder exportar una definición a un archivo de texto.
3. poder mostrar el contenido del diccionario con las 3 formas PreOrden, InOrden y PosOrden.

Durante la ejecución del programa se imprimen datos en cuanto a la eficiencia
del diccionario, como el número de colisiones, la cantidad de comparaciones
realizadas, etc.

Se compila de la forma:
    gcc -w -o diccionario diccionario.c ./lib/TADListaSL.c ./lib/TADTablaHash.c

Se ejecuta de la forma:
    ./diccionario
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/TADABB.h"
#include "./lib/TADListaSL.h"
#include "./lib/TADListaSL.c"
#define NUM_LISTAS 1000

void DibujarMenu();
void CargarArchivo(abb *a);
void AgregarPalabra(abb *a);
void BuscarPalabra(abb *a);
void ModificarDefinicion(abb *a);
void EliminarPalabra(abb *a);
void InformacionBusqueda(abb *a, int lista, int comps);
void LimpiarBuffer();
void RecorridoPreOrden(abb *a);
void RecorridoInOrden(abb *a);
void RecorridoPosOrden(abb *a);
void VerEstadisticas(abb *a);
bool ElementoVacio(elemento e);

int main(void)
{

	lista mi_lista[NUM_LISTAS];
	elemento a,b;
	posicion p;
	int i,j,n;
	
	for(i=0;i<NUM_LISTAS;i++)
		Initialize(&mi_lista[i]);
	
	for(j=0;j<NUM_LISTAS;j++)
		for(i=0;i<20;i++)
		{
			a.n=i;
			Add(&mi_lista[j],a);
		}
	
	for(j=0;j<NUM_LISTAS;j++)
	{
		p=Final(&mi_lista[j]);
		for(i=0;i<Size(&mi_lista[j]);i++)
		{
			b=Position(&mi_lista[j],p);
			printf("\n%d",b.n);
			p=Previous(&mi_lista[j],p);
		}
	}
	
	//Inserta un 50 en la mitad lista 500
	n=Size(&mi_lista[500]);
	n/=2;
	a.n=50;
	p=ElementPosition(&mi_lista[500],n);
	
	Insert(&mi_lista[500],p,a,TRUE);
	printf("\nLista 500\n");
	p=First(&mi_lista[500]);
	for(i=0;i<Size(&mi_lista[500]);i++)
	{
		a=Position(&mi_lista[500],p);
		printf("\n%d",a.n);
		p=Following(&mi_lista[500],p);
	}	
	
	//VerLigasLista(&mi_lista[500]);
	
	for(j=0;j<NUM_LISTAS;j++)
		Destroy(&mi_lista[j]);
	
	return 0;
}
