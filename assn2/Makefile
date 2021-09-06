CC=g++

CFLAGS=-c -g -Wall

all: avl

debug: main.o AVL_Tree.o
	$(CC) -g main.o AVL_Tree.o -o debug

avl: main.o AVL_Tree.o
	$(CC) main.o AVL_Tree.o -o avl

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

AVL_Tree.o: AVL_Tree.cpp
	$(CC) $(CFLAGS) AVL_Tree.cpp

clean:
	rm -rf *o avl debug

#this will compile all the files
# all: avl

# avl: main.o AVL_Tree.o
# 	g++ main.o AVL_Tree.o -o avl

# main.o: main.cpp
# 	g++ -c main.cpp

# AVL_Tree.o: AVL_Tree.cpp
# 	g++ -c AVL_Tree.cpp

# clean:
# 	rm -rf *o avl
	

