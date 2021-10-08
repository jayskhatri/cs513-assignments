class BSTNode{
    private:
        int key;
        BSTNode *left;
        BSTNode *right;
        friend class BST;

    public:
        BSTNode(int k){
            key = k;
            left = right = nullptr;
        }
};