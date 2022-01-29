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

#ifndef SEMANTIC_H_
#define SEMANTIC_H_

#include "parser.h"
#include "symbol.h"

void inicializar(char *identificador);

void finalizar(void);

void escribir(char *variable_der);

void asignar(char *variable_izq, char *variable_der);

void leer(char *variable_izq);

int declarar(char *identificador);

int declarado(char *identificador);

char *operar(char *variable_izq, char operador, char *variable_der);

char *negar(char *variable_izq);

#endif // SEMANTIC_H_