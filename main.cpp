#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

// Función para mostrar la ayuda
void showHelp() {
    printf("Uso: calc [OPCIÓN] [EXPRESIÓN]\n");
    printf("Opciones:\n");
    printf("  -c, --calculate <EXPRESIÓN>  Calcula el resultado de la expresión\n");
    printf("  --help                       Muestra este mensaje de ayuda\n");
    printf("  --version                    Muestra la versión del programa\n");
}

void showVersion(){
    printf("calc 1.0.0\n");
}

// Función para evaluar una expresión matemática simple
double calculate(const char *expression) {

}

int main(int argc, char *argv[]) {


    return 0;
}



