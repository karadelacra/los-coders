#!/bin/sh
# Un script de shell que compila todos los archivos .c en el directorio actual
# y los guarda en el directorio bin

# Variable de la carpeta de binarios
BIN_DIR=bin

# Crear el directorio de binarios
mkdir -p $BIN_DIR

# Compilar todos los archivos .c en el directorio actual y guardarlos en BIN_DIR
for f in *.c
do
    echo "Compilando $f"
    gcc -o $BIN_DIR/${f%.*} $f
done