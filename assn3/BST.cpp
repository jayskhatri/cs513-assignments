#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include "BST.h"
using namespace std;

BST::BST(){
    root = NULL;
}

//destructor
BST::~BST(){
    //calling function to destroy each node
    destroyBST(root);
}

//operator overloading
BST& BST::operator=(const BST &obj){
    if(this->root != obj.root){
        destroyBST(this->root);
        root = clone(obj.root);
    }
    return *this;
}

//recursive helper function to destroy the nodes of the tree
void BST::destroyBST(BSTNode *&node){
    if(!node) return;
    
    if(node != NULL){
        //destroying left subtree
        destroyBST(node->left);
        //destroying right subtree
        destroyBST(node->right);

        //deleting root
        delete node;
    }
}

//clone function to deep copy the tree
BSTNode* BST::clone(BSTNode *root){
    if(root == NULL)
        return NULL;
    //create new node with same key
    BSTNode *new_node = new BSTNode(root->key);
    //clone left subtree, recursively
    new_node->left = clone(root->left);
    //clone right subtree, recursively
    new_node->right = clone(root->right);
    return new_node;
}

void BST::addNode(int key)
{
    totalComparisons++;
    if (!root) {
        root = new BSTNode(key);
        totalNodes++;
        return;
    }

    addChildNode(root, key);
}

void BST::addChildNode(BSTNode *parent, int key){
    totalComparisons++;
    if (!parent) {
        cout<<"parent can't be null\n";
    }

    if (key < parent->key) {
        if (parent->left) {
            addChildNode(parent->left, key);
        }
        else {
            parent->left = new BSTNode(key);
            cout<<"BST:: Insertion of "<<key<<" is successful\n";
            totalNodes++;
        }
    }
    else if(key > parent->key){
        if (parent->right) {
            addChildNode(parent->right, key);
        }
        else {
            parent->right = new BSTNode(key);
            totalNodes++;
        }
    }

    else if(key == parent->key){
        cout<<"BST:: key "<<key<<" already exists\n";
    }
}

void BST::deleteNode(int key){
    deleteChildNode(nullptr, root, key);
}

void BST::deleteChildNode(BSTNode *parent, BSTNode *current, int key){
    totalComparisons++;
    if (!current) {
        cout<<"can't delete, no node exists with value "<<key<<endl;
        return;
    }

    if (current->key == key) {
        if (current->left || current->right) { 
            // cout<<"current: "<<current->key<<endl;
            if (!current->left || !current->right) { //one child
                BSTNode* child = current->left ? current->left : current->right;

                if (parent) {
                    if (parent->left == current) {
                        parent->left = child;
                    }
                    else {
                        parent->right = child;
                    }
                }
                else {
                    root = child;
                }

                delete current;
            }
            else { //two children
                // cout<<"both children exists current: "<<current->key<<"\n";
                BSTNode* nearestSuccessorParent = current;
                BSTNode* nearestSuccessor = findNearestSuccessor(current, &nearestSuccessorParent);
                // cout<<"nearest successor: "<<nearestSuccessor->key<<" parent: "<<nearestSuccessorParent->key<<"\n";
                current->key = nearestSuccessor->key;
                if (nearestSuccessorParent->left == nearestSuccessor) {
                    nearestSuccessorParent->left = nearestSuccessor->right;
                }
                else {
                    nearestSuccessorParent->right = nearestSuccessor->right;
                }

                delete nearestSuccessor;
            }
        }
        else { //no children, i.e. leaf
            if (parent) {
                if (parent->left == current) {
                    parent->left = nullptr;
                }
                else {
                    parent->right = nullptr;
                }
            }
            else {
                root = nullptr;
            }

            delete current;
        }
        totalNodes--;
        cout<<"BST:: Deletion of "<<key<<" is successful\n";
    }
    else {
        if(key < current->key){
            // cout<<"checking for left subtree\n";
            deleteChildNode(current, current->left, key);
        }
        else{
            // cout<<"checking for right subtree\n";
            deleteChildNode(current, current->right, key);
        }
    }
}

BSTNode* BST::findNearestSuccessor(BSTNode* current, BSTNode** parent){
    if (!current || !current->right) {
        throw logic_error("Error: cannot find nearest greater. Invalid current node");
    }

    *parent = current;
    current = current->right;

    while (current->left) {
        *parent = current;
        current = current->left;
    }

    return current;
}


// writing the node to the file
void BST::printNode(BSTNode*& node, ofstream& outFile) {
	//if it's leaf return from there
	if(node->left == NULL && node->right == NULL) return;
	//if it's not leaf and it has left child
	if(node->left != NULL) {
        // cout<<"left: "<<node->left->key<<"\n";
		outFile << "\t"<<node->left->key<<"[label=\""<<node->left->key<<"\"]" << endl;
		outFile << "\t\"" << node->key << "\" -> \"" << node->left->key <<"\"" << endl;

		//recursively call the function for left child
		this->printNode(node->left, outFile);
	}
	//if it's not leaf and it has right child
	if(node->right != NULL) {
        // cout<<"right: "<<node->right->key<<"\n";
		outFile << "\t"<<node->right->key<<"[label=\""<<node->right->key<<"\"]" << endl;
		outFile << "\t\"" << node->key << "\" -> \"" << node->right->key <<"\"" << endl;
		//recursively call the function for right child
		this->printNode(node->right, outFile);
	}
}

// printing the tree using graphwiz
void BST::BST_Print(const char* filename) {
	BSTNode* temp = root;
	ofstream outFile;
    if(temp == NULL) cout<<"Tree is empty\n";
	//source file
	outFile.open("graph.gv");
	//source code for printing the tree
	outFile << "digraph BST {" << endl;
	outFile << "\t"<<temp->key<<"[label=\""<<temp->key<<"\"]" << endl;
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

void BST::traverse() {
    cout<<endl<<"inorder - ";
    traverse(root);
    std::cout << std::endl;
}

void BST::traverse(BSTNode* current) {
    if(current) {
        traverse(current->left);
        std::cout << current->key <<" ";
        traverse(current->right);
    }
}

//recursive function to get height of the node
int BST::getHeight(BSTNode *&node){
    if(!node) return -1;

    return max(getHeight(node->left), getHeight(node->right)) + 1;
}

//total height helper
int BST::totalHeightHelper(BSTNode *&node){
    if(!node) return 0;

    return totalHeightHelper(node->left) + getHeight(node) + totalHeightHelper(node->right);
}

int BST::size(){
    return totalNodes;
}

//driver fucntion to call calculate and return total height
double BST::findAvgHeightofEachNode(){
    int tH = totalHeightHelper(root);
    // cout<<"totalheight: "<<tH<<" size of bst: "<<size()<<endl;
    if(size() != 0)
        return tH/(double) size();
    return 0;
}

//function to get height of tree
int BST::heightOfTree(){
    return getHeight(root);
}

long int BST::getComparisons(){
    return totalComparisons;
}