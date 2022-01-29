#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "scanner.h"

#define YYACCEPT 0
#define YYABORT 1
#define YYNOMEM 2

int yylexerrs = 0;
int yysemerrs = 0;

extern int yynerrs;

int main(void)
{
    unsigned int exit_code = 0;

    switch (yyparse())
    {
    case YYACCEPT:
        printf("Compilación terminada con éxito\n");
        exit_code = YYACCEPT;
        break;
    case YYABORT:
        printf("Errores de compilación\n");
        exit_code = YYABORT;
        break;
    case YYNOMEM:
        printf("Memoria insuficiente\n");
        exit_code = YYNOMEM;
        break;
    }

    printf("Errores sintácticos: %d - Errores léxicos: %d - Errores semánticos: %d\n", yynerrs, yylexerrs, yysemerrs);

    return exit_code;
}
