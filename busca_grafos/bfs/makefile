CFLAGS="-Wall -g -c99"

all: main.o bfs.o graph.o fila.o
	gcc ${CFLAGS} -o  main main.o bfs.o graph.o fila.os

main.o: main.c bfs.o
	gcc ${CFLAGS} -c main.c

bfs.o: bfs.c graph.o
	gcc ${CFLAGS} -c bfs.c

graph.o: graph.c fila.o
	gcc ${CFLAGS} -c graph.c

fila.o: fila.c
	gcc -g -c fila.c