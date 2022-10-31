# Proyecto 1: Algoritmos de Ordenamiento

Centrado en seis diferentes algoritmos de ordenamiento comunes. Cada algoritmo esta contenido en su propio archivo independiente, para facilitar su uso están presentes scripts para el compilado y la ejecución de los archivos.

## Requisitos

Se utilizó para la compilación [GCC](https://gcc.gnu.org/) tanto en Windows como Linux.

### Windows

GCC está disponible a partir de la instalación de [MinGW](http://www.mingw.org/)

### Linux

GCC se puede encontrar dentro del paquete `build-essential` en distribuciones de Debian. Instalándose con el comando:

```bash
sudo apt install build-essential
```

## Compilación

Para compilar los archivos se debe ejecutar el script  `compilar.bat` o `compile.sh` desde la carpeta `/Algoritmos_de_Ordenamiento/`.

En Windows:

```bash
scripts/compilar.bat
```

En Linux:

```bash
bash ./scripts/compilar.sh
```

Los archivos quedan compilados dentro de una carpeta de binarios `/bin/`.

## Ejecución

Hay dos scripts para el uso de los algoritmos, ambos asumen que el proyecto tiene un set de números aleatorios con el nombre de `numeros1M.txt` en la carpeta del proyecto.

Para ejecutar todos los algoritmos secuencialmente con un set de 100 valores numéricos tomados del archivo se debe ejecutar el script `ejecutar.sh` desde la raíz del proyecto.

En Windows:

```bash
scripts/ejecutar.bat
```

En Linux:

```bash
bash ./scripts/ejecutar.sh
```

Los resultados quedan guardados dentro de la carpeta `/out/`

### Recolección de datos (Work In Progress)

Para recolectar los datos de cada algoritmo individualmente se utiliza el script para guardar los tiempos del algoritmo dado con intervalos progresivamente mayores de números.

## Algoritmos (Work In Progress)

(Descripciones breves)

### Bubble Sort

### Insertion Sort

### Selection Sort

### Merge Sort

### Quick Sort

### Shell Sort
