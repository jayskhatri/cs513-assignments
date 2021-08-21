//if it is pointing to child
#define CHILD	0 // false means link is pointing child
//if it is pointing to successor or predecessor
#define THREAD	1 //true means link is pointing thread

#include <iostream>
#include <fstream>
#include <climits>
#include <algorithm>
#include "ThreadedBST.h"

using namespace std;

// Traverse all the nodes and deletes it
void ThreadedBST::eraseTreeNodes(BSTNode* node) {
	BSTNode* curr = this->min();
	while (curr != NULL) {
		BSTNode* n = this->next(curr);
		delete curr;
		curr = n;
	}
} 

//copy constructor
ThreadedBST::ThreadedBST(const ThreadedBST& other) {
	root = copy_helper(other.root);
}

BSTNode* ThreadedBST::copy_helper(BSTNode* other_node) {
	cout<<"hi\n";
	if(other_node == NULL) {
		return NULL;
	} else if(other_node){
		BSTNode* this_node = new BSTNode(other_node->key);
		this_node->rCount = other_node->rCount;
		this_node->leftLinkType = other_node->leftLinkType;
		this_node->rightLinkType = other_node->rightLinkType;
		this_node->left = copy_helper(other_node->left);
		this_node->right = copy_helper(other_node->right);
		return this_node;
	}
}

// Adds a given key to the BST
void ThreadedBST::insert(int x) {

	BSTNode* node = root;
	BSTNode* parentNode = NULL;

	// search the parent node of where the given x will be inserted 
	while (node != NULL) {

		if (x == (node->key)) {
			throw "ThreadedBST::Add() Key already exist";
			return;
		}

		parentNode = node;

		if (x < (node->key)) {
			if (node->leftLinkType == CHILD)
				node = node->left;
			else
				break;
		}

		else {
			if ((node->rightLinkType) == CHILD){
				node = node->right;
			}
			else
				break;
		}
	}

	//for increasing the count value
	//we can implement the rcount++ in the above while loop, but then 
	// it will cause the problem if we insert 10 elements and 9th element is actually already inserted element
	// 9th element will change the rCount value everywhere and in the last cause the problem and we won't be able to revert it
	node = root; parentNode = NULL;
	while (node != NULL) {

		if (x == (node->key)) {
			throw "ThreadedBST::Add() Key already exist";
			return;
		}

		parentNode = node;

		if (x < (node->key)) {
			if (node->leftLinkType == CHILD)
				node = node->left;
			else
				break;
		}

		else {
			node->rCount++;
			if ((node->rightLinkType) == CHILD){
				node = node->right;
			}
			else
				break;
		}
	}

	// set 
	BSTNode* tempNode = new BSTNode(x);

	// set left and right pointers and threads
	// first time called insert
	if (parentNode == NULL) {
		root = tempNode;
		tempNode->left = NULL;
		tempNode->right = NULL;	
	}

	else {

		// traverse to the left branch tree
		if (x < (parentNode->key)) {

			tempNode->left = parentNode->left;
			tempNode->right = parentNode;
			parentNode->leftLinkType = CHILD;
			parentNode->left = tempNode;
		}
		// traverse to the right branch of tree
		else {
			tempNode->left = parentNode;
			tempNode->right = parentNode->right;
			parentNode->rightLinkType = CHILD;
			parentNode->right = tempNode;
		}
	}
} 

// Removes a given key from the BST (if it exists)
void ThreadedBST::deleteNode(int key) {
	BSTNode* parentNode = root, *tempNode = root;

	// check for empty trees
	if (parentNode == NULL)
		return;

	else {

		//finding node to delete
		while (1) {

			// traverse to right for bigger keys
			if (tempNode->key < key) {
				tempNode->rCount--;
				//if there is no right child, this means element is not present
				if (tempNode->rightLinkType == THREAD) throw "element doesn't exist in tree";
				// reassign parentNode
				parentNode = tempNode;

				// traverse to right tree nodes
				tempNode = tempNode->right;
			}

			// traverse to left for smaller keys
			else if (tempNode->key > key) {
				//if there is no left child, this means element is not present
				if (tempNode->leftLinkType == THREAD) throw "element doesn't exist in tree";

				parentNode = tempNode;

				// traverse to the left
				tempNode = tempNode->left;
			}

			else {
				//comes in this section only if the node value matched and we found our node to be deleted
				break;
			}

		}

		//tempNode contains the node to be deleted
		BSTNode* node = tempNode;

		//both child exist, then we copy the predecessor to the node to be deleted and change the node to be deleted to predecessor node
		if (tempNode->rightLinkType != THREAD && tempNode->leftLinkType != THREAD) {

			parentNode = tempNode;

			// finding maximum predecessor - it will be on the left side, most right part of the tree
			// get max node 
			node = tempNode->left;

			while(node->rightLinkType != THREAD) {
				parentNode = node;
				node = node->right;
			}

			//copy the value of the predecessor to the node to be deleted
			tempNode->key = node->key;
		}

		// left side traversals
		if (parentNode->key > node->key) {
			// if left child is a leaf node
			if (node->rightLinkType== THREAD && node->leftLinkType == THREAD) {
				//changing parent pointers and type which parent is pointing
				parentNode->left = node->left;
				parentNode->leftLinkType = THREAD;
			}

			// if only left child exists
			else if (node->rightLinkType == THREAD) {
				//finding maximum in the left subtree
				BSTNode* maxNode = node->left;
				while (maxNode->rightLinkType != THREAD) {
					maxNode = maxNode->right;
				}
				//changing the successor of the max node in the left subtree, as the current successor of that being deleted
				maxNode->right = parentNode;
				//changing the left child of the parent node of the node being deleted to the left child of the node being deleted
				parentNode->left = node->left;
			}
			//if only right child exists
			else {
				//finding minimum node in the right subtree
				BSTNode* minNode = node->right;
				while (minNode->leftLinkType!= THREAD) {
					minNode = minNode->left;
				}
				
				//changing the predecessor of the min node in the right subtree, as the current predecessor of that being deleted
				minNode->left = node->left;
				//changing the left child of the parent node of the node being deleted to the right child of the node being deleted
				parentNode->left = node->right;
			}
		}

		else {
			//leaf case
			if(node->rightLinkType == THREAD && node->leftLinkType == THREAD) {

				parentNode->right = node->right;
				parentNode->rightLinkType = THREAD;
			}
			//only left child exists
			else if(node->rightLinkType == THREAD) {
				//find the maximum node in the left subtree
				BSTNode* maxNode = node->left;
				while(maxNode->rightLinkType != THREAD) {
					maxNode = maxNode->right;
				}

				//changing the right pointer of the max node to parent node, as the successor of the max is being deleted
				maxNode->right = node->right;
				//changing the right pointer of the parent node to the left child of the node to be deleted
				parentNode->right = node->left;
			}
			//only right child exists
			else {
				//finding the minimum node in the right subtree
				BSTNode* minNode = node->right;
				while (minNode->leftLinkType != THREAD) {
					minNode = minNode->left;
				}

				//changing the left pointer of the min node to parent node, as the predecessor of the min is being deleted
				minNode->left = parentNode;
				//changing the left pointer of the parent node to the right child of the node to be deleted
				parentNode->right = node->right;
			}
		}

		//remove node from the heap and free the memory
		delete node;
	}
}

// Searches a given key in the ThreadedBST
// Return a pointer to the node that holds the key
// If the key is not found, return NULL
BSTNode *ThreadedBST::search(int key) {
	BSTNode* temp = root;
	while (temp!=NULL) {
		if (temp->key == key) {
			return temp;
		}
		
		else if (temp->leftLinkType != THREAD && temp->key > key) {
			temp = temp->left;
		}

		else if (temp->rightLinkType!= THREAD && temp->key < key){
			temp = temp->right;
		}
		
		//leaf condition
		 else {
			return NULL;
			break;
		}
 	}
	 return NULL;
}

// Returns the minimum key in the ThreadedBST
// Return a pointer to the node that holds the key
// If the key is not found, return NULL
BSTNode* ThreadedBST::min() {
	BSTNode* temp = root;

	while(temp != NULL) {
		if (temp->left == NULL) {
			return temp;
		}	
		temp = temp->left;
	}

	return NULL;
}

// Returns the maximum key in the ThreadedBST
// Return a pointer to the node that holds the key
// If the key is not found, return NULL
BSTNode* ThreadedBST::max() {

	BSTNode* currNode = root;

	while (currNode != NULL) {

		if (currNode->right == NULL) {
			return currNode;
		}

		currNode = currNode->right;
	}

	return NULL;
} 

// Given a valid pointer to a node in the ThreadedBST,
// returns a pointer to the node that contains the inorder successor
// If the inorder successor does not exist, returns NULL 
BSTNode* ThreadedBST::next(BSTNode* node) {

	BSTNode* parentNode = node;

	//if the node doesn't have a right child, we directly go to the right child as it is sucessor
	if (node->rightLinkType == THREAD)
		node = node->right;

	//if it is not a thread, but pointing to child node. it means we have to find the minimum of the right child
	else {
		//find the minimum of the right child
		node = node->right;

		//finding minimum of the right child
		while (node->left != parentNode) {
			node = node->left;
		}
	}

	return node;
} 

// Given a valid pointer to a node in ThreadedBST,
// returns a pointer to the node that contains the inorder predecessor
// If the inorder predecessor does not exist, returns NULL
BSTNode* ThreadedBST::predecessor(BSTNode* node) { 

	BSTNode* parentNode = node;

	//if the node doesn't have a left child then the left node is pointer to the predecessor
	if (node->leftLinkType == THREAD)
		node = node->left;

	else {
		//if the node has a left child then the predecessor is in left tree with max value
		node = node->left;
		//right most element in left tree
		while (node->right != parentNode) {
			node = node->right;
		}
	}

	return node;
} 

// given a valid pointer to a node in ThreadedBST,
// returns a inorder successor key value
// If the inorder successor does not exist, returns -1
int ThreadedBST::successor(BSTNode* node) {
	BSTNode* parentNode = node;
	if (node->rightLinkType == THREAD)
		node = node->right;
	else {
		node = node->right;
		while (node->left != parentNode) {
			node = node->left;
		}
	}
	if(node)
		return node->key;
	else
		return INT_MIN;
} 

//finding all elements in between of a given k1 and k2
//returns singly linkedlist head
LLNode* ThreadedBST::allElementsBetween(int k1, int k2) {
	//finding the k1 node
    BSTNode* k1Node = search(k1);
	if(k1Node!=NULL) {
		LLNode *head = new LLNode(k1Node->key);
		LLNode *current = head;
		while(k1Node->key != k2){
			k1Node = next(k1Node);
			current->next = new LLNode(k1Node->key);
			current = current->next;
		}

		if(k1Node->key == k2) return head;
	} 
	//k1 doesn't exist
	else {
		throw "entered value k1 does not exists in tree";
	}
	return NULL;
}

// Returns the reverse inorder of the bst
LLNode* ThreadedBST::reverseInorder() {
    BSTNode *p = this->max();
    LLNode* head = new LLNode(p->key);
    p = this->predecessor(p);
    LLNode *temp = head;
    while(p){
        temp->next = new LLNode(p->key);
        temp = temp->next;
        p = this->predecessor(p);

    }
    return head;
}

//split function takes valid k and then split the tree into left and right subtrees
void ThreadedBST::split(int k, ThreadedBST*& left, ThreadedBST*& right) {
    LLNode *fHead = this->inorder();
    LLNode *firstTree = fHead;

    //finding k value node in inorder traversal
    while(firstTree->data <= k) {
        firstTree = firstTree->next;
	}
	
    LLNode *secondTree = firstTree->next, *sHead = secondTree;
    firstTree->next = NULL;
	firstTree = fHead;

    left = new ThreadedBST();
    right = new ThreadedBST();
    while(firstTree != NULL ) {
        left->insert(firstTree->data);
        firstTree = firstTree->next;
	}
    
    while(secondTree != NULL) {
		right->insert(secondTree->data);
        secondTree = secondTree->next;
	}
	
}

//inorder of the given bst 
LLNode* ThreadedBST::inorder() {
	//starting from the minimum node
    BSTNode *p = this->min();
    LLNode* head = new LLNode(p->key);
	
	//traversing the tree
    p = this->next(p);
    LLNode *temp = head;
    while(p){
        temp->next = new LLNode(p->key);
        temp = temp->next;
        p = this->next(p);
    }

    return head;
}

//utility function to find kth largest element in the tree
BSTNode* kthElementUtil(BSTNode* node, int k) {
	if(!node) return NULL;
	
	int count = node->rCount+1;
	if(count == k) return node;

	if(count > k) return kthElementUtil(node->right, k);
	
	return kthElementUtil(node->left, k-count);
}

//kth largest element in the bst
int ThreadedBST::kthElement(int k) {
	
	BSTNode* found =kthElementUtil(this->root, k);
	if(found == NULL) cout<<"hi null";
	return found ? found->key : INT_MIN;
	
	// O(n) solution	
	// int count = 0;
    // BSTNode *last = this->max();

	// //traversing the tree in reverse order until count value becomes k
    // while(++count != k){
    //     last = this->predecessor(last);
    // }

	// // if count value is k, return the key of the last node
    // if(count == k) return last->key;
}

// writing the node to the file
void printNode(BSTNode* node, ofstream& outFile) {
	//if it's leaf return from there
	if(node->leftLinkType == THREAD && node->rightLinkType == THREAD) return;

	//if it's not leaf and it has left child
	if(node->left != NULL && node->leftLinkType == CHILD) {
		outFile << "\tnode"<<node->left->key<<"[label=\""<<node->left->key<<"\"]" << endl;
		outFile << "\t\"node" << node->key << "\" -> \"node" << node->left->key << "\"" << endl;

		//recursively call the function for left child
		printNode(node->left, outFile);
	}
	//if it's not leaf and it has right child
	if(node->right != NULL && node->rightLinkType == CHILD) {
		outFile << "\tnode"<<node->right->key<<"[label=\""<<node->right->key<<"\"]" << endl;
		outFile << "\t\"node" << node->key << "\" -> \"node" << node->right->key << "\"" << endl;
		//recursively call the function for right child
		printNode(node->right, outFile);
	}
}

// printing the tree using graphwiz
void ThreadedBST::printTree() {
	BSTNode* temp = root;
	ofstream outFile;

	//source file
	outFile.open("graph.gv");
	
	//source code for printing the tree
	outFile << "digraph BST {" << endl;
	outFile << "\tnode"<<temp->key<<"[label=\""<<temp->key<<"\"]" << endl;
	//function which writes the nodes code into the file
	printNode(temp, outFile);
	outFile << "}" << endl;

	//calling the system command to generate the tree png 
	system("dot -Tpng graph.gv -o graph.png");

	//removing the source (graph.gv) file
	remove("graph.gv");
	outFile.close();
}