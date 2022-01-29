/*
 * scanner.l
 *
 * Copyright 2021 Roberto Nicolás Savinelli <rnsavinelli@frba.utn.edu.ar>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

%{

#include <stdio.h>
#include "tokens.h"

void yyerror(const char *);

#define ERROR_LEXICO(mensaje) char buffer[128]; sprintf(buffer, "Error léxico: %s: %s", mensaje, yytext ); yyerror(buffer);

%}

%option outfile="scanner.c"
%option header-file="scanner.h"

%option noyywrap
%option nounput
%option noinput
%option yylineno

espacio_en_blanco [[:space:]]
comentario \/\/[^\n]*
caracter_invalido [~`!@#$^&\[}[\]'"?\\>]

letra [[:alpha:]]
digito [[:digit:]]

operador_primario [+-]
operador_secundario [*/%]

identificador {letra}({letra}|{digito})*
constante {digito}+
palabra_reservada programa|entero|leer|escribir|fin-programa
asignacion <<

%%

"programa" { return PROGRAMA; }

"entero" { return ENTERO; }

"leer" { return LEER; }

"escribir" { return ESCRIBIR; }

"fin-programa" { return FIN_PROGRAMA; }

{espacio_en_blanco}+ {} /* ignorar nuevas lineas, tabuladores y espacios */

{comentario} {} /* ignorar comentarios */

{caracter_invalido}+ { ERROR_LEXICO("cadena inválida"); }

{asignacion} { return ASIGNACION; }

{identificador} { return IDENTIFICADOR; }

{constante} { return CONSTANTE; }

{constante}({caracter_invalido}|{letra})({caracter_invalido}|{letra}|{digito})* { ERROR_LEXICO("constante inválida"); }

{identificador}{caracter_invalido}({caracter_invalido}|{letra}|{digito})*  { ERROR_LEXICO("identificador inválido"); }

"+" { return '+'; }

"-" { return '-'; }

"*" { return '*'; }

"/" { return '/'; }

"%" { return '%'; }

"(" { return '('; }

")" { return ')'; }

"," { return ','; }

";" { return ';'; }

. { ERROR_LEXICO("caracter desconocido"); }

%%

/* Informa la ocurrencia de un error. */
void yyerror(const char *s){
	printf("línea #%d: %s\n", yylineno, s);
	return;
}
