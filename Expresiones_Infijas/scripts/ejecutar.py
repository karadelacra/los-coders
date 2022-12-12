# compilar.py
# Version 1.0 22 de Noviembre 2022
# Autores: Darío Quiñones, Karel R. Padilla
#
# Descripcion: Este programa es un script que le manda
# diferentes test cases al programa de Expresiones Infijas

import os

def main():
    # Sisterma operativo
    SistemaOperativo = os.name
    if SistemaOperativo == "nt":
        ejecutable = "bin\Expresiones_Infijas.exe"
    elif SistemaOperativo == "posix":
        ejecutable = "bin/Expresiones_Infijas"

    # Comprobar que el ejecutable existe
    if not os.path.exists(ejecutable):
        # Si no existe, compilar el codigo fuente
        print(f"El ejecutable \"{ejecutable}\" no existe")
        print("Compilando el codigo fuente...")
        os.system("python3 scripts/compilar.py")

    expresiones = [
        # Paréntesis
        "()",
        "(())",
        "( ) (())",
        ")(()",
        "())",
        # incógnitas
        "A+B",
        "B*A +A",
        "B +A*D",
        # Incógnitas con paréntesis
        "B+(F*C)",
        "C*(A+B )",
        "B*(C+A)^D",
        "F*(G+A)^D+E",
        # Incógnitas con paréntesis y números
        "B+(F*C)+ 2",
        "C*(A+5.3*3-(5))",
        "(1+2)^3/4+5+6+7+8+9+10",
        "5*(C+(4*(5)*A)^D",
        "5*A + 3*B + 2*C + 1*D",
        # La legendaria chicharronera
        "(0-B-((B^2)-4*A*C)^(1/2))/(2*A)",
        "(0-B+((B^2)-4*A*C)^(1/2))/(2*A)"
    ]

    valores_de_incognitas = {
        "A": 0.5,
        "B": -1,
        "C": -3,
        "D": 4,
        "E": 5,
        "F": 6,
        "G": 7,
    }

    # Directorio donde se encuentran los test cases
    if not os.path.exists("out"):
        os.mkdir("out")

    for expresion in expresiones:
        print(f"Probando caso: {expresion}")

        # Escribir los valores de las incognitas en un archivo en el orden en que aparecen
        # Es muy similar a el escaneo de los valores de las incognitas en el programa
        valores_asignados = [False for _ in range(26)]

        with open("out/valores.txt", "w") as archivo:
            for i in range(len(expresion)):
                # Si el caracter es una incognita, y no se ha asignado un valor a esa incognita
                if expresion[i].isalpha() and not valores_asignados[ord(expresion[i]) - ord("A")]:
                    # Lo escribimos en el archivo
                    archivo.write(f"{valores_de_incognitas[expresion[i]]}\n")
                    valores_asignados[ord(expresion[i]) - ord("A")] = True

        # Ejecutar el programa con los valores de las incognitas
        if SistemaOperativo == "posix":
            os.system(f"./{ejecutable} \"{expresion}\" < ./out/valores.txt")
        else:
            os.system(f"{ejecutable} \"{expresion}\" < out/valores.txt")

        print()

    # Borrar el archivo de valores de incognitas
    # os.system("rm out/valores.txt")
    # ¶╣¶╣¶╣¶╣¶╣¶╣¶╣¶╣¶╣¶╣¶╣¶╣¶╣¶╣¶╣¶╣¶╣¶╣
if __name__ == "__main__":
    main()