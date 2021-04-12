##################################################
CC =gcc
CFLAGS = -c -g -Wall -pedantic
EJS = p3_e1a
##################################################
all: $(EJS) clear

vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) vertex.c

p3_e1a.o: p3_e1a.c
	$(CC) $(CFLAGS) p3_e1a.c

p3_e1a: p3_e1a.o libdelivery.a libqueue.a vertex.o
	$(CC) -o p3_e1a p3_e1a.o libdelivery.a libqueue.a vertex.o

clear:
	rm -rf *.o