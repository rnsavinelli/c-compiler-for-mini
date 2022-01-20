#!/bin/bash

echo "Compiling scanner..."

flex -l scanner.l && gcc -o scanner scanner.c main.c -lfl && echo "Success."