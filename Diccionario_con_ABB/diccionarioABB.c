#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lib/TAD_ABB/TADABB.h"
#include "lib/presentacion.h"
/* PARA COMPILAR:
gcc -o diccionarioABB.exe diccionarioABB.c lib/TAD_ABB/TADABB.c lib/presentacionWin.c
*/
void cargarArchivo(abb *a);
void agregarPalabra(abb *a);
void buscarPalabra(abb *a);
void modificarPalabra(abb *a);
void eliminarPalabra(abb *a);
void recorridoPre(abb *a);
void recorridoIn(abb *a);
void recorridoPost(abb *a);
void verEstadisticas(abb *a);

void dibujarMenu();
void limpiarBuffer();

int main()
{
	int opcion;
	abb arbol;
	elemento e;
	posicion pos;
	Initialize(&arbol);
	
	while (1)
    {
        dibujarMenu();
        // Se pide la opci贸n al usuario
        printf("Opci贸n: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        // Se ejecuta la opci贸n seleccionada
        switch (opcion)
        {
        case 1:
            cargarArchivo(&arbol);
            break;
        case 2:
            agregarPalabra(&arbol);
            break;
        case 3:
            buscarPalabra(&arbol);
            break;
        case 4:
            modificarPalabra(&arbol);
            break;
        case 5:
            eliminarPalabra(&arbol);
            break;
        case 6:
            recorridoPre(&arbol);
            break;
        case 7:
            recorridoIn(&arbol);
            break;
        case 8:
            recorridoPost(&arbol);
            break;
        case 9:
            verEstadisticas(&arbol);
            break;
        case 10:
            printf("Saliendo...\n");
            //Destroy(&arbol);
            //VerLigas(&arbol);
            exit(0);
            break;
        default:
            printf("Opci贸n inv谩lida\n");
            break;
        }
        getchar();
    }
    
}
//1
void cargarArchivo(abb *a)
{
	BorrarPantalla();
	printf("\n\t\033[95m1. CARGAR UN ARCHIVO DE TEXTO.\033[0m");
	
	char direccion[256];
    elemento e;
    char caracter = 'a';
    char p[101];
    char d[251];
    int i = 0;
    int j, renglones = 0;
    bool EsPalabra = true;
	
    printf("\n\n    Introduzca la direcci%cn: ", 162);
    scanf("%s", direccion);
    FILE *flujo = fopen(direccion, "rb");
    if (flujo == NULL)
    {
        perror("\n\n   Error en la apertura del archivo.");
        exit(1);
    }
    printf("\n\n   Archivo cargado con %cxito.\n",130);

    while ((int)caracter != -1)
    {
        caracter = fgetc(flujo);
        if (EsPalabra == true && (int)caracter != ':')
        {
            p[i] = caracter;
            i++;
        }
        else if (EsPalabra == false && (int)caracter != '\n' && (int)caracter != -1 && (int)caracter != 13)
        {
            d[i] = caracter;
            i++;
        }
        if ((int)caracter == ':')
        {
            strncpy(e.p,p,101);
            EsPalabra = false;
            i = 0;
        }
        else if ((int)caracter == '\n' || (int)caracter == -1)
        {
            strncpy(e.d,d,101);
            EsPalabra = true;
            Add(a, e);
            memset(p, 0, 101);
            memset(e.p, 0, 101);
            memset(d, 0, 251);
            memset(e.d, 0, 251);
            //free(p);
            //free(d);
            //free(e);
            i = 0;
            renglones++;
        }
    }
    fclose(flujo);
    printf("\n\n   \033[95mSe cargaron %d palabras\033[0m\n", renglones);
    //printf("\n  Altura del arbol: %d", altura(Root(a)));
    printf("\n\n   Presiona cualquier tecla para continuar\n");
    getchar();
}
//2
void agregarPalabra(abb *a)
{
    BorrarPantalla();
	printf("\n\t\033[95m2. AGREGAR UNA PALABRA.\033[0m");
	
	char palabra[101];
    int modificar;
    int comps = 0;
    int i;
    elemento e;
    posicion p;

    printf("\n\n    Palabra a Agregar: ");
    scanf("%s", palabra);
	strcpy(e.p, palabra);
	p = Search(a, e);
    if (p != NULL)
    {
        printf("\nLa palabra \"%s\" ya existe\n", palabra);
        printf("Definici%cn: %s\n", 162, Element(a, p).d);
        printf("緿esea modificar la definici%cn? (1/0): ",162);
        scanf("%d", &modificar);
        if (modificar == 1)
        {
            printf("Nueva definici%cn: ",162);
            limpiarBuffer();
            fgets(e.d, 251, stdin);
            ReplaceDefinition(a, p, e.d);
            printf("\n\n   \033[95mSe reemplaz%c la definici%cn de \"%s\": %s\033[0m\n",162, 162, Element(a, p).p, Element(a,p).d );
        }
    }
    else
	{
    	printf("    Definici%cn: ",162);
    	limpiarBuffer();
    	fgets(e.d, 251, stdin);
    	Add(a, e);
    	//printf("\n  Altura del arbol: %d", altura(Root(a)));
    	printf("\n\n   \033[95mSe carg%c 1 palabra\033[0m\n", 162);
	}
	//getchar();
    //informacionBusqueda(t, lista, comps);
    
    printf("\n\n   Presiona cualquier tecla para continuar\n");
    //getchar();
}
//3
void buscarPalabra(abb *a)
{
	BorrarPantalla();
	printf("\n\t\033[95m3. BUSCAR UNA PALABRA.\033[0m");
	
	char palabra[101];
    int i;
    elemento e;
    posicion p;

    printf("\n\n    Palabra a buscar: ");
    scanf("%s", palabra);
    strcpy(e.p, palabra);
    p = Search(a, e);
    if (p != NULL)
    {
    	printf("\n   La palabra \"%s\" se encontr%c", palabra, 162);
        printf("\n   Definici%cn: %s\n", 162, Element(a, p).d);
    }
    else
    {
    	printf("\n\n   La palabra \"%s\" \033[31mNO\033[0m se encontr%c\n", palabra, 162);
	}
	printf("\n\n   Presiona cualquier tecla para continuar\n");
	getchar();
}
//4
void modificarPalabra(abb *a)
{
	BorrarPantalla();
	printf("\n\t\033[95m4. MODIFICAR UNA DEFINICI%cN.\033[0m",224);
	
	char palabra[101];
	elemento e;
    posicion p;

    printf("\n\n    Palabra a modificar: ");
    scanf("%s", palabra);
    strcpy(e.p, palabra);
    p = Search(a, e);
    if (p != NULL)
    {
    	printf("\nLa palabra \"%s\" se encontr%c\n", palabra, 162);
        printf("Definici%cn: %s\n", 162, Element(a, p).d);
        
        printf("\nNueva definici%cn: ", 162);
        limpiarBuffer();
        fgets(e.d, 251, stdin);
        ReplaceDefinition(a, p, e.d);
        printf("\n\n   \033[95mSe reemplaz%c la definici%cn de \"%s\": %s\033[0m\n",162, 162, Element(a, p).p, Element(a,p).d );
    }
    else
    {
    	printf("\n\n   La palabra \"%s\" \033[31mNO\033[0m se encontr%c\n", palabra, 162);
	}
	printf("\n\n   Presiona cualquier tecla para continuar\n");
	//getchar();
}
//5
void eliminarPalabra(abb *a)
{
	BorrarPantalla();
	printf("\n\t\033[95m5. ELIMINAR UNA PALABRA.\033[0m",224);
	
	char palabra[101];
	elemento e;
    posicion p;

    printf("\n\n    Palabra a eliminar: ");
    scanf("%s", palabra);
    strcpy(e.p, palabra);
    p = Search(a, e);
    if (p != NULL)
    {
    	Remove(a, p);
        printf("\n\n   \033[95mSe elimin%c la palabra \"%s\" exitosamente.\033[0m\n",162, palabra);
    }
    else
    {
    	printf("\n\n   La palabra \"%s\" \033[31mNO\033[0m se encontr%c\n", palabra, 162);
	}
	printf("\n\n   Presiona cualquier tecla para continuar\n");
	getchar();
}
//6
void recorridoPre(abb *a)
{
	BorrarPantalla();
	printf("\n\t\033[95m6. RECORRIDO PREORDEN.\033[0m");
	printf("\n\n  Recorrido: ");
	RecorridoPreOrden(Root(a));
}
//7
void recorridoIn(abb *a)
{
	BorrarPantalla();
	printf("\n\t\033[95m7. RECORRIDO INORDEN.\033[0m");
	printf("\n\n  Recorrido: ");
	RecorridoInOrden(Root(a));
}
//8
void recorridoPost(abb *a)
{
	BorrarPantalla();
	printf("\n\t\033[95m8. RECORRIDO POSTORDEN.\033[0m");
	printf("\n\n  Recorrido: ");
	RecorridoPosOrden(Root(a));
}
//9
void verEstadisticas(abb *a)
{
	BorrarPantalla();
	printf("\n\t\033[95m9. VER ESTAD%cSTICAS.\033[0m",214);
	VerLigas(a);
}



void dibujarMenu()
{
    BorrarPantalla();
	//system("clear");
    printf("\nDiccionario Hash con %crbol Binario de B%csqueda\n",181,233);
    printf("\n  \033[34m%c\033[35m%c%c%c  %c%c%c%c \033[34m%c\033[35m%c%c%c%c \033[34m%c\033[35m%c%c   \033[34m%c\033[35m%c \033[34m%c\033[35m%c   \033[34m%c\033[35m%c", 219, 219, 219, 220, 220, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 220, 219, 219, 219, 219, 219, 219);
    printf("\n  \033[34m%c\033[35m%c\033[34m%c\033[45m%c   \033[35m\033[40m%c\033[34m%c\033[35m%c \033[34m%c\033[35m%c    \033[34m%c\033[35m%c\033[44m\033[35m%c%c\033[40m%c \033[34m%c\033[35m%c \033[34m%c\033[35m%c   \033[34m%c\033[35m%c", 219, 219, 223, 220, 223, 219, 219, 219, 219, 219, 219, 223, 219, 220, 219, 219, 219, 219, 219, 219);
    printf("\n  \033[34m%c\033[35m%c  \033[34m%c\033[35m%c  \033[34m%c\033[35m%c \033[34m%c\033[35m%c%c%c  \033[34m%c\033[35m%c \033[34m%c\033[45m%c\033[35m%c\033[34m%c\033[35m\033[40m%c \033[34m%c\033[35m%c   \033[34m%c\033[35m%c", 219, 219, 223, 223, 219, 219, 219, 219, 219, 219, 219, 219, 223, 220, 219, 223, 219, 219, 219, 219, 219);
    printf("\n  \033[34m%c\033[35m%c      \033[34m%c\033[35m%c \033[34m%c\033[35m%c    \033[34m%c\033[35m%c   \033[34m%c\033[45m%c\033[40m\033[35m%c \033[34m%c\033[35m%c%c \033[34m%c\033[45m%c\033[40m\033[35m%c", 219, 219, 219, 219, 219, 219, 219, 219, 223, 220, 219, 219, 219, 220, 220, 223, 219);
    printf("\n  \033[34m%c\033[35m%c      \033[34m%c\033[35m%c \033[34m%c\033[35m%c%c%c%c \033[34m%c\033[35m%c    \033[34m%c\033[35m%c \033[34m%c\033[45m%c\033[40m\033[35m%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 223, 220, 219, 219, 219, 219, 223);
    printf("\n\033[0m\n");
    printf("1. Cargar un archivo de texto\n");
    printf("2. Agregar una palabra\n");
    printf("3. Buscar una palabra\n");
    printf("4. Modificar una definici%cn\n",162);
    printf("5. Eliminar una palabra\n");
    printf("6. Recorrido PreOrden\n");
    printf("7. Recorrido InOrden\n");
    printf("8. Recorrido PostOrden\n");
    printf("9. Ver estad铆sticas\n");
    printf("10. Salir\n\n");
}

// Funci髇 para limpiar el Buffer
void limpiarBuffer()
{
    int temp;
    while ((temp = getchar()) != '\n' && temp != EOF);
}

