/*
01-supermercado.c
V 1.0 Diciembre 2022
Autores:
    Juan Luis Molina
    Karel Román Padilla
    Danna Lizbeth Matías
    Darío Quiñones

Realiza la simulación de un supermercado con una cola de clientes.

* Al inicio de la simulación no hay clientes en ninguna caja.
* El número de cajas de la simulación puede ser un entero del 1 al 10,
* Cada cliente tiene un identificador único.
* Una vez que ya se atendieron a más de 100 clientes y no hay gente
esperando, el supermercado cierra.
* Mientras el supermercado esté
abierto los clientes llegan en intervalos de tiempo constantes.

Se imprimen las cajas y los clientes que están en cada una de ellas
durante la simulación.

Se compila de la forma:
    (Linux)
    gcc -o 01-supermercado 01-supermercado.c ../lib/TAD_Cola/TADColaEst.c ../lib/presentacionLin.c
    (Windows)
    gcc -o 01-supermercado 01-supermercado.c ../lib/TAD_Cola/TADColaEst.c ../lib/presentacionWin.c

Se ejecuta de la forma:
    ./01-supermercado
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../lib/TAD_Cola/TADColaEst.h"
#include "../lib/presentacion.h"

#define MAX_CAJAS 10
#define MAX_CLIENTES 100
#define INTERVALO_BASE 10

void EscanearDatos(int *num_cajas, int *tiempo_atencion, int *intervalo_llegada);
void LlegadaCliente(cola *cajas, int num_cajas, int *clientes_totales);
void DibujarSuper(cola *cajas, int num_cajas, char *nombre_supermercado);
void DibujarClientes(cola *caja, int num_caja);

int main()
{
    int i, num_cajas, *tiempo_atencion, intervalo_llegada,
        tiempo = 0, clientes_atendidos = 0, clientes_totales = 0;
    bool super_vacio = false;
    cola *cajas;
    char nombre_supermercado[50];

    // Escanear nombre del supermercado
    printf("Nombre del supermercado: ");
    scanf("%s", nombre_supermercado);

    // Escanear número de cajas
    printf("Numero de cajas: ");
    scanf("%d", &num_cajas);
    if (num_cajas > MAX_CAJAS)
    {
        printf("El numero de cajas no puede ser mayor a %d\n", MAX_CAJAS);
        exit(1);
    }
    else if (num_cajas < 1)
    {
        printf("El numero de cajas no puede ser menor a 1\n");
        exit(1);
    }

    // Asignar memoria para los tiempos de atención
    tiempo_atencion = (int *)malloc(num_cajas * sizeof(int));
    if (tiempo_atencion == NULL)
    {
        printf("No se pudo asignar memoria\n");
        exit(1);
    }

    // Escanear el resto de los datos
    EscanearDatos(&num_cajas, tiempo_atencion, &intervalo_llegada);

    // Inicializar cajas
    cajas = (cola *)malloc(num_cajas * sizeof(cola));
    if (cajas == NULL)
    {
        printf("Error al asignar memoria para las cajas");
        exit(1);
    }
    for (i = 0; i < num_cajas; i++)
        Initialize(&cajas[i]);

    // Dibujar supermercado
    DibujarSuper(cajas, num_cajas, nombre_supermercado);

    // Comenzar simulación
    while (clientes_atendidos < 100 || !super_vacio)
    {
        // Incrementar tiempo
        EsperarMiliSeg(INTERVALO_BASE * 10);
        tiempo++;
        MoverCursor(strlen(nombre_supermercado) + 5, 2);
        printf(" Clientes Atendidos: %d\n", clientes_atendidos);

        // Atender clientes
        for (i = 0; i < num_cajas; i++)
            if (tiempo % tiempo_atencion[i] == 0 && !Empty(&cajas[i]))
            {
                // printf("Caja %d atendio al cliente %d\n", i + 1, Dequeue(&cajas[i]).n);
                Dequeue(&cajas[i]);
                DibujarClientes(&cajas[i], i);
                clientes_atendidos++;
            }

        // Llegada de clientes
        if (tiempo % intervalo_llegada == 0)
            LlegadaCliente(cajas, num_cajas, &clientes_totales);

        // Verificar si el supermercado está vacío
        super_vacio = true;
        for (i = 0; i < num_cajas; i++)
            if (!Empty(&cajas[i]))
                super_vacio = false;
    }
    MoverCursor(1, 17);
    printf("%s cerro, despues de atender a %d clientes\n", nombre_supermercado, clientes_atendidos);
    printf("Tiempo total: %d\n", tiempo);
    return 0;
}

/* void EscanearDatos(int *num_cajas, int *tiempo_atencion, int *intervalo_llegada)
Recibe:
    - num_cajas: puntero a entero donde se guardará el número de cajas
    - tiempo_atencion: puntero a arreglo de enteros donde se guardará el tiempo de atención de cada caja
    - intervalo_llegada: puntero a entero donde se guardará el intervalo de llegada de clientes

Asigna los valores escaneados a las variables recibidas
Saldrá del programa si:
    - El número de cajas es mayor a MAX_CAJAS
    - El número de cajas es menor a 1
    - El tiempo de atención de alguna caja o el intervalo de llegada de los
    clientes no es un múltiplo de INTERVALO_BASE
*/
void EscanearDatos(int *num_cajas, int *tiempo_atencion, int *intervalo_llegada)
{
    int i;
    // Escanear tiempo de atención de cada caja
    for (i = 0; i < *num_cajas; i++)
    {
        printf("Tiempo de atencion de la caja %d: ", i + 1);
        scanf("%d", &tiempo_atencion[i]);
        if (tiempo_atencion[i] < 10)
        {
            printf("El tiempo de atencion de la caja %d no puede ser menor a %d\n", i + 1, INTERVALO_BASE);
            exit(1);
        }
        else if (tiempo_atencion[i] % INTERVALO_BASE != 0)
        {
            printf("El tiempo de atencion de la caja %d no es multiplo de %d\n", i + 1, INTERVALO_BASE);
            exit(1);
        }
        tiempo_atencion[i] /= INTERVALO_BASE;
    }
    // Escanear tiempo de llegada de clientes
    printf("Tiempo de llegada de clientes: ");
    scanf("%d", intervalo_llegada);
    if (*intervalo_llegada < 10)
    {
        printf("El tiempo de llegada de clientes no puede ser menor a %d\n", INTERVALO_BASE);
        exit(1);
    }
    else if (*intervalo_llegada % INTERVALO_BASE != 0)
    {
        printf("El tiempo de llegada de clientes no es multiplo de %d\n", INTERVALO_BASE);
        exit(1);
    }
    *intervalo_llegada /= INTERVALO_BASE;
}

/* void LlegadaCliente(caja *cajas, int num_cajas, int *clientes_totales)
Recibe:
    cajas: Arreglo de cajas del supermercado
    num_cajas: Número de cajas del supermercado
    clientes_totales: Número de clientes que hayan llegado al supermercado

Asigna un nuevo cliente a una caja aleatoria y lo agrega a la cola de clientes de la caja.

Pero se guardan por orden de prioridad en el arreglo intervalos_llegada.*/
void LlegadaCliente(cola *cajas, int num_cajas, int *clientes_totales)
{
    int i, caja_elegida;
    elemento nuevo_cliente;
    // Elegir caja aleatoria
    caja_elegida = rand() % num_cajas;
    // Asignar nuevo cliente
    ++(*clientes_totales);
    nuevo_cliente.n = *clientes_totales;

    // Agregar cliente a la cola de la caja
    Queue(&cajas[caja_elegida], nuevo_cliente);
    DibujarClientes(&cajas[caja_elegida], caja_elegida);
}

/* void ImprimirConMarco(char *cadena)
Recibe:
    cadena: Cadena de caracteres a imprimir

Imprime la cadena de caracteres recibida con un marco alrededor
*/
void ImprimirConMarco(int pos_x, int pos_y, char *cadena)
{
    int i, ancho = strlen(cadena) + 4 - 1;
    MoverCursor(pos_x, pos_y);
    printf("%c", 201);
    for (i = 0; i < ancho; i++)
        printf("%c", 205);
    printf("%c", 187);
    MoverCursor(pos_x, pos_y + 1);
    printf("%c", 186);
    printf(" %s ", cadena);
    printf("%c", 186);
    MoverCursor(pos_x, pos_y + 2);
    printf("%c", 200);
    for (i = 0; i < ancho; i++)
        printf("%c", 205);
    printf("%c", 188);
}

/* void DibujarSuper(cola *cajas, int num_cajas , char *nombre_supermercado)
Recibe:
    cajas: Arreglo de cajas del supermercado
    num_cajas: Número de cajas del supermercado
    nombre_supermercado: Nombre del supermercado

Imprime la parte estática del supermercado, es decir, los barandales y los recuadros de las cajas.
*/
void DibujarSuper(cola *cajas, int num_cajas, char *nombre_supermercado)
{
    int i, j;
    int ancho_caja = 10, margen = 2, ancho_fila = 5;
    int pos_x;
    char buffer[20];

    BorrarPantalla();
    // Imprimir el nombre del supermercado con un borde bonito
    ImprimirConMarco(1, 1, nombre_supermercado);

    for (i = 0; i < num_cajas; i++)
    {
        pos_x = i * (ancho_caja + ancho_fila) + margen + 1;
        // Primero los barandales
        for (j = 0; j < 15; j++)
        {
            MoverCursor(pos_x + ancho_caja - 1, margen + 6 + j);
            printf("|     |");
        }
        // Ahora los recuadros
        sprintf(buffer, "Caja %d", i + 1);
        ImprimirConMarco(pos_x, margen + 3, buffer);
    }
}

/* void DibujarClientes(cola *caja, int n_caja)
Recibe:
    caja: Puntero a una cola de clientes
    n_caja: Número de la caja (a partir de 0)

Re-imprime la cola de clientes de la caja recibida.
*/
void DibujarClientes(cola *caja, int n_caja)
{
    int i, pos_x, pos_y;
    elemento cliente;

    // Asumiendo que acaba de haber un cambio en la cola
    // Borrar el cliente que estaba en la última posición
    pos_x = (n_caja + 1) * (10 + 5) - 1;
    pos_y = 5 + Size(caja);
    MoverCursor(pos_x, pos_y + 1);
    printf("    ");
    MoverCursor(pos_x, pos_y + 2);
    printf("    ");

    for (i = 1; i <= Size(caja); i++)
    {
        pos_y = 5 + i;
        MoverCursor(pos_x, pos_y);
        if (i >= 20)
        {
            MoverCursor(pos_x, pos_y - 1);
            printf("... ");
            MoverCursor(pos_x, pos_y);
            cliente = Final(caja);
            // Recortar los números grandes
            printf("%d", cliente.n);
            break;
        }
        cliente = Element(caja, i);
        printf("%d", cliente.n);
    }
}