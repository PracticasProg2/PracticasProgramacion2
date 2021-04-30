##################################################
CC =gcc
CFLAGS = -c -g -Wall -pedantic
EJS = p3_e1a p3_e1b p3_e2a p3_e2b p3_e3 p3_e3_ord
##################################################
all: $(EJS) clear

vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) vertex.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) queue.c

list.o: list.c list.h
	$(CC) $(CFLAGS) list.c

p3_e1a.o: p3_e1a.c
	$(CC) $(CFLAGS) p3_e1a.c

p3_e1b.o: p3_e1b
	$(CC) $(CFLAGS) p3_e1b.c

p3_e3.o: p3_e3
	$(CC) $(CFLAGS) p3_e3.c

p3_e3_ord.o: p3_e3_ord
	$(CC) $(CFLAGS) p3_e3_ord.c

p3_e1b: p3_e1b.o libdelivery.a libqueue.a vertex.o
	$(CC) -o p3_e1b p3_e1b.o libdelivery.a libqueue.a vertex.o

p3_e1a: p3_e1a.o libdelivery.a libqueue.a vertex.o
	$(CC) -o p3_e1a p3_e1a.o libdelivery.a libqueue.a vertex.o

p3_e2b: p3_e1b.o libdelivery.a queue.o vertex.o
	$(CC) -o p3_e1b p3_e1b.o libdelivery.a queue.o vertex.o

p3_e2a: p3_e1a.o libdelivery.a queue.o vertex.o
	$(CC) -o p3_e1a p3_e1a.o libdelivery.a queue.o vertex.o

p3_e3: p3_e3.o list.o vertex.o
	$(CC) -o p3_e3 p3_e3.o list.o vertex.o

p3_e3_ord: p3_e3_ord.o list.o libstack_fDoble.a
	$(CC) -o p3_e3_ord p3_e3_ord.o libstack_fDoble.a list.o

clear:
	rm -rf *.o