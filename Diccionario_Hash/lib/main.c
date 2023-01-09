#include <stdio.h>
#include "TADListaSL.h"
#define NUM_LISTAS 1000
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