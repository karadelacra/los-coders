# compilar.py
# Version 1.0 22 de Noviembre 2022
# Autor:
#
# Descripcion: Este programa es un script que le manda
# diferentes test cases al programa de Expresiones Infijas

import os

def main():
    # Sisterma operativo
    SistemaOperativo = os.uname().sysname

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
        "()(())",
        "(()",
        "())",
        # incógnitas
        "A+B",
        "B*A+A",
        "B+A*D",
        # Incógnitas con paréntesis
        "B+(F*C)",
        "C*(A+B)",
        "B*(C+A)^D",
        "F*(G+A)^D+E",
    ]

    valores_de_incognitas = {
        "A": 1.5,
        "B": -2,
        "C": 0.0,
        "D": 4,
        "E": 5,
        "F": 6,
        "G": 7,
    }

    # Directorio donde se encuentran los test cases
    os.system("mkdir -p out")

    for expresion in expresiones:
        print(f"Probando caso: {expresion}")

        # Escribir los valores de las incognitas en un archivo en el orden en que aparecen
        # Es muy similar a el escaneo de los valores de las incognitas en el programa
        valores_asignados = [False for _ in range(26)]
        with open("out/valores.txt", "w") as archivo:
            for i in range(len(expresion)):
                if expresion[i].isalpha() and not valores_asignados[ord(expresion[i]) - ord("A")]:
                    archivo.write(f"{valores_de_incognitas[expresion[i]]}\n")
                    valores_asignados[ord(expresion[i]) - ord("A")] = True

        # Ejecutar el programa con los valores de las incognitas
        if SistemaOperativo == "Linux":
            os.system(f"./{ejecutable} '{expresion}' < ./out/valores.txt")
        else:
            os.system(f"{ejecutable}.exe '{expresion} < out/valores.txt")

        print()

    # Borrar el archivo de valores de incognitas
    # os.system("rm out/valores.txt")

if __name__ == "__main__":
    main()