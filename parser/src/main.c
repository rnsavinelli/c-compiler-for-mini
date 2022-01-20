#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

#define YYACCEPT 0
#define YYABORT 1
#define YYNOMEM 2

int yylexerrs = 0;
extern int yynerrs;

int main(void)
{
    switch( yyparse() )
    {
        case YYACCEPT:
            printf("Compilación terminada con éxito\n");
            break;
        case YYABORT:
            printf("Errores de compilación\n");
            break;
        case YYNOMEM:
            printf("Memoria insuficiente\n");
            break;
    }

    printf("Errores sintácticos: %d - Errores léxicos: %d\n", yynerrs, yylexerrs);

    return 0;
}
