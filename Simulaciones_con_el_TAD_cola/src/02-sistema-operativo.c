/*
02-sistema-operativo.c
V 1.0 Diciembre 2022
Autores:
    Juan Luis Molina
    Karel Román Padilla
    Danna Lizbeth Matías
    Darío Quiñones

Realiza la simulación de la ejecución de procesos en un sistema
operativo de un solo procesador.

A partir de una lista fija de procesos a realizar, el sistema
operativo progresa en la ejecución de los procesos de acuerdo
a cómo estén encolados.

Después de terminar la tarea de un proceso, el sistema operativo
lo elimina de la cola de procesos y lo agrega a la cola de
procesos terminados.

Se compila de la forma:
    (Linux)
    gcc -o 02-sistema-operativo 02-sistema-operativo.c ../lib/TAD_Cola/TADColaEst.c ../lib/presentacionLin.c
    (Windows)
    gcc -o 02-sistema-operativo 02-sistema-operativo.c ../lib/TAD_Cola/TADColaEst.c ../lib/presentacionWin.c

Se ejecuta de la forma:
    ./02-sistema-operativo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include <stdbool.h>
#include "../lib/TAD_Cola/TADColaEst.h"
#include "../lib/presentacion.h"

#define INTERVALO_BASE 1000
#define PROCESOS_INICIALES 5

/* Estructura de un proceso
    * nombre: Nombre del proceso
    * actividad: Actividad que realiza el proceso
    * ID: Identificador único del proceso
    * tiempo: Tiempo que tarda el proceso en realizar su actividad
    * tiempo_restante: Tiempo que le falta al proceso para terminar su actividad
    * inicio: Tiempo en el que el proceso inició su actividad
    * fin: Tiempo en el que el proceso terminó su actividad
*/
typedef struct proceso{
    char nombre[45];
    char actividad[200];
    char ID[45];
    int tiempo;
    int tiempo_restante;
    time_t inicio;
    time_t fin;
} proceso;

proceso *ProcesoPseudoaleatorio(int procesos_totales);

int main() {
    int i, tiempo = 0, procesos_totales = 0;
    cola procesos, procesos_terminados;
    proceso *p;
    elemento e;

    // Inicializar semilla de números aleatorios
    srand((unsigned) 1);

    Initialize(&procesos);
    Initialize(&procesos_terminados);

    // Crear procesos iniciales
    for (i = 0; i < PROCESOS_INICIALES; i++) {
        p = ProcesoPseudoaleatorio(procesos_totales);
        printf("Proceso %d: %s", i, p->nombre);
        printf(" (%s)", p->ID);
        printf(" - %s", p->actividad);
        printf(" - Tiempo restante: %d\n", p->tiempo_restante);
        procesos_totales++;
        e.p = p;
        Queue(&procesos, e);
    }

    // Realizar simulación
    while (!Empty(&procesos))
    {
        EsperarMiliSeg(INTERVALO_BASE);

        e = Dequeue(&procesos);
        p = (proceso *)e.p;
        p->tiempo_restante--;
        if (p->tiempo_restante == 0) {
            printf("Proceso %s %s terminado\n", p->ID, p->nombre);
            time(&p->fin);
            e.p = p;
            Queue(&procesos_terminados, e);
        } else {
            printf("Proceso %s (%s): %d\n", p->ID, p->nombre, p->tiempo_restante);
            e.p = p;
            Queue(&procesos, e);
        }
        tiempo++;
    }

    // Imprimir procesos terminados
    printf("Procesos terminados:\n");
    while (!Empty(&procesos_terminados))
    {
        e = Dequeue(&procesos_terminados);
        p = (proceso *)e.p;
        printf("Proceso %s: %s", p->ID, p->nombre);
        printf(" - %s", p->actividad);
        printf(" - Tiempo requerido: %dseg\n", (int)(p->fin - p->inicio));
        free(p);
    }

    return 0;
}

/* proceso ProcesoAleatorio(procesos_totales)
Recibe:
    procesos_totales: el número de procesos totales que se han creado
Retorna un puntero al proceso mallocado

Crea un proceso a partir de un grupo de nombres y actividades predefinidas.
*/
proceso *ProcesoPseudoaleatorio(int procesos_totales) {
    proceso *nuevo_proceso;
    char nombres[15][45] = {
        "Microsoft Word",
        "Microsoft Excel",
        "Microsoft PowerPoint",
        "Task Manager",
        "Google Chrome",
        "Mozilla Firefox",
        "Microsoft Edge",
        "Discord",
        "Spotify",
        "Visual Studio Code",
        "Command Prompt",
        "Adobe Photoshop",
        "Avast Antivirus",
        "Paint",
        "Windows Explorer"
    },
    actividades[15][200] = {
        "Procesando texto enriquecido",
        "Procesando gráficos financieros",
        "Renderizando presentación multimedia",
        "Detectando procesos en ejecución",
        "Cargando página web",
        "Cargando página web",
        "Descargando Google Chrome",
        "Recibiendo mensajes y llamadas",
        "Reproduciendo streaming de audio",
        "Ejecutando código fuente",
        "El comando 'cls' no se reconoce como un comando interno o externo",
        "Editando imagen con filtros",
        "Escaneando archivos",
        "Dibujando formas básicas",
        "Cargando archivos"
    };
    int rand_val;

    nuevo_proceso = (proceso *) malloc(sizeof(proceso));

    rand_val = rand() % 15;
    strcpy(nuevo_proceso->nombre, nombres[rand_val]);
    strcpy(nuevo_proceso->actividad, actividades[rand_val]);
    sprintf(nuevo_proceso->ID, "%03d%c%d", procesos_totales, nombres[rand_val][0], rand() % 10);

    nuevo_proceso->tiempo_restante = rand() % 20 + rand() % 20 + 5;
    nuevo_proceso->tiempo = nuevo_proceso->tiempo_restante;

    time(&nuevo_proceso->inicio);

    return nuevo_proceso;
}