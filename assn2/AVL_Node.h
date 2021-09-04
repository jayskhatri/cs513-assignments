// definition of AVL_Node class

class AVL_Node{ 
  private: 
    int key; 
    int bf;  // balance factor bf = height(left subtree) – height(right subtree) 
    AVL_Node *LChild, *RChild; 
    friend class AVL_Tree; 
  
  public:
    //constructor
    AVL_Node(int k){
      key = k;
      bf = 0;
      LChild = RChild = nullptr;
    }
};
