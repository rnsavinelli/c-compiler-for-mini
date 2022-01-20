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
#include "parser.h"

#define ERROR_LEXICO(mensaje) printf("[ERROR LÉXICO] %s: %s\n", mensaje, yytext )

%}

%option outfile="scanner.c"
%option header-file="scanner.h"

%option noyywrap
%option nounput
%option noinput

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

{caracter_invalido}+ { yylexerrs++; ERROR_LEXICO("Cadena inválida"); }

{asignacion} { return ASIGNACION; }

{identificador} { yylval = strdup(yytext); return IDENTIFICADOR; }

{constante} { yylval = strdup(yytext); return CONSTANTE; }

{constante}({caracter_invalido}|{letra}|{digito})+ { yylexerrs++; ERROR_LEXICO("Constante inválida"); }

{identificador}({caracter_invalido}|{letra}|{digito})+  { yylexerrs++; ERROR_LEXICO("Identificador inválido"); }

"+" { return '+'; }

"-" { return '-'; }

"*" { return '*'; }

"/" { return '/'; }

"%" { return '%'; }

"(" { return '('; }

")" { return ')'; }

"," { return ','; }

";" { return ';'; }

. { yylexerrs++; ERROR_LEXICO("Caracter desconocido"); }

%%
