/*
diccionario.c
V 1.0 Enero 2023
Autores:
    Juan Luis Molina
    Karel Román Padilla
    Danna Lizbeth Matías
    Darío Quiñones

Con base a una tabla de Hash, implementa un diccionario de palabras, donde
se puede agregar, eliminar, buscar y mostrar el contenido del diccionario.

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
#include "./lib/TADTablaHash.h"
#include "./lib/TADListaSL.h"

void dibujarMenu();
void cargarArchivo(TablaHash *t);
void agregarPalabra(TablaHash *t);
void buscarPalabra(TablaHash *t);
void modificarPalabra(TablaHash *t);
void eliminarPalabra(TablaHash *t);
void verEstadisticas(TablaHash *t);
void informacionBusqueda(TablaHash *t, int lista, int comps);
void limpiarBuffer();
bool elementoVacio(elemento e);

int main()
{
    int opcion;
    char palabra[101];
    TablaHash t;

    // Se inicializa la tabla hash
    inicializarTablaHash(&t);

    // Comienza el loop principal del programa
    while (1)
    {
        dibujarMenu();
        // Se pide la opción al usuario
        printf("Opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        // Se ejecuta la opción seleccionada
        switch (opcion)
        {
        case 1:
            cargarArchivo(&t);
            break;
        case 2:
            agregarPalabra(&t);
            break;
        case 3:
            buscarPalabra(&t);
            break;
        case 4:
            modificarPalabra(&t);
            break;
        case 5:
            eliminarPalabra(&t);
            break;
        case 6:
            verEstadisticas(&t);
            break;
        case 7:
            printf("Saliendo...\n");
            exit(0);
            break;
        default:
            printf("Opción inválida\n");
            break;
        }
        getchar();
    }
}

void dibujarMenu()
{
    system("clear");
    printf("\nDiccionario Hash\n\n");
    printf("\n  \033[34m%c\033[35m%c%c%c  %c%c%c%c \033[34m%c\033[35m%c%c%c%c \033[34m%c\033[35m%c%c   \033[34m%c\033[35m%c \033[34m%c\033[35m%c   \033[34m%c\033[35m%c", 219, 219, 219, 220, 220, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 220, 219, 219, 219, 219, 219, 219);
    printf("\n  \033[34m%c\033[35m%c\033[34m%c\033[45m%c   \033[35m\033[40m%c\033[34m%c\033[35m%c \033[34m%c\033[35m%c    \033[34m%c\033[35m%c\033[44m\033[35m%c%c\033[40m%c \033[34m%c\033[35m%c \033[34m%c\033[35m%c   \033[34m%c\033[35m%c", 219, 219, 223, 220, 223, 219, 219, 219, 219, 219, 219, 223, 219, 220, 219, 219, 219, 219, 219, 219);
    printf("\n  \033[34m%c\033[35m%c  \033[34m%c\033[35m%c  \033[34m%c\033[35m%c \033[34m%c\033[35m%c%c%c  \033[34m%c\033[35m%c \033[34m%c\033[45m%c\033[35m%c\033[34m%c\033[35m\033[40m%c \033[34m%c\033[35m%c   \033[34m%c\033[35m%c", 219, 219, 223, 223, 219, 219, 219, 219, 219, 219, 219, 219, 223, 220, 219, 223, 219, 219, 219, 219, 219);
    printf("\n  \033[34m%c\033[35m%c      \033[34m%c\033[35m%c \033[34m%c\033[35m%c    \033[34m%c\033[35m%c   \033[34m%c\033[45m%c\033[40m\033[35m%c \033[34m%c\033[35m%c%c \033[34m%c\033[45m%c\033[40m\033[35m%c", 219, 219, 219, 219, 219, 219, 219, 219, 223, 220, 219, 219, 219, 220, 220, 223, 219);
    printf("\n  \033[34m%c\033[35m%c      \033[34m%c\033[35m%c \033[34m%c\033[35m%c%c%c%c \033[34m%c\033[35m%c    \033[34m%c\033[35m%c \033[34m%c\033[45m%c\033[40m\033[35m%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 223, 220, 219, 219, 219, 219, 223);
    printf("\n\033[0m");
    printf("1. Cargar un archivo de texto\n");
    printf("2. Agregar una palabra\n");
    printf("3. Buscar una palabra\n");
    printf("4. Modificar una palabra\n");
    printf("5. Eliminar una palabra\n");
    printf("6. Ver estadísticas\n");
    printf("7. Salir\n\n");
}

void cargarArchivo(TablaHash *t)
{
    char direccion[256];
    elemento e;
    char caracter = 'a';
    char p[101];
    char d[251];

    int i = 0;
    int j, renglones = 0;
    bool EsPalabra = true;

    printf("\tINTRODUZCA LA DIRECCIÓN\t", 224);
    scanf("%s", direccion);
    // printf("\n%s ",direccion);
    FILE *flujo = fopen(direccion, "rb");
    if (flujo == NULL)
    {
        perror("Error en la apertura del archivo");
        exit(1);
    }
    printf("Archivo cargado con éxito\n");

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
            for (j = 0; j < i; j++)
                e.p[j] = p[j];
            EsPalabra = false;
            i = 0;
        }
        else if ((int)caracter == '\n' || (int)caracter == -1)
        {
            for (j = 0; j < i; j++)
                e.d[j] = d[j];
            EsPalabra = true;
            insertarTablaHash(t, e);
            memset(p, 0, 101);
            memset(e.p, 0, 101);
            memset(d, 0, 251);
            memset(e.d, 0, 251);
            i = 0;
            renglones++;
        }
    }
    fclose(flujo);
    printf("Se cargaron %d palabras\n", renglones);
    printf("\n\n   Presiona cualquier tecla para continuar\n");
    getchar();
}


void agregarPalabra(TablaHash *t)
{
    char palabra[101];
    char modificar;
    int lista;
    int comps = 0;
    elemento e;

    printf("Palabra a Agregar: ");
    scanf("%s", palabra);

    e = buscarTablaHash(t, palabra, &comps);
    lista = hash(palabra);

    if (!elementoVacio(e))
    {
        printf("La palabra %s ya existe\n", palabra);
        printf("Definición: %s\n", e.d);
        printf("¿Desea modificar la definición? (s/n): ");
        scanf("%c", &modificar);
        if (modificar == 's')
        {
            printf("Nueva definición: ");
            limpiarBuffer();
            fgets(e.d, 251, stdin);
            modificarTablaHash(t, e, &comps);

            informacionBusqueda(t, lista, comps);
        }
        return;
    }

    strcpy(e.p, palabra);
    printf("Definición: ");
    limpiarBuffer();
    fgets(e.d, 251, stdin);

    insertarTablaHash(t, e);

    informacionBusqueda(t, lista, comps);
}

void buscarPalabra(TablaHash *t)
{
    char palabra[101];
    elemento e;
    int comps = 0;

    printf("Palabra a buscar: ");
    scanf("%s", palabra);

    e = buscarTablaHash(t, palabra, &comps);

    if (elementoVacio(e))
        printf("Palabra no encontrada\n");
    else
        printf("Definición: %s\n", e.d);

    informacionBusqueda(t, hash(palabra), comps);
    getchar();
}

void modificarPalabra(TablaHash *t)
{
    char palabra[101];
    elemento e;
    int comps = 0;

    printf("Modificar: ");
    scanf("%s", palabra);

    e = buscarTablaHash(t, palabra, &comps);

    if (elementoVacio(e))
        printf("Palabra no encontrada\n");
    else
    {
        printf("Definición: %s\n", e.d);
        printf("Nueva definición: ");
        limpiarBuffer();
        fgets(e.d, 251, stdin);
        modificarTablaHash(t, e, &comps);
    }

    printf("Palabra modificada en la lista %d\n", hash(palabra));
    printf("Después de hacer %d comparaciones\n", comps);
}

void eliminarPalabra(TablaHash *t)
{
    char palabra[101];
    elemento e;
    int comps = 0;

    printf("Eliminar: ");
    scanf("%s", palabra);

    e = buscarTablaHash(t, palabra, &comps);

    if (elementoVacio(e))
        printf("Palabra no encontrada\n");
    else
        eliminarTablaHash(t, palabra, &comps);
    printf("Palabra eliminada\n");

    printf("Palabra eliminada en la lista %d\n", hash(palabra));
    printf("Después de hacer %d comparaciones\n", comps);
    getchar();
}

void verEstadisticas(TablaHash *t)
{
    char imprimir;
    int i, max = 0, min = 0;
    printf("Estadísticas\n");
    printf("Elementos en la tabla: %d\n", t->elementos);

    // Maximo y minimo de colisiones
    min = t->colisiones[0];
    for (i = 0; i < TAM_TABLA; i++)
    {
        if (t->colisiones[i] > max)
            max = t->colisiones[i];
        if (t->colisiones[i] < min)
            min = t->colisiones[i];
    }
    printf("Número de colisiones desde %d hasta %d\n[", min, max);
    for (i = 0; i < TAM_TABLA - 1; i++)
        printf("%d, ", t->colisiones[i]);
    printf("%d]\n", t->colisiones[TAM_TABLA - 1]);

    printf("Profundidad Máxima: %d\n", t->profundidad);

    printf("¿Desea imprimir la tabla? (s/n): ");
    scanf("%c", &imprimir);
    if (imprimir == 's')
        imprimirTablaHash(t);
        getchar();
}

void informacionBusqueda(TablaHash *t, int lista, int comps)
{
    printf("En la lista %d ", lista);
    printf("detrás de %d palabra(s) ", Size(&(t->tabla[lista])) - 1);
    printf("tras %d comparaciones\n", comps);
}

// Función para limpiar el buffer
void limpiarBuffer()
{
    int temp;
    while ((temp = getchar()) != '\n' && temp != EOF);
}

// Función para verificar si un elemento está vacío
bool elementoVacio(elemento e)
{
    if (strcmp(e.p, "") == 0 && strcmp(e.d, "") == 0)
        return true;
    return false;
}