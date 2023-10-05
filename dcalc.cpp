#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "exprtk.hpp"
#include <iostream>

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

int parseArg(int argc, char *argv[]){
    if (argc == 1) return UI;
    if (argc == 2) {
        if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) return HELP;
        if(strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) return VERSION;
        if(strcmp(argv[1], "--calculate") == 0 || strcmp(argv[1], "-c") == 0) return CALCULATE_NOARG;
        return ERR_ARG;
    }
    if (argc >= 3) {
        if(strcmp(argv[1], "--calculate") == 0 || strcmp(argv[1], "-c") == 0) return CALCULATE;
    }
    return ERR_ARG;

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
    void trig_function(const char *exp)
    {
        typedef exprtk::symbol_table<double> symbol_table_t;
        typedef exprtk::expression<double> expression_t;
        typedef exprtk::parser<double> parser_t;

        std::string expression_string(exp);

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
    char expresion[300];
    printf("Introduce la expresión a calcular: ");
    scanf("%s", expresion);
    trig_function(expresion);
}

int main(int argc, char *argv[]) {

    int option = parseArg(argc, argv);
    switch (option) {
        case 0:
            userInterface();
            break;
        case 1:
            printf("Error: Falta la expresión a calcular\n");
            break;
        case 2:{
            const char *expresion = getExpression(argc, argv, 2);
            trig_function(expresion);
        }
            break;
        case 3:
            showHelp();
            break;
        case 4:
            showVersion();
            break;
        case 5:
            printf("Error: Argumento no reconocido\nUsa -h | --help para más información\n");
            break;
    }
    return 0;
}



