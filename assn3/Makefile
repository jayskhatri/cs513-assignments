CC=g++

CFLAGS=-c -Wall

all: analysis treap

debug: CFLAGS += -g 
debug: executable 
debug: exe1

executable: analysis.o Treap.o AVL_Tree.o BST.o
	$(CC) -g  analysis.o Treap.o AVL_Tree.o BST.o -o dAnalysis

exe1: main_treap.o Treap.o
	$(CC) -g main_treap.o Treap.o -o dTreap

analysis: analysis.o Treap.o AVL_Tree.o BST.o
	$(CC) analysis.o Treap.o AVL_Tree.o BST.o -o analysis

treap: main_treap.o Treap.o
	$(CC) main_treap.o Treap.o -o treap

analysis.o: analysis.cpp
	$(CC) $(CFLAGS) analysis.cpp

main_treap.o: main_treap.cpp 
	$(CC) $(CFLAGS) main_treap.cpp

Treap.o: Treap.cpp
	$(CC) $(CFLAGS) Treap.cpp

BST.o: BST.cpp
	$(CC) $(CFLAGS) BST.cpp

AVL_Tree.o: AVL_Tree.cpp
	$(CC) $(CFLAGS) AVL_Tree.cpp

clean:
	rm -rf *o treap debug analysis dTreap dAnalysis