#include "Treap.h"
#include <iostream>
#include <fstream>

using namespace std;

//constructor for Treap
Treap::Treap(){
    dummy = new TreapNode(INT_MIN);
    dummy->left = dummy->right = dummy;
    dummy->priority = INT_MAX;
    root = dummy;
}

//copy constructor
Treap::Treap(const Treap &obj){
    root = clone(obj.root);
}

//operator overloading
Treap& Treap::operator=(const Treap &obj){
    if(this->root != obj.root){
        destroyTreap(this->root);
        root = clone(obj.root);
    }
    return *this;
}

//clone function to deep copy the tree
TreapNode* Treap::clone(TreapNode *root){
    if(root == NULL)
        return NULL;
    //create new node with same value
    TreapNode *new_node = new TreapNode(root->key);
    //clone left subtree, recursively
    new_node->left = clone(root->left);
    //clone right subtree, recursively
    new_node->right = clone(root->right);
    //copy priority
    new_node->priority = root->priority;
    return new_node;
}

//destructor
Treap::~Treap(){
    //calling function to destroy each node
    destroyTreap(root);

    delete dummy;
}

//recursive helper function to destroy the nodes of the tree
void Treap::destroyTreap(TreapNode *&node){
    if(node == dummy) return;
    
    if(node != NULL){
        //destroying left subtree
        destroyTreap(node->left);
        //destroying right subtree
        destroyTreap(node->right);

        //deleting root
        delete node;
    }
}

//left rotation
void Treap::L_Rotate(TreapNode *&node){
    totalRotation++;
    TreapNode *q = node->left; //q is the left child of node
    node->left = q->right; //node's left child becomes q's right child
    q->right = node; //q's right child becomes node
    node = q; //node becomes q
}

void Treap::R_Rotate(TreapNode *&node){
    totalRotation++;
    TreapNode *q = node->right; //q is the right child of node
    node->right = q->left; //node's right child becomes q's left child
    q->left = node; //q's left child becomes node
    node = q; //node becomes q
}

//recursive insertion helper function 
void Treap::insertionHelper(TreapNode *&node, int key, int p){
    //if node is dummy node, create a new node with key
    totalComparisons++;
    if (node == dummy) {
        //creating new node with given key
        node = new TreapNode(key, p);
        cout<<"Treap::Insertion of "<<key<<" is successful\n";
        //setting left and right tree as dummy tree
        node->left = node->right = dummy;
    } else if (key < node->key) {
        //inserting in left subtree if key is less than node's key
        insertionHelper(node->left, key, p);
        //if left subtree's priority is greater than node's priority, rotate left
        if (node->left->priority < node->priority) L_Rotate(node);
    } else if(key > node->key){
        //inserting in right subtree if key is greater than node's key
        insertionHelper(node->right, key, p);
        //if right subtree's priority is greater than node's priority, rotate right
        if (node->right->priority < node->priority) R_Rotate(node);
    }else{
        //element exists
        cout<<"Treap::Element already exist\n";
    }
}

//inserting node in the tree
bool Treap::insertNode(int key, int priority){
    try{
        //calling insertion function
        insertionHelper(root, key, priority);
        totalNodes++;
        return true;
    }catch(const char* e){
        throw e;
    }
}

//overloaded recursive helper function to delete node
void Treap::deletionHelper(TreapNode *&node){
    //if node is leaf node than delete it
    if (node->left == dummy && node->right == dummy) {
        delete node;
        totalNodes--;
        node = dummy;
        return;
    }

    //update the balance factor if reqiured
    if (node->left->priority < node->right->priority) {
        L_Rotate(node);
        deletionHelper(node->right);
    } else {
        R_Rotate(node);
        deletionHelper(node->left);
    }
}

//overloaded recursive function: deleting node with given key
void Treap::deletionHelper(TreapNode *&node, int key){
    totalComparisons++;
    //if node is dummy node, return
    if (node == dummy) return;

    //if key found than delete the node
    if (node->key == key){
        deletionHelper(node);
        cout<<"Treap::Deletion of "<<key<<" is successful\n";
    }
    
    //if key is less than node's key, search in left subtree
    else if (key < node->key){
        deletionHelper(node->left, key);
    }
    
    //if key is greater than node's key, search in right subtree
    else if (key > node->key){
        deletionHelper(node->right, key);
    }
}

//deleting node with given key
void Treap::deleteNode(int key){
    deletionHelper(root, key);
}

//helper function to search node
bool Treap::searchHelper(TreapNode *&node, int key){
    //if we found dummy node before finding actual node, return false
    if (node == dummy) return false;

    //if key found, return true
    if (key == node->key) return true;

    //calling recursive function to search
    return (key < node->key) ? searchHelper(node->left, key) : searchHelper(node->right, key);
}

//searching node with given key
bool Treap::searchNode(int key){
    return searchHelper(root, key);
}

//recursive helper function to print node
void Treap::inorder(TreapNode *&node){
    if(!node || node == dummy) return;

    inorder(node->left);
    cout<<node->key<<" {"<<node->priority<<"}, ";
    inorder(node->right);
}

//printing the tree inorder
void Treap::inorderTraversal(){
    inorder(root);
}

//recursive function to get height of the node
int Treap::getHeight(TreapNode *&node){
    if(!node || node == dummy) return -1;

    return max(getHeight(node->left), getHeight(node->right)) + 1;
}

//total height helper
int Treap::totalHeightHelper(TreapNode *&node){
    if(!node || node == dummy) return 0;

    return totalHeightHelper(node->left) + getHeight(node) + totalHeightHelper(node->right);
}

int Treap::size(){
    return totalNodes;
}

//driver fucntion to call calculate and return total height
double Treap::findAvgHeightofEachNode(){
    int tH = totalHeightHelper(root);
    // cout<<"totalheight: "<<tH<<" size of treap: "<<size()<<endl;
    if(size()!= 0)
        return tH/(double) size();
    return 0;
}

//function to get height of tree
int Treap::heightOfTree(){
    return getHeight(root);
}

// writing the node to the file
void Treap::printNode(TreapNode *&node, ofstream &outFile){
     //if it's leaf return from there
	if((node->left == NULL && node->right == NULL) || (node->left == dummy && node->right == dummy)) return;
	//if it's not leaf and it has left child
	if((node->left != NULL || node->left != dummy) && node->left->key != INT_MIN){
        // if(node->left->key == INT_MIN)
		outFile << "\t"<<node->left->key<<"[label=\""<<node->left->key<<" {"<<node->left->priority<<"}\"]" << endl;
		outFile << "\t\"" << node->key << "\" -> \"" << node->left->key <<"\"" << endl;

		//recursively call the function for left child
        if(node->left != dummy)
		    this->printNode(node->left, outFile);
	}
	//if it's not leaf and it has right child
	if((node->right != NULL || node->right != dummy) && node->right->key != INT_MIN){
		outFile << "\t"<<node->right->key<<"[label=\""<<node->right->key<<" {"<<node->right->priority<<"}\"]" << endl;
		outFile << "\t\"" << node->key << "\" -> \"" << node->right->key <<"\"" << endl;
		//recursively call the function for right child
        if(node->right != dummy)
		    this->printNode(node->right, outFile);
	}
}

// printing the tree using graphwiz
void Treap::printTree(const char* filename) {
	TreapNode* temp = root;
	ofstream outFile;
    if(root == NULL || root == dummy) {
        cout<<"Tree is empty\n";
        return;
    }
	//source file
	outFile.open("graph.gv");
	//source code for printing the tree
	outFile << "digraph BST {" << endl;
	outFile << "\t"<<temp->key<<"[label=\""<<temp->key<<" {"<<temp->priority<<"}\"]" << endl;
	//function which writes the nodes code into the file
	this->printNode(temp, outFile);
	outFile << "}" << endl;

	//calling the system command to generate the tree png 
    char command[30];
    strcpy(command, "dot -Tpng graph.gv -o ");
    strcat(command, filename);
	system(command);

	#ifdef _WIN32
		system(filename);
	#endif

	//removing the source (graph.gv) file
	remove("graph.gv");
	outFile.close();

	cout<<"PNG file is generated\n";
}

long int Treap::getComparisons(){
    return totalComparisons;
}

long int Treap::getRotations(){
    return totalRotation;
}