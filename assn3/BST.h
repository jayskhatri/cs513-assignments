#include "BSTNode.h"
#include <iostream>
using namespace std;

class BST {
    private:
        BSTNode *root;
        int totalNodes = 0;
        long int totalComparisons = 0;

        void destroyBST(BSTNode *&root);
        //helper function for deep copy 
        BSTNode* clone(BSTNode*);
        void printNode(BSTNode *&, ofstream &);
        BSTNode* searchChildNode(BSTNode *parent, int value);
        void addChildNode(BSTNode *parent, int value);
        void deleteChildNode(BSTNode *parent, BSTNode *current, int value);
        BSTNode* findNearestSuccessor(BSTNode* current, BSTNode** parent);
        void traverse(BSTNode*);
        
        int totalHeightHelper(BSTNode *&);
        int getHeight(BSTNode *&);

    public:
        BST();
        ~BST();
        // copy constructor
        BST(const BST &T); 
        // = operator overoading
        BST &operator=(const BST &T); 

        BSTNode* searchNode(int value);
        void addNode(int value);
        void deleteNode(int value);
        void traverse();
        void BST_Print(const char *);

        //analysis helper functions
        int size();
        long int getComparisons();
        double findAvgHeightofEachNode();
        int heightOfTree();
};