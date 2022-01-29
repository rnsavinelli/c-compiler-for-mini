/*
 * semantic.c
 *
 * Copyright 2020 Roberto Nicolás Savinelli <rnsavinelli@est.frba.utn.edu.ar>
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "semantic.h"

#define DECLARACION_INEXISTENTE "NO"
#define REDECLARACION "YA FUE"

extern simbolo_t *tabla_de_simbolos;

int _variables_temporales = 0;

static void _generar_instruccion(const char *instruccion, int cantidad_de_argumentos, ...)
{
    va_list ap;

    printf("%s", instruccion);

    va_start(ap, cantidad_de_argumentos);
    for (int i = 0; i < cantidad_de_argumentos; i++)
    {
        if (i == 0)
            printf(" %s", va_arg(ap, char *));
        else
            printf(", %s", va_arg(ap, char *));
    }
    va_end(ap);

    printf("\n");
}

static void _arrojar_error_semantico(const char *identificador, const char *estado)
{
    char buffer[128];
    yysemerrs++;
    sprintf(buffer, "Error semántico: identificador %s %s declarado", identificador, estado);
    yyerror(buffer);
    return;
}

static char *_nueva_variable_temporal(void)
{
    char buffer[128];

    sprintf(buffer, "Temp@%d", _variables_temporales++);

    char *temporal = strdup(buffer);

    if (declarar(temporal) == 0)
        return temporal;

    return NULL;
}

void inicializar(char *identificador)
{
    tabla_de_simbolos = NULL;

    _generar_instruccion("Load", 2, "rtlib", identificador);

    free(identificador);
}

void finalizar(void)
{
    borrar_simbolos(&tabla_de_simbolos);

    _generar_instruccion("Exit", 0);
}

void escribir(char *variable_der)
{
    if (contiene_simbolo(tabla_de_simbolos, variable_der) == 0)
        _generar_instruccion("Write", 2, variable_der, "Integer");

    else
        _arrojar_error_semantico(variable_der, DECLARACION_INEXISTENTE);

    free(variable_der);

    return;
}

void asignar(char *variable_der, char *variable_izq)
{
    if (contiene_simbolo(tabla_de_simbolos, variable_izq) == 0)
    {
        if (contiene_simbolo(tabla_de_simbolos, variable_der) == 0)
            _generar_instruccion("Store", 2, variable_izq, variable_der);
        else
            _arrojar_error_semantico(variable_der, DECLARACION_INEXISTENTE);
    }
    else
        _arrojar_error_semantico(variable_izq, DECLARACION_INEXISTENTE);

    free(variable_izq);
    free(variable_der);

    return;
}

void leer(char *variable_izq)
{
    if (contiene_simbolo(tabla_de_simbolos, variable_izq) == 0)
        _generar_instruccion("Read", 2, variable_izq, "Integer");

    else
        _arrojar_error_semantico(variable_izq, DECLARACION_INEXISTENTE);

    free(variable_izq);

    return;
}

int declarar(char *identificador)
{
    if (contiene_simbolo(tabla_de_simbolos, identificador) != 0)
    {
        simbolo_t *simbolo = nuevo_simbolo(identificador);
        agregar_simbolo(&tabla_de_simbolos, simbolo);
        _generar_instruccion("Reserve", 2, identificador, "4");
        return 0;
    }

    _arrojar_error_semantico(identificador, REDECLARACION);

    return -1;
}

int declarado(char *identificador)
{
    if (contiene_simbolo(tabla_de_simbolos, identificador) == 0)
        return 1;

    _arrojar_error_semantico(identificador, DECLARACION_INEXISTENTE);

    return -1;
}

char *operar(char *variable_izq, char operador, char *variable_der)
{
    char *temporal = _nueva_variable_temporal();

    /*
    if (contiene_simbolo(tabla_de_simbolos, variable_izq) != 0)
    {
        _arrojar_error_semantico(variable_izq, DECLARACION_INEXISTENTE);
        return NULL;
    }

    if (contiene_simbolo(tabla_de_simbolos, variable_der) != 0)
    {
        _arrojar_error_semantico(variable_der, DECLARACION_INEXISTENTE);
        return NULL;
    }
    */

    switch (operador)
    {
    case '*':
        _generar_instruccion("MUL", 3, variable_izq, variable_der, temporal);
        break;
    case '/':
        _generar_instruccion("DIV", 3, variable_izq, variable_der, temporal);
        break;
    case '%':
        _generar_instruccion("MOD", 3, variable_izq, variable_der, temporal);
        break;
    case '+':
        _generar_instruccion("ADD", 3, variable_izq, variable_der, temporal);
        break;
    case '-':
        _generar_instruccion("SUB", 3, variable_izq, variable_der, temporal);
        break;
    }
    return temporal;
}

char *negar(char *variable_izq)
{

    char *temporal = _nueva_variable_temporal();

    _generar_instruccion("INV", 3, variable_izq, "", temporal);

    return temporal;
}