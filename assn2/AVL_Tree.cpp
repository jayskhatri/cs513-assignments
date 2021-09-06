#include<bits/stdc++.h>
#include<fstream>
#include "AVL_Tree.h"

using namespace std;

//default constructor
AVL_Tree::AVL_Tree(){
    root = NULL;
}

//copy constructor
AVL_Tree::AVL_Tree(const AVL_Tree &obj){
    root = clone(obj.root);
}

//operator overloading
AVL_Tree& AVL_Tree::operator=(const AVL_Tree &obj){
    if(this->root != obj.root){
        destroyAVL(this->root);
        root = clone(obj.root);
    }
    return *this;
}

//clone function to deep copy the tree
AVL_Node* AVL_Tree::clone(AVL_Node *root){
    if(root == NULL)
        return NULL;
    AVL_Node *new_node = new AVL_Node(root->key);
    new_node->LChild = clone(root->LChild);
    new_node->RChild = clone(root->RChild);
    new_node->bf = root->bf;
    return new_node;
}

//recursive helper function to destroy the nodes of the tree
void AVL_Tree::destroyAVL(AVL_Node *&root){
    if(root != NULL){
        destroyAVL(root->LChild);
        destroyAVL(root->RChild);
        delete root;
    }
}

//destructor
AVL_Tree::~AVL_Tree(){
    //calling recursive helper function to destroy all the nodes of the tree
    destroyAVL(root);
}

// right rotation
void  AVL_Tree::R_Rotate (AVL_Node *&node) {
    AVL_Node *lc = node->LChild; // LC pointing left child node of passed node
    node->LChild = lc->RChild; // right subtree node set lc p junction left subtree
    lc->RChild = node; // set the node as the right child node of lc
    node = lc; // node points to the new root node i.e. lc
}

// left rotation
void AVL_Tree::L_Rotate(AVL_Node *&node) {
    AVL_Node *rc = node->RChild ;
    node->RChild = rc->LChild ;
    rc->LChild = node;
    node = rc;
}

// LL rotation or RL rotation, depending on the T's right child balance factor
void AVL_Tree::RightBalance (AVL_Node *&T) {
    AVL_Node *rc, *ld;
    rc = T-> RChild ;
    switch (rc-> bf) {
        /*
        Case where left child (C) has balance factor -1
            T(1) this should be balanced
                \
                C(1) T's left child has -1
                    \
                    D(0)(new added)
        */
        case -1:
            T-> bf = rc-> bf = 0;
            L_Rotate (T);
            break ;
        
        /*
        Case where left child (C) has balance factor 1
            T(1) this should be balanced
                \
                C(1) T's left child has 1
                /
            D(0)(new added)
        */
        case 1:
            ld = rc->LChild;
            switch (ld-> bf) {
                case -1:
                    T->bf = 1;
                    rc->bf = 0;
                    break ;
                case 0:
                    T->bf = rc->bf = 0;
                    break ;
                case 1:
                    T->bf = 0;
                    rc->bf = -1;
                    break ;
            }
            ld->bf = 0;
            R_Rotate(T->RChild);
            L_Rotate(T);
            break ;
    }
}

//R rotation or LR rotation depending on the balance factor of the left child of T node
void  AVL_Tree::LeftBalance (AVL_Node *&T) {
    AVL_Node *lc, *rd;
    lc = T-> LChild;
    switch (lc-> bf) {
        
        /*
            Case where left child has balance factor 1
                    T(1) this should be balanced
                    /
                C(1) T's left child has 1
                /
            D(0)(new added)
        */
        case 1: {
            T-> bf = lc-> bf = 0;
            R_Rotate (T);
            break ;
        } 
        
        /*
            Case where left child has balance factor -1
                T(1) this should be balanced
                /
            C(-1) T's left child has -1
                \
                D(0)(new added)
        */
        case -1: {
            rd = lc-> RChild ;
            switch (rd-> bf) {
                case 1: {
                    T-> bf = -1;
                    lc-> bf = 0;
                    break;
                } 
                case 0: {
                    T-> bf = lc-> bf = 0;
                    break ;
                } 
                case -1: {
                    T-> bf = 0;
                    lc-> bf = 1;
                    break ;
                }
            }
            rd-> bf = 0;
            L_Rotate (T-> LChild);
            R_Rotate (T);
            break;
        }
    }
}

//recursive helper function which insert node into tree, taller is used to check if the balancing is required or not
int AVL_Tree::insertHelper(AVL_Node*& root, int key, int &taller){
    if(root == NULL){
        root = new AVL_Node(key);
        taller = true;
    }else if(key == root->key){
        taller = false;
        return false;
    }
    //insert into left subtree
    else if(key < root->key){
        if(insertHelper(root->LChild, key, taller) == false){
            return false;
        }

        //check whether the height has been increased or not
        if(taller == true){
            switch (root->bf){
                //case 1
                //case when the new node has been inserted into the left subtree of the tree and the root was already having the balance factor of 1
                //so now on inserting the new node into the left subtree it there came imbalance and we have to do the LR rotation
                //after balancing height has been the same so taller = false.
                case 1:
                    {
                        LeftBalance(root);
                        taller = false;
                        break;
                    } 

                //case 2
                //on adding the new node to left side when the root was having the balance factor of 0
                //so now balance factor will change to 1 and height has been increased so taller will be true
                case 0:
                    {
                        root->bf = 1;
                        taller = true;
                        break;
                    }
                
                //case 3
                //if it was previously having more height in the right subtree than adding the node into the left subtree will make it more balanced
                //so balance factor of root will become now 0 and height will be balanced so taller = false.
                case -1:
                    {
                        root->bf = 0;
                        taller = false;
                        break;
                    }
            }
        }
    }
    //insert into right subtree
    else{
        if(insertHelper(root->RChild, key, taller) == false){
            return false;
        }

        if(taller == true){
            switch (root->bf){
                
                //case 1
                //if it was previously having more height in the left subtree than adding the node into the right subtree will make it more balanced
                //so balance factor of root will become now 0 and height will be balanced so taller = false.
                case 1:
                    {
                        root->bf = 0;
                        taller = false;
                        break;
                    }

                //case 2
                //on adding the new node to right side when the root was having the balance factor of 0
                //so now balance factor will change to -1 and height has been increased so taller will be true
                case 0:
                    {
                        root->bf = -1;
                        taller = true;
                        break;
                    }
                
                //case 3
                //case when the new node has been inserted into the right subtree of the tree and the root was already having the balance factor of -1
                //so now on inserting the new node into the right subtree it there came imbalance and we have to do the RL rotation
                //after balancing height has been the same so taller = false.
                case -1:
                    {
                        RightBalance(root);
                        taller = false;
                        break;
                    }        
            }
        }
    }

    return true;
}

//insert function
void AVL_Tree::AVL_Insert(int key){
    if(AVL_Search(key) == true){
        throw "Key already exists in the tree";
    }else {
        int taller = 0;
        insertHelper(root, key, taller);
    }
}

//search function
bool AVL_Tree::AVL_Search(int key){
    AVL_Node *temp = root;

    while(temp!=NULL){
        if(temp->key == key){
            return true;
        }
        else if(temp->key > key){
            temp = temp->LChild;
        }
        else{
            temp = temp->RChild;
        }
    }

    return false;
}

//link function gives the child node which side balancing is required 
AVL_Node* AVL_Tree::link(AVL_Node *P, int a){
    return a == 1 ? P->LChild : P->RChild;
}

void AVL_Tree::AVL_Delete(int key){
    AVL_Node *n = root; 
	
    // base case
    if(n == NULL) throw "No element exists to be deleted";

	// balance - AVL_Node to be balanced
	// parent - parent of the AVL_Node to be balanced
	// child - left/right child of the AVL_Node to be balanced
    // d - dummy node to handle the rotation on root node

	AVL_Node *balance, *parent, *child, *d = new AVL_Node(INT_MIN);
    AVL_Node *t;//temporary node
    d->RChild = n;
	bool exists = false;

    stack<AVL_Node*> rootToNode;
	rootToNode.push(d);

    //finding node to be deleted and tracking path from root to node in rootToNode
	while(n){
		if(key > n->key){
			rootToNode.push(n);
			n = n->RChild;
		}
        else if(key < n->key){
			rootToNode.push(n);
			n = n->LChild;
		}
		else if(n->key == key){
			exists = true;
			break;
		}
	}
    //if node with given key does not exists
	if(!exists) delete d, throw "Element to be deleted does not exist";
	
    else{
		
		// AVL_Node to be deleted has both the children
		if(n->LChild && n->RChild){
            rootToNode.push(n);
            AVL_Node *pred = n->LChild;
            while(pred->RChild){
                rootToNode.push(pred);
                pred = pred->RChild;
            }

            n->key = pred->key;
            key = pred->key;
            AVL_Node *temp = pred->RChild ? pred->RChild : pred->LChild;
            AVL_Node *parent = rootToNode.top();

            //if pred has no child
            if(!temp){
                temp = pred;

                if(parent->LChild == pred)
                    parent->LChild = nullptr;
                else parent->RChild = nullptr;

                pred = nullptr;
            }
            
            //if pred has one child
            else {
                pred->key = temp->key;
                pred->LChild = temp->LChild;
                pred->RChild = temp->RChild;
                pred->bf = temp->bf;
            }
            
            delete temp;
		}
        // if parent has a single child or no child (leaf)
		if(!n->LChild || !n->RChild){
			AVL_Node *temp = n->LChild ? n->LChild : n->RChild;
			AVL_Node *par = rootToNode.top();
            
            //if n has no child
			if(!temp){
				temp = n;
                
                //incase the root itself is being deleted
                if(d == rootToNode.top()) this->root = nullptr;

				if(n == par->LChild)
					par->LChild = nullptr;
				else par->RChild = nullptr;
				n = nullptr;
			}

            //if n has only one child
			else{
				n->key = temp->key;
				n->bf = temp->bf;
				n->LChild = temp->LChild;
				n->RChild = temp->RChild;
			}
			delete temp;
		}
	}

    //processing the path from root to node and balancing the tree
	while(rootToNode.top() != d){
		balance = rootToNode.top();
		rootToNode.pop();
		parent = rootToNode.top();

        int a = key < balance->key ? 1 : -1;

		if(balance->bf == a){
            child = link(balance, balance->bf);
            if(child)
                if(child->bf == -1 || child->bf == 1)
                    balance->bf = a;
                else balance->bf = 0;
            else balance->bf = 0;
			continue;
		}
		else if(balance->bf == 0){
			balance->bf = -1*a;
            delete d;
			return;
		}
		else{
			child = link(balance, balance->bf);
			//single rotation
			if(child->bf == -1*a){
				if(a == -1){
					n = child;
                    //storing actual node
                    t = balance;
                    R_Rotate(balance);
                    //restoring it
                    balance = t;

                    //updating balance factors
					balance->bf = child->bf = 0;
				}
				else if(a == 1){
					n = child;
                    //storing actual node
                    t = balance;
                    L_Rotate(balance);
                    //restoring it
                    balance = t;

                    //updating balance factors
					balance->bf = child->bf = 0;
				}
			}
			//single rotation
			else if(child->bf == 0){
				if(a == -1){
					n = child;
                    t = balance;
                    R_Rotate(balance);
                    balance = t;
					child->bf = a; 
				}
				else if(a == 1){
					n = child;
                    t = balance;
                    L_Rotate(balance);
                    balance = t;
					child->bf = a;
				}
			}
			//double rotation
			else if(child->bf == a){
                //LR rotation
				if(a == -1){
					n = child->RChild;
                    LeftBalance(balance);
				}
                //RL rotation
				else if(a == 1){
                    n = child->LChild;
                    t = balance;
                    RightBalance(balance);
                    balance = t;
				}
			}
		}
        
        if(balance == parent->RChild) parent->RChild = n;
        else parent->LChild = n;	

        if(parent == d) root = n;
	}
    delete d;	
}

// writing the node to the file
void AVL_Tree::printNode(AVL_Node*& node, ofstream& outFile) {
	//if it's leaf return from there
	if(node->LChild == NULL && node->RChild == NULL) return;
	//if it's not leaf and it has left child
	if(node->LChild != NULL) {
		outFile << "\t"<<node->LChild->key<<"[label=\""<<node->LChild->key<<" {"<<node->LChild->bf<<"}\"]" << endl;
		outFile << "\t\"" << node->key << "\" -> \"" << node->LChild->key <<"\"" << endl;

		//recursively call the function for left child
		this->printNode(node->LChild, outFile);
	}
	//if it's not leaf and it has right child
	if(node->RChild != NULL) {
		outFile << "\t"<<node->RChild->key<<"[label=\""<<node->RChild->key<<" {"<<node->RChild->bf<<"}\"]" << endl;
		outFile << "\t\"" << node->key << "\" -> \"" << node->RChild->key <<"\"" << endl;
		//recursively call the function for right child
		this->printNode(node->RChild, outFile);
	}
}

// printing the tree using graphwiz
void AVL_Tree::AVL_Print(const char* filename) {
	AVL_Node* temp = root;
	ofstream outFile;

	//source file
	outFile.open("graph.gv");
	//source code for printing the tree
	outFile << "digraph BST {" << endl;
	outFile << "\t"<<temp->key<<"[label=\""<<temp->key<<" {"<<temp->bf<<"}\"]" << endl;
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