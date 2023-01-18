#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lib/TAD_ABB/TADABB.h"
#include "lib/presentacion.h"
/*
PARA COMPILAR
gcc -o prueba.exe prueba.c lib/TAD_ABB/TADABB.c lib/presentacionWin.c

gcc -o prueba.exe prueba.c lib/TAD_ABB/TADABB.c lib/presentacionWin.c
*/
int main()
{
	abb arbol;
	elemento e;
	posicion pos;
	
	BorrarPantalla();
	Initialize(&arbol);
	/*
	strncpy(e.p, "N", 101);
	strncpy(e.d, "ene", 251);
	Add(&arbol, e);
	
	strncpy(e.p, "E", 101);
	strncpy(e.d, "e", 251);
	Add(&arbol, e);
	
	strncpy(e.p, "S", 101);
	strncpy(e.d, "ese", 251);
	Add(&arbol, e);
	
	strncpy(e.p, "D", 101);
	strncpy(e.d, "de", 251);
	Add(&arbol, e);
	
	strncpy(e.p, "K", 101);
	strncpy(e.d, "ca", 251);
	Add(&arbol, e);
	
	strncpy(e.p, "R", 101);
	strncpy(e.d, "erre", 251);
	Add(&arbol, e);
	
	strncpy(e.p, "W", 101);
	strncpy(e.d, "doble u", 251);
	Add(&arbol, e);
	
	strncpy(e.p, "B", 101);
	strncpy(e.d, "be", 251);
	Add(&arbol, e);
	
	strncpy(e.p, "H", 101);
	strncpy(e.d, "ache", 251);
	Add(&arbol, e);
	
	strncpy(e.p, "M", 101);
	strncpy(e.d, "eme", 251);
	Add(&arbol, e);
	
	strncpy(e.p, "Q", 101);
	strncpy(e.d, "cu", 251);
	Add(&arbol, e);
	
	strncpy(e.p, "V", 101);
	strncpy(e.d, "uve", 251);
	Add(&arbol, e);
	
	strncpy(e.p, "T", 101);
	strncpy(e.d, "te", 251);
	Add(&arbol, e);
	
	strncpy(e.p, "Q", 101);
	strncpy(e.d, "cu", 251);
	Add(&arbol, e);
	*/
	VerLigas(&arbol);
	
	strncpy(e.p, "D", 101);
	printf("\n\nSEARCH: %d\n", Search(&arbol,e));
	if(NullNode(&arbol,Search(&arbol,e)) == false)
	{
		printf("\n\nLa Posicion %d si se encuentra en el arbol", Search(&arbol,e));
	}
	else
	{
		printf("\n\nLa Posicion %d NO se encuentra en el arbol", Search(&arbol,e));
	}
	
}
