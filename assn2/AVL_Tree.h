#include "AVL_Node.h"
#include<fstream>
using namespace std;

// AVL_Tree class
class AVL_Tree{ 
  private: 
    AVL_Node *root;

    //extra/helper functions
    void R_Rotate(AVL_Node *&);
    void L_Rotate(AVL_Node *&);
    void LeftBalance(AVL_Node *&);
    void RightBalance(AVL_Node *&);
    int insertHelper(AVL_Node *&, int, int &);
    int deleteHelper(AVL_Node *&, int, int &);
    void printNode(AVL_Node*&, ofstream&);
    // void ConcaveTablePrintAVL(AVL_Node *&, int);
    // void inorderHelper(AVL_Node *&);
    AVL_Node* link(AVL_Node*, int);
    AVL_Node* clone(AVL_Node*);
    //to destroy the tree
    void destroyAVL(AVL_Node *&root);

public: 
    //default constructor
    AVL_Tree(); 
    //copy constructor
    AVL_Tree(const AVL_Tree &T); 
    // = operator overoading
    AVL_Tree &operator=(const AVL_Tree &T); 
    //insert function
    void AVL_Insert(int k); 
    //delete function
    void AVL_Delete(int k); 
    //search function
    bool AVL_Search(int k);
    //print function 
    void AVL_Print(const char *filename); 
    //destructor
    ~AVL_Tree(); 

};