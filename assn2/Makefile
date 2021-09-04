CC=g++

CFLAGS=-c -Wall

all: avl

avl: main.o AVL_Tree.o
	$(CC) main.o AVL_Tree.o -o avl

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

AVL_Tree.o: AVL_Tree.cpp
	$(CC) $(CFLAGS) AVL_Tree.cpp

clean:
	rm -rf *o avl

#this will compile all the files
all: avl

avl: main.o AVL_Tree.o
	g++ main.o AVL_Tree.o -o avl

main.o: main.cpp
	g++ -c main.cpp

AVL_Tree.o: AVL_Tree.cpp
	g++ -c AVL_Tree.cpp

clean:
	rm -rf *o avl
	

