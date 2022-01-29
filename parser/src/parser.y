%code top{
    #include <stdio.h>
    #include "scanner.h"
}

%code provides{
    void yyerror(const char *);
    extern int yylexerrs;
}

%defines "parser.h"
%output "parser.c"

%define api.value.type {char *}
%define parse.error verbose

%token IDENTIFICADOR CONSTANTE PROGRAMA ENTERO LEER ESCRIBIR FIN_PROGRAMA ASIGNACION

%start programa

%left '+' '-'
%left '*' '/' '%'

%precedence NEG   /* negation--unary minus */

%%

programa
    : PROGRAMA IDENTIFICADOR { printf("PROGRAMA %s\n", $IDENTIFICADOR); } logica FIN_PROGRAMA { if (yynerrs || yylexerrs) YYABORT; else YYACCEPT; }
    ;

logica
    : sentencia
    | logica sentencia
    ;

sentencia
    : identificador ASIGNACION expresion ';' { printf("ASIGNACIÓN\n"); }
    | ENTERO IDENTIFICADOR ';' { printf("ENTERO %s\n", yylval); free(yylval); }
    | LEER '(' lista-de-identificadores ')' ';' { printf("LEER\n"); }
    | ESCRIBIR '(' lista-de-expresiones ')' ';' { printf("ESCRIBIR\n"); }
    | error ';'
    ;

lista-de-identificadores
    : identificador
    | lista-de-identificadores ',' IDENTIFICADOR
    ;

lista-de-expresiones
    : expresion
    | lista-de-expresiones ',' expresion
    ;

expresion
    : identificador
    | CONSTANTE
    | '(' expresion ')' { printf("PARÉNTESIS\n"); }
    | '-' expresion %prec NEG { printf("NEGACIÓN\n"); }
    | expresion '*' expresion { printf("MULTIPLICACIÓN\n"); }
    | expresion '/' expresion { printf("DIVISIÓN\n"); }
    | expresion '%' expresion { printf("MÓDULO\n"); }
    | expresion '+' expresion { printf("SUMA\n"); }
    | expresion '-' expresion { printf("RESTA\n"); }
    ;

identificador
    : IDENTIFICADOR
    ;

%%

/* Informa la ocurrencia de un error. */
void yyerror(const char *s){
	printf("línea #%d: %s\n", yylineno, s);
	return;
}
