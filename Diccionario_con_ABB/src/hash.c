#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../lib/TAD_Lista/TADListaSL.h"

/*
Se compila de la forma:
    (Linux)
    gcc -o hash hash.c ../lib/TAD_Lista/TADListaSL.c ../lib/presentacionLin.c
    (Windows)
    gcc -o hash hash.c ../lib/TAD_Lista/TADListaSL.c ../lib/presentacionWin.c
*/

int AsignarValor(char c);
char RegresarValor(int n);
void DibujarMenu();
void CargarArchivo(lista milista, char *direccion);

int main()
{
	BorrarPantalla();
	lista milista;
	Initialize(&milista);
	char direccion;
	//printf("\n%s",d);s
	int opcion;
	int a;
	char str[37] = "abcdefghijklmnopqrstuvwxyz0123456789";
	char str2[37] = "";
	int ar[37];
	while(true)
	{
		DibujarMenu();
		printf("\n\n  \033[35mOpci%cn: \033[97m",162);
		scanf("%d",&opcion);
		printf("\033[0m");
		if(opcion == 1)
		{
			CargarArchivo(milista, &direccion);
		}
		else if(opcion == 7)
		{
			break;
		}
	}
	
	/*a = AsignarValor('b');
	//a = (int)character - 48;
	a = 0;
	for(i = 0; i < strlen(str); i++)
	{
		a = AsignarValor(str[i]);
		//a *= (i+1);
		a += 17;
		a %= 36;
		a++;
		ar[i] = a;
		str2[i] = RegresarValor(a);
	}
	/*printf("\n\n%s", str);
	for(i = 0; i < 36; i++)
	{
		printf("\n%c = %d = %c", str[i], ar[i], str2[i]);
	}*/
	//printf("\n%s", str2);
	return 0;
}

void DibujarMenu()
{	//FrontMagenta();
	BorrarPantalla();
	printf("\n  \033[34m%c\033[35m%c%c%c  %c%c%c%c \033[34m%c\033[35m%c%c%c%c \033[34m%c\033[35m%c%c   \033[34m%c\033[35m%c \033[34m%c\033[35m%c   \033[34m%c\033[35m%c",219,219,219,220,220,219,219,219,219,219,219,219,219,219,219,220,219,219,219,219,219,219);
	printf("\n  \033[34m%c\033[35m%c\033[34m%c\033[45m%c   \033[35m\033[40m%c\033[34m%c\033[35m%c \033[34m%c\033[35m%c    \033[34m%c\033[35m%c\033[44m\033[35m%c%c\033[40m%c \033[34m%c\033[35m%c \033[34m%c\033[35m%c   \033[34m%c\033[35m%c",219,219,223,220,223,219,219,219,219,219,219,223,219,220,219,219,219,219,219,219);
	printf("\n  \033[34m%c\033[35m%c  \033[34m%c\033[35m%c  \033[34m%c\033[35m%c \033[34m%c\033[35m%c%c%c  \033[34m%c\033[35m%c \033[34m%c\033[45m%c\033[35m%c\033[34m%c\033[35m\033[40m%c \033[34m%c\033[35m%c   \033[34m%c\033[35m%c",219,219,223,223,219,219,219,219,219,219,219,219,223,220,219,223,219,219,219,219,219);
	printf("\n  \033[34m%c\033[35m%c      \033[34m%c\033[35m%c \033[34m%c\033[35m%c    \033[34m%c\033[35m%c   \033[34m%c\033[45m%c\033[40m\033[35m%c \033[34m%c\033[35m%c%c \033[34m%c\033[45m%c\033[40m\033[35m%c",219,219,219,219,219,219,219,219,223,220,219,219,219,220,220,223,219);
	printf("\n  \033[34m%c\033[35m%c      \033[34m%c\033[35m%c \033[34m%c\033[35m%c%c%c%c \033[34m%c\033[35m%c    \033[34m%c\033[35m%c \033[34m%c\033[45m%c\033[40m\033[35m%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,223,220,219,219,219,219,223);
	printf("\n\033[0m");
	printf("\n1. Cargar un archivo de definiciones");
	printf("\n2. Agregar una palabra y su definici%cn",162);
	printf("\n3. Buscar una palabra y ver su definici%cn",162);
	printf("\n4. Modificar una definici%cn",162);
	printf("\n5. Eliminar una palabra");
	printf("\n6. Ver estadisticas Hash",161);
	printf("\n7. Salir");
}

void CargarArchivo(lista milista, char *direccion)
{	
	BorrarPantalla();
	printf("\n   INTRODUZCA LA DIRECCI%cN\n    ",224); 
	scanf("%s", direccion);
	//printf("\n%s ",direccion);
	FILE * flujo = fopen(direccion, "rb");
	if(flujo == NULL)
	{
		perror("Error en la apertura del archivo");
		exit(1);
	}
	//BorrarPantalla();
	elemento e;
	char caracter = 'a';
	char p[101];
	char d[251];
	
	int i=0;
	int j;
	bool EsPalabra = true;
	
	while((int)caracter != -1)
	{
		caracter = fgetc(flujo);
		if(EsPalabra == true && (int)caracter != ':'){
			p[i] = caracter;
			i++;
		}
		else if (EsPalabra == false && (int)caracter != '\n' && (int)caracter != -1 && (int)caracter != 13){
			d[i] = caracter;
			i++;
		}
		if((int)caracter == ':'){
			for(j=0; j<i; j++)
				e.p[j] = p[j];
			EsPalabra = false;
			i=0;
		}
		else if((int)caracter == '\n' || (int)caracter == -1)
		{
			for(j=0; j<i; j++)
				e.d[j] = d[j];
			EsPalabra = true;
			Add(&milista,e);
			memset(p,0,101);
			memset(e.p,0,101);
			memset(d,0,251);
			memset(e.d,0,251);
			i=0;
		}
	}
	
	elemento e2;
	printf("\n   PALABRAS Y DEFINICIONES A%cADIDAS\n",165);
	for(i = 1; i <= Size(&milista); i++)
	{
		memset(e2.p,0,101);
		memset(e2.d,0,251);
		e2 = Element(&milista, i);
		printf("\n  \033[35m%s: \033[0m%s", e2.p, e2.d);
	}
	//e2 = Element(&milista, 4);
	//printf("\n e2.p = %s:%s", e2.p, e2.d);
	printf("\n\n   Presiona cualquier tecla para continuar\n");
	getch();
}

char Hash(char str[50])
{
	char convertido[50];
	
	return convertido;
}

int AsignarValor(char c)
{
	int x = 0;
	if(isdigit(c))
	{
		x = (int)c - 21;
	}
	else if(isalpha(c))
	{	
		c = toupper(c);
		x = (int)c - 64;
	}

	return x;
}

char RegresarValor(int n)
{
	char c = 'a';
	if (n<11)
	{
		c = (char)n+47;
	}
	else
	{
		c = (char)n-11+65;
	}
	return c;
}

void FrontMagenta()
{
	printf("\033[35m");
}

