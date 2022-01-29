#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"
#include "scanner.h"

int main(void)
{
    token_t token;
    char token_name[64];

    while ((token = yylex()) != FDT)
    {
        switch (token)
        {
        case IDENTIFICADOR:
            strcpy(token_name, "IDENTIFICADOR");
            break;

        case CONSTANTE:
            strcpy(token_name, "CONSTANTE");
            break;

        case PROGRAMA:
        case ENTERO:
        case LEER:
        case ESCRIBIR:
        case FIN_PROGRAMA:
            strcpy(token_name, "PALABRA RESERVADA");
            break;

        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
            strcpy(token_name, "OPERADOR");
            break;

        case ASIGNACION:
            strcpy(token_name, "ASIGNACION");
            break;

        case '(':
        case ')':
        case ',':
        case ';':
            strcpy(token_name, "CARACTER DE PUNTUACION");
            break;
        }

        printf("Token: \"%s\", Lexema: \"%s\"\n", token_name, yytext);
    }

    return 0;
}
