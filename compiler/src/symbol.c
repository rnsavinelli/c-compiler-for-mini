/*
 * template.c
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

#include "symbol.h"

simbolo_t *nuevo_simbolo(char *valor)
{
    simbolo_t *simbolo = malloc(sizeof(simbolo_t));
    simbolo->valor = malloc(sizeof(char) * (strlen(valor) + 1));
    strcpy(simbolo->valor, valor);
    simbolo->sig = NULL;
    return simbolo;
}

void agregar_simbolo(simbolo_t **lista, simbolo_t *simbolo)
{
    simbolo->sig = *lista;
    *lista = simbolo;
}

void borrar_simbolos(simbolo_t **lista)
{
    simbolo_t *actual = *lista;
    simbolo_t *sig;

    while (actual != NULL)
    {
        sig = actual->sig;
        free(actual);
        actual = sig;
    }

    *lista = NULL;
}

int contiene_simbolo(simbolo_t *lista, char *valor)
{
    simbolo_t *aux;

    for (aux = lista; aux != NULL; aux = aux->sig)
    {
        if (strcmp(aux->valor, valor) == 0)
            return 0;
    }
    return -1;
}