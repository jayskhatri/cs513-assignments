#include "TreapNode.h"
#include <iostream>
#include <fstream>
using namespace std;

class Treap{
    private:
        //root node and dummy node
        TreapNode *root, *dummy;
        //total number of rotation happened in tree while inserting/deleting node
        long int totalRotation = 0;
        //total number of comparisons happened in tree while inserting/deleting node
        long int totalComparisons = 0;
        //total number of nodes in tree
        int totalNodes = 0;

        //left rotation
        void L_Rotate(TreapNode *&);
        //right rotation
        void R_Rotate(TreapNode *&);
        //recursive function i.e. insertion helper
        void insertionHelper(TreapNode *&, int, int);
        //overloaded recursive function i.e. deletion helper
        void deletionHelper(TreapNode *&, int);
        //overloaded recursive function i.e. deletion helper
        void deletionHelper(TreapNode *&);
        //recursive function to search the node with given key
        bool searchHelper(TreapNode *&, int);
        //recursive function to destroy Tree
        void destroyTreap(TreapNode *&);
        //recursive function to print the tree
        void printNode(TreapNode *&, ofstream &);
        //recursive function to print the inorder
        void inorder(TreapNode *&);
        //helper function for deep copy 
        TreapNode* clone(TreapNode*);
        //helper function to find total height
        int totalHeightHelper(TreapNode *&);
        //function to find height of given node
        int getHeight(TreapNode *&);

    public:
        //constructor
        Treap();
        //destructor
        ~Treap();
        //copy constructor
        Treap(const Treap &T); 
        // = operator overoading
        Treap &operator=(const Treap &T); 
        //insertion function
        bool insertNode(int key, int p);
        //deletion function
        void deleteNode(int key);
        //search function
        bool searchNode(int key);
        //inorder traversal print function
        void inorderTraversal();
        //printing the tree using graphviz
        void printTree(const char *);

        //analysis helper functions
        //size of the tree
        int size();
        //finding average height of each node
        double findAvgHeightofEachNode();
        //finding height of tree
        int heightOfTree();
        //getter of total number of comparison
        long int getComparisons();
        //getter of total number of rotations
        long int getRotations();
};