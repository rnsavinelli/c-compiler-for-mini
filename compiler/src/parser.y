%code top{
    #include <stdio.h>

    #include "scanner.h"
    #include "semantic.h"
    #include "symbol.h"

    simbolo_t *tabla_de_simbolos =  NULL;
}

%code provides{
    void yyerror(const char *);
    extern int yylexerrs;
    extern int yysemerrs;
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
    :  PROGRAMA IDENTIFICADOR { inicializar($2); } logica FIN_PROGRAMA { finalizar(); if (yynerrs || yylexerrs || yysemerrs) YYABORT; else YYACCEPT; }
    ;

logica
    : sentencia
    | logica sentencia
    ;

sentencia
    : identificador ASIGNACION expresion ';' { asignar($1, $3); }
    | ENTERO IDENTIFICADOR ';' { if( declarar($2) == -1 ) YYERROR; }
    | LEER '(' lista-de-identificadores ')' ';' 
    | ESCRIBIR '(' lista-de-expresiones ')' ';' 
    | error ';'
    ;

lista-de-identificadores
    : identificador { leer($1); }
    | lista-de-identificadores ',' identificador { leer($3); }
    ;

lista-de-expresiones
    : expresion { escribir($1); }
    | lista-de-expresiones ',' expresion { escribir($3); }
    ;

expresion
    : identificador
    | CONSTANTE
    | '(' expresion ')' { $$ = $2; }
    | '-' expresion %prec NEG { $$ = negar($2); }
    | expresion '*' expresion { $$ = operar($1, '*', $3); }
    | expresion '/' expresion { $$ = operar($1, '/', $3); }
    | expresion '%' expresion { $$ = operar($1, '%', $3); }
    | expresion '+' expresion { $$ = operar($1, '+', $3); }
    | expresion '-' expresion { $$ = operar($1, '-', $3); }
    ;

identificador
    : IDENTIFICADOR { if (declarado($1) == 1) $$ = $1; else YYERROR; }
    ;

%%

/* Informa la ocurrencia de un error. */
void yyerror(const char *s){
	printf("línea #%d: %s\n", yylineno, s);
	return;
}
