##################################################
CC =gcc
CFLAGS = -c -g -Wall -pedantic
EJS = p3_e1a p3_e1b
##################################################
all: $(EJS) clear

vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) vertex.c

p3_e1a.o: p3_e1a.c
	$(CC) $(CFLAGS) p3_e1a.c

p3_e1b.o: p3_e1b
	$(CC) $(CFLAGS) p3_e1b.c

p3_e1b: p3_e1b.o libdelivery.a libqueue.a vertex.o
	$(CC) -o p3_e1b p3_e1b.o libdelivery.a libqueue.a vertex.o

p3_e1a: p3_e1a.o libdelivery.a libqueue.a vertex.o
	$(CC) -o p3_e1a p3_e1a.o libdelivery.a libqueue.a vertex.o

clear:
	rm -rf *.o