/*
 * symbol.h
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

#ifndef SYMBOL_H_
#define SYMBOL_H_

#include "parser.h"

typedef struct simbolo
{
    char *valor;
    struct simbolo *sig;
} simbolo_t;

simbolo_t *nuevo_simbolo(char *valor);

void borrar_simbolos(simbolo_t **lista);

void agregar_simbolo(simbolo_t **lista, simbolo_t *simbolo);

int contiene_simbolo(simbolo_t *lista, char *valor);

#endif // SYMBOL_H_