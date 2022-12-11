# Proyecto 3: Simulaciones con el TAD cola

Enfocado en el uso de las colas para su uso en diferentes situaciones.
De manera didáctica se implementaron dos tipos de colas, una estática y otra dinámica. Estas fueron utilizadas para la simulación de un sistema de colas de un banco, de un supermercado y de un sistema operativo.

## Requisitos

Se utilizó para la compilación [GCC](https://gcc.gnu.org/) tanto en Windows como Linux.

Scripts para facilitar la compilación y ejecución fueron escritos en [Python](https://www.python.org/), así que se recomienda instalar una versión reciente de su interpretador.

### Windows

GCC está disponible a partir de la instalación de [MinGW](http://www.mingw.org/)

Python tiene su página de [descargas](https://www.python.org/downloads/)

### Linux

GCC se puede encontrar dentro del paquete `build-essential` en distribuciones de Debian. Instalándose con el comando:

```bash
sudo apt install build-essential
```

Y de forma similar están disponible un paquetes con python en muchas distribuciones:

```bash
sudo apt install python3
```

## Compilación

### Compilación por script

Para compilar los archivos se debe ejecutar el script  `compilar.py` desde la carpeta `/Simulaciones_con_el_TAD_cola/`. Dentro de este archivo se puede relacionar ya sea la implementación dinámica de las `colas`, o la estática (Nota: Además de cambiar el parámetro en el script hace falta incluirlo en el archivo de la simulación que se desea ejecutar)

En Windows:

```bash
python scripts/compilar.py
```

En Linux:

```bash
python ./scripts/compilar.py
```

El archivo quedan compilados dentro de una carpeta de binarios `/bin/`.

### Compilación desde la terminal

Dependiendo de la implementación de `colas` se enlaza el código fuente de la pila de la siguiente forma:

Para colas dinámicas (en Linux)

<!-- PENDIENTE -->

```bash

```

## Ejecución

Para ejecutar el algoritmo dentro de la terminal con diferentes ecuaciones como parámetro se utiliza de la forma:

<!-- PENDIENTE -->
En Windows:

```bash

```
<!-- PENDIENTE -->
En Linux:

```bash

```
