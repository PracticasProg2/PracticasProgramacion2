########################################################
CC=gcc
CFLAGS= -c -Wall -pedantic
########################################################

graph.o: graph.c graph.h vertex.h
	$(CC) $(CFLAGS) graph.c
 
vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) vertex.c
	
p2_e1a.o: p2_e1a.c
	$(CC) $(CFLAGS) p2_e1a.c
	
p2_e1b.o: p2_e1b.c
	$(CC) $(CFLAGS) p2_e1b.c
 
p2_e2.o: p2_e2.c
	$(CC) $(CFLAGS) p2_e2.c
	
stack_fDoble.o: stack_fDoble.h stack_fDoble.c
	$(CC) $(CFLAGS) stack_fDoble.c

p2_e1a: p2_e1a.o libstack_fDoble.a
	$(CC) -o p2_e1a p2_e1a.o libstack_fDoble.a
	
p2_e1b: p2_e1b.o vertex.o stack_fDoble.o
	$(CC) -o p2_e1b vertex.o p2_e1b.o stack_fDoble.o

p2_e2: graph.o vertex.o p2_e2.o libstack_fDoble.a
	$(CC) -o p2_e2 graph.o vertex.o p2_e2.o libstack_fDoble.a
	
run: p2_e2
	./p2_e2 g2.txt 100 700
	
runv: p2_e2
	valgrind --leak-check=full ./p2_e2 g2.txt 100 700
