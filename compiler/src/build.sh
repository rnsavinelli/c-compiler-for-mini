#!/bin/bash

echo "Compiling parser..."

flex -l scanner.l && bison -Wcounterexamples -d parser.y && gcc -o compiler scanner.c symbol.c semantic.c parser.c main.c -lfl && echo "Success."
