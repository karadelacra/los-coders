# Proyecto 2: Expresiones Infijas

Enfocado en el uso de las pilas dinámicas y estáticas para la evaluación de expresiones aritméticas. El programa utiliza pilas para corroborar la utilización de paréntesis, para la conversión de una expresión infija, a una postfija, y para evaluar la expresión.

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

Para compilar los archivos se debe ejecutar el script  `compilar.py` desde la carpeta `/Expresiones_Infijas/`. Dentro de este archivo se puede relacionar ya sea la implementación dinámica de las `pilas`, o la estática (Nota: Además de cambiar el parámetro en el script hace falta incluirlo en `main.c`)

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

Dependiendo de la implementación de `pilas` se enlaza el código fuente de la pila de la siguiente forma:

Para pilas dinámicas (en Linux)

```bash
gcc -o output main.c pilas/pila-dinamica.c
```

## Ejecución

Para ejecutar el algoritmo dentro de la terminal con diferentes ecuaciones como parámetro se utiliza de la forma:

En Windows:

```bash
bin/Expresiones_Infijas.exe "A+B"
```

En Linux:

```bash
./bin/Expresiones_Infijas "A+B"
```

Durante el desarrollo se utilizó el script de Python `/scripts/ejecutar.py` con una serie de ecuaciones de referencia.
