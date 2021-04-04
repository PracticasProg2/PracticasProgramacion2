#!/bin/bash

gcc -c vertex.c #Compilacion vertex.c

gcc -c p1_e1.c #Compilacion p1_e1.c

gcc vertex.o p1_e1.o -o p1_e1 #Crea el ejecutable a partir de vertex.o y p1_e1.o

