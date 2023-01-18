

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "TADTablaHash.h"
//#include "TADListaSL.h"

// Función de hash
int hash(char* str) {
  long hash = 5381;
  for (int i = 0; i < strlen(str); i++) {
    hash = ((hash * 33) + str[i]) % TAM_TABLA;
  }
  return (int)hash;
}

// Inicializa la tabla hash
void inicializarTablaHash(TablaHash *t)
{
    int i;
    /*for (i = 0; i < TAM_TABLA; i++)
    {
        Initialize(&t->arboles[i]);
        t->colisiones[i] = 0;
    }*/
    Initialize(&t->arboles[1]);
    t->colisiones[1] = 0;
    
    
    t->profundidad = 0;
    t->elementos = 0;
}

// Inserta un elemento en la tabla hash
void insertarTablaHash(TablaHash *t, elemento e)
{
    int pos = hash(e.p);
    // Si la lista no está vacía, se actualiza el valor de colisiones
    if (!Empty(&t->arboles[pos]))
        t->colisiones[pos]++;
	printf("\n P = %s\t D = %s",e.p,e.d);
    Add(&t->arboles[pos], e);
    // Se actualiza el valor de profundidad
    /*if (Size(&t->tabla[pos]) > t->profundidad)
        t->profundidad = Size(&t->tabla[pos]);
    t->elementos++;*/
}

// Modifica un elemento de la tabla hash
void modificarTablaHash(TablaHash *t, elemento e, int *comps)
{
    /*int pos = hash(e.p);
    posicion p = BuscarLlave(&t->tabla[pos], e.p, comps);
    if (p != NULL)
        Replace(&t->tabla[pos], p, e);*/
}

// Busca un elemento en la lista donde su clave es igual a la clave que se busca
// Retorna la posición del elemento encontrado o NULL si no se encuentra
posicion BuscarLlave(abb *a, char *clave, int *comps)
{
    /*posicion p = First(l);
    while (p != NULL)
    {
        printf("Comparando %s con %s\n", Position(l, p).p, clave);
        (*comps)++;
        if (strcmp(Position(l, p).p, clave) == 0)
            return p;
        p = Following(l, p);
    }
    return NULL;*/
}

// Busca un elemento en la tabla hash, retorna su posición o NULL si no se encuentra
elemento buscarTablaHash(TablaHash *t, char *clave, int *comps)
{
    /*int pos = hash(clave);
    posicion p = BuscarLlave(&t->tabla[pos], clave, comps);
    elemento e;

    if (p == NULL)
    {
        strcpy(e.p, "");
        strcpy(e.d, "");
    }
    else
        e = Position(&t->tabla[pos], p);

    return e;*/
}

// Elimina el elemento con la clave dada de la tabla hash
// Retorna TRUE si se eliminó el elemento, FALSE si no se encontró
bool eliminarTablaHash(TablaHash *t, char *clave, int *comps)
{
    /*int pos = hash(clave);
    posicion e = BuscarLlave(&t->tabla[pos], clave, comps);
    if (e == NULL)
        return false;

    Remove(&t->tabla[pos], e);
    t->elementos--;
    // Actualizar el valor de profundidad podría ser excesivamente costoso
    return true;*/
}

// Libera la memoria de la tabla hash
void liberarTablaHash(TablaHash *t)
{
    /*int i;
    for (i = 0; i < TAM_TABLA; i++)
    {
        Destroy(&t->tabla[i]);
        t->colisiones[i] = 0;
    }
    t->profundidad = 0;
    t->elementos = 0;*/
}

// Imprime la tabla hash
void imprimirTablaHash(TablaHash *t)
{
    int i;
    posicion p;

    for (i = 0; i < TAM_TABLA; i++)
    {
        printf("Arbol %d: ", i);
        /*p = First(&t->tabla[i]);
        while (p != NULL)
        {
            printf("%s, ", Position(&t->tabla[i], p).p);
            p = Following(&t->tabla[i], p);
        }*/
        RecorridoPreOrden(Root(&t->arboles[i]));
        printf("\n");
    }
}

void ImprimirPre(TablaHash *t)
{
	int i;
	
	for (i = 0; i < TAM_TABLA; i++)
    {
        printf("Arbol %d:\n", i);
        //RecorridoPreOrden(Root(&t->arboles[i]));
        VerLigas(&t->arboles[1]);
        printf("\n");
    }
    
    VerLigas(&t->arboles[1]);
}
