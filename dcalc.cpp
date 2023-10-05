#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "exprtk.hpp"
#include <iostream>
#include <string>

enum Option {UI, CALCULATE_NOARG, CALCULATE, HELP, VERSION, ERR_ARG};
// Función para mostrar la ayuda
void showHelp() {
    printf("Uso: dcalc [OPCIÓN] [EXPRESIÓN]\n");
    printf("Opciones:\n");
    printf("  -c, --calculate <EXPRESIÓN>  Calcula el resultado de la expresión\n");
    printf("  --help                       Muestra este mensaje de ayuda\n");
    printf("  --version                    Muestra la versión del programa\n");
}
void showVersion(){
    printf("DCAlc 1.0.0\n");
    printf("Autor: Alejandro Galan Perez\n");
}

enum Option parseArg(int argc, char *argv[]){
    if (argc == 1) return UI;
    if (argc == 2) {
        if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) return HELP;
        if(strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) return VERSION;
        if(strcmp(argv[1], "--calculate") == 0 || strcmp(argv[1], "-c") == 0) return CALCULATE_NOARG;
        return ERR_ARG;
    }
    if (argc >= 3) {
        if(strcmp(argv[1], "--calculate") == 0 || strcmp(argv[1], "-c") == 0) return CALCULATE;
        return ERR_ARG;
    }
}

int caracteresPermitidos(const char* str) {
    // Itera a través de cada carácter en la cadena
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        // Comprueba si el carácter no está en la lista de caracteres permitidos
        if (!(c >= '0' && c <= '9') && c != '.' && c != '(' && c != ')' &&
            c != '+' && c != '-' && c != '*' && c != '/' && c != '^') {
            return 0; // El carácter no está permitido
        }
    }
    return 1; // Todos los caracteres son permitidos
}

char *getExpression(int argc, char *argv[], int pos){
    int longitudTotal = 0;
    for (int i = pos; i < argc; i++) {
        longitudTotal += strlen(argv[i]) + 1; // +1 para el espacio entre argumentos
    }

    char* resultado = (char*)malloc(longitudTotal * sizeof(char));
    if (resultado == NULL) {
        perror("Error al asignar memoria");
        exit(1);
    }

    strcpy(resultado, ""); // Inicializa el resultado como una cadena vacía

    for (int i = pos; i < argc; i++) {
        strcat(resultado, argv[i]);
        if (i < argc - 1) {
            strcat(resultado, " "); // Agrega un espacio entre argumentos
        }
    }
    strcat(resultado, "\0"); // Agrega el carácter nulo al final de la cadena

    return resultado;
}

// Función para evaluar la expresión en RPN
    void trig_function(char *exp)
    {
        typedef exprtk::symbol_table<double> symbol_table_t;
        typedef exprtk::expression<double> expression_t;
        typedef exprtk::parser<double> parser_t;

        std::string expression_string str(exp);

        symbol_table_t symbol_table;
        expression_t expression;
        parser_t parser;

        if (parser.compile(expression_string, expression)) {
            double result = expression.value();
            std::cout << "Resultado de la expresión: " << result << std::endl;
        } else {
            std::cerr << "Error al compilar la expresión." << std::endl;
        }
    }


void userInterface(){

}

int main(int argc, char *argv[]) {

    //TODO gestor de argumentos
    int option = parseArg(argc, argv);

    //TODO tratar segun argumento
    switch (option) {
        case UI:
            userInterface();
            break;
        case CALCULATE_NOARG:
            printf("Error: Falta la expresión a calcular\n");
            break;
        case CALCULATE:
            const char *expresion = getExpression(argc, argv, 2);
            if (!caracteresPermitidos(expresion)) {
                printf("Error: Caracteres no permitidos en la expresión\n");
                exit(1);
            }
            char* rpn = convertirARPN(expresion);

            if (rpn != NULL) {
                double resultado = evaluarRPN(rpn);
                printf("Resultado de la expresion: %f\n", resultado);
                free(rpn);
            } else {
                printf("Error en la expresion.\n");
            }
            break;
        case HELP:
            showHelp();
            break;
        case VERSION:
            showVersion();
            break;
        case ERR_ARG:
            printf("Error: Argumento no reconocido\nUsa -h | --help para más información\n");
            break;
    }
    return 0;
}



