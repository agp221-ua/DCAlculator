#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "exprtk.hpp"
#include <iostream>

enum Option { UI, CALCULATE_NOARG, CALCULATE, HELP, VERSION, ERR_ARG, RAW_CALCULATE };

// Function to display help
void showHelp() {
    printf("Usage: dcalc [OPTION] [EXPRESSION]\n");
    printf("Options:\n");
    printf("  -c, --calculate <EXPRESSION>  Calculate the result of the expression\n");
    printf("  -rc, --raw-calculate <EXPRESSION>  Calculate the result of the expression showing it without added text as 'Result: '\n");
    printf("  --help                       Display this help message\n");
    printf("  --version                    Display program version\n");
}

void showVersion() {
    printf("DCAlc 1.0.0\n");
    printf("Author: Alejandro Galan Perez\n");
}

int parseArg(int argc, char *argv[]) {
    if (argc == 1) return UI;
    if (argc == 2) {
        if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) return HELP;
        if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) return VERSION;
        if (strcmp(argv[1], "--raw-calculate") == 0 || strcmp(argv[1], "-rc") == 0) return CALCULATE_NOARG;
        return ERR_ARG;
    }
    if (argc >= 3) {
        if (strcmp(argv[1], "--calculate") == 0 || strcmp(argv[1], "-c") == 0) return CALCULATE;
        if (strcmp(argv[1], "--raw-calculate") == 0 || strcmp(argv[1], "-rc") == 0) return RAW_CALCULATE;
    }
    return ERR_ARG;
}

char *getExpression(int argc, char *argv[], int pos) {
    int totalLength = 0;
    for (int i = pos; i < argc; i++) {
        totalLength += strlen(argv[i]) + 1; // +1 for the space between arguments
    }

    char *result = (char *)malloc(totalLength * sizeof(char));
    if (result == NULL) {
        perror("Error allocating memory");
        exit(1);
    }

    strcpy(result, ""); // Initialize the result as an empty string

    for (int i = pos; i < argc; i++) {
        strcat(result, argv[i]);
        if (i < argc - 1) {
            strcat(result, " "); // Add a space between arguments
        }
    }
    strcat(result, "\0"); // Add the null character at the end of the string

    return result;
}

// Function to evaluate the RPN expression
void trig_function(const char *exp, bool raw) {
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

    std::string expression_string(exp);
    int count = std::count_if(expression_string.begin(), expression_string.end(),
                              [](unsigned char c){ return std::isspace(c); });
    remove(expression_string.begin(), expression_string.end(), ' ');
    expression_string = expression_string.substr(0, expression_string.length()-count);


    symbol_table_t symbol_table;
    expression_t expression;
    parser_t parser;

    if (parser.compile(expression_string, expression)) {
        double result = expression.value();
        std::cout << ((raw) ? "" : "Result of the expression: ") << result << std::endl;
    } else {
        std::cerr << "Error compiling the expression." << std::endl;
    }
}

void userInterface() {
    printf("Enter the expression to calculate: ");
    std::string expression;
    std::getline(std::cin, expression);
    trig_function(expression.c_str(), false);
}

int main(int argc, char *argv[]) {

    int option = parseArg(argc, argv);
    switch (option) {
        case 0:
            userInterface();
            break;
        case 1:
            printf("Error: Missing expression to calculate\n");
            break;
        case 2: {
            const char *expression = getExpression(argc, argv, 2);
            trig_function(expression, false);
        }
            break;
        case 3:
            showHelp();
            break;
        case 4:
            showVersion();
            break;
        case 5:
            printf("Error: Unrecognized argument\nUse -h | --help for more information\n");
            break;
        case 6: {
            const char *expression = getExpression(argc, argv, 2);
            trig_function(expression, true);
        }
    }
    return 0;
}
