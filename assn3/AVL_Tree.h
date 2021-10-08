#include "AVL_Node.h"
#include<fstream>
using namespace std;

// AVL_Tree class
class AVL_Tree{ 
  private: 
    AVL_Node *root;
    long int totalRotations = 0;
    long int totalComparisons = 0;
    int totalNodes = 0;

    //extra/helper functions
    //single rotation function
    void R_Rotate(AVL_Node *&);
    void L_Rotate(AVL_Node *&);

    //double rotations
    void LeftBalance(AVL_Node *&);
    void RightBalance(AVL_Node *&);
    
    //helper function for insertion
    int insertHelper(AVL_Node *&, int, int &);
    
    //helper function for printing tree
    void printNode(AVL_Node*&, ofstream&);
    
    //function to get the left or right child depending on the
    //balance factor
    AVL_Node* link(AVL_Node*, int);
    
    //helper function for deep copy 
    AVL_Node* clone(AVL_Node*);
    
    //to destroy the tree
    void destroyAVL(AVL_Node *&);


    int totalHeightHelper(AVL_Node *&);
    int getHeight(AVL_Node *&);

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

    //analysis helper functions
    int size();
    double findAvgHeightofEachNode();
    int heightOfTree();
    long int getComparisons();
    long int getRotations();

};