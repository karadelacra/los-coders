#!/bin/sh
# compilar.sh
# Version 1.0 Octubre 2022
# Autor: Darío Quiñones

# Un script de shell que compila todos los archivos .c en el directorio actual
# y los guarda en el directorio bin

# Variable de la carpeta de binarios
BIN_DIR=bin

# Crear el directorio de binarios
mkdir -p $BIN_DIR

# Compilar todos los archivos .c en el directorio actual y guardarlos en BIN_DIR
for f in *.c
do
    # Si el archivo no está ya en el directorio de binarios, compilarlo
    if [ ! -f $BIN_DIR/${f%.*} ]; then
        echo "Compilando $f"
        gcc -o $BIN_DIR/${f%.*} $f
    fi
done