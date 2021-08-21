#include "BSTNode.h"
#include "LLNode.h"
//Threaded Binary search Tree Node class
class ThreadedBST {
private:
	BSTNode* root;
	void eraseTreeNodes(BSTNode* node);
	BSTNode* copy_helper(BSTNode* copy_from);
public:
	ThreadedBST() { root = NULL; }
	~ThreadedBST() { eraseTreeNodes(root); root = NULL; }

	ThreadedBST(const ThreadedBST& other);

	void insert(int x);
    BSTNode* search(int key);
	void deleteNode(int key);
    LLNode* reverseInorder();
    int successor(BSTNode* node);
    void split(int k, ThreadedBST*& left, ThreadedBST*& right);
    LLNode* allElementsBetween(int k1, int k2);
    int kthElement(int k);
    void printTree();

	BSTNode* getRoot() { return root; }
	BSTNode* min();
	BSTNode* max();
	BSTNode* predecessor(BSTNode* node);
	BSTNode* next(BSTNode* node);
    LLNode* inorder();
};