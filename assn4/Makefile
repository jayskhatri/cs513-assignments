CC=g++

CFLAGS=-c -Wall

all: graph

debug: CFLAGS += -g 
debug: executable

executable: main.o Graph.o
	$(CC) -g main.o Graph.o -o dgraph

graph: main.o Graph.o
	$(CC) main.o Graph.o -o graph

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Graph.o: Graph.cpp
	$(CC) $(CFLAGS) Graph.cpp

clean:
	rm -rf *o graph dgraph graph.gv graph.png