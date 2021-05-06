
include makefile_ext

bstree.o: bstree.c bstree.h
	gcc -c -g -Wall -pedantic bstree.c

vertex.o: vertex.c vertex.h
	gcc -c -g -Wall -pedantic vertex.c

p4_e1a.o: p4_e1a.c
	gcc -c -g -Wall -pedantic p4_e1a.c 

p4_e1a: p4_e1a.o bstree.o vertex.o
	gcc -o p4_e1a p4_e1a.o bstree.o vertex.o