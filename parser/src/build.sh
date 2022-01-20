#!/bin/bash

echo "Compiling parser..."

flex -l scanner.l && bison -Wcounterexamples -d parser.y && gcc -o parser scanner.c parser.c main.c -lfl && echo "Success."
