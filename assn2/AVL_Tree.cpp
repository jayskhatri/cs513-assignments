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
        return;
    }else {
        int taller = 0;
        cout<<"insertion: "<<insertHelper(root, key, taller)<<endl;
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


//     // if(AVL_Search(key) == false){
//     //     cout << "The key is not in the tree" << endl;
//     // }else {
//     //     int shorter = 0;
//     //     cout<<"ans: "<<deleteHelper(root, key, shorter)<<"\n";
//     // }

//link function gives the child node which side balancing is required 
AVL_Node* AVL_Tree::link(AVL_Node *P, int a){
    return a == 1 ? P->LChild : P->RChild;
}

void AVL_Tree::AVL_Delete(int key){
    AVL_Node *n = root; 
	
	// b -> AVL_Node to be balanced
	// p -> parent of the AVL_Node to be balanced
	// c -> left/right child of the AVL_Node to be balanced
	AVL_Node *b, *p, *c, *h = new AVL_Node(INT_MIN);
    AVL_Node *t;
    h->RChild = n;
	bool exists = false;

	stack<AVL_Node*> path;
	path.push(h);

	if(n == NULL) throw "No element exists to be deleted";

	while(n){
		if(key > n->key){
			path.push(n);
			n = n->RChild;
		}
        else if(key < n->key){
			path.push(n);
			n = n->LChild;
		}
		else if(n->key == key){
			exists = true;
			break;
		}
	}
	if(!exists) throw "Element to be deleted does not exist";
	else{
		// if p has a single child or no child (leaf)
		if(!n->LChild || !n->RChild){
			AVL_Node *temp = n->LChild ? n->LChild : n->RChild;
			AVL_Node *par = path.top();

			if(!temp){
				temp = n;
				if(n == par->LChild)
					par->LChild = nullptr;
				else par->RChild = nullptr;
				n = nullptr;
			}
			else{
				n->key = temp->key;
				n->bf = temp->bf;
				n->LChild = temp->LChild;
				n->RChild = temp->RChild;
			}
			delete temp;
		}
		// AVL_Node to be deleted has both the children
		else{
            path.push(n);
            AVL_Node *pred = n->LChild;
            while(pred->RChild){
                path.push(pred);
                pred = pred->RChild;
            }

            n->key = pred->key;
            key = pred->key;
            AVL_Node *temp = pred->RChild ? pred->RChild : pred->LChild;
            AVL_Node *parent = path.top();

            if(!temp){
                temp = pred;

                if(parent->LChild == pred)
                    parent->LChild = nullptr;
                else parent->RChild = nullptr;

                pred = nullptr;
            }else {
                pred->key = temp->key;
                pred->LChild = temp->LChild;
                pred->RChild = temp->RChild;
                pred->bf = temp->bf;
            }
            
            delete temp;

            //----> n is not being deleted
			// path.push(n);
			// AVL_Node *succ = n->RChild; //finding the successor of n
			// while(succ->LChild){
			// 	path.push(succ);
			//  	succ = succ->LChild;
			// }
			// n->key = succ->key;
			// key = succ->key; // because the AVL_Node that is being deleted is the successor
			// AVL_Node *temp = succ->LChild ? succ->LChild : succ->RChild;
			// AVL_Node *par = path.top();

			// if(!temp){
			// 	temp = succ;
			// 	if(succ == par->LChild)
			// 		par->LChild = nullptr;
			// 	else par->RChild = nullptr;
			// 	succ = nullptr;
			// }
			// else{
			// 	succ->key = temp->key;
			// 	succ->bf = temp->bf;
			// 	succ->LChild = temp->LChild;
			// 	succ->RChild = temp->RChild;
			// }
			// delete temp;
		}
	}

	while(path.top() != h){
		b = path.top();
		int a = key < b->key ? 1 : -1;
		path.pop();
		p = path.top();

        // cout<<"b->bf: "<<b->bf << " p->bf: "<<p->bf<<" a: "<<a<<"\n";
		if(b->bf == a){
            // cout<<"1 if: b->bf: "<<b->bf<<" a: "<<a<<"\n";
            c = link(b, b->bf);
            if(c)
                if(c->bf == -1 || c->bf == 1)
                    b->bf = a;
                else b->bf = 0;
            else b->bf = 0;
			continue;
		}
		else if(b->bf == 0){
            // cout<<"2 if: b->bf: "<<b->bf<<" a: 0"<<"\n";
			b->bf = -1*a;
			return;
		}
		else{
            // cout<<"3 else: b->bf: "<<b->bf<<" a: "<<a<<"\n";
			c = link(b, b->bf);
			//single rotation
			if(c->bf == -1*a){
                // cout<<"3.1 if: c->bf: "<<c->bf<<" a: "<<a<<"\n";
				if(a == -1){
                    // cout<<"3.1.1 if a: "<<a<<"\n";
					n = c;
                    t = b;
                    // cout<<"rc->bf: "<<-1*a<<endl;
                    R_Rotate(b);
                    b = t;
					b->bf = c->bf = 0;
				}
				else if(a == 1){
                    // cout<<"3.1.2 if a: "<<a<<"\n";
					n = c;
                    t = b;
                    // cout<<"lc->bf: "<<-1*a<<endl;
                    L_Rotate(b);
                    b = t;
					b->bf = c->bf = 0;
				}
			}
			//single rotation
			else if(c->bf == 0){
                // cout<<"3.2 if: c->bf: "<<c->bf<<" a: "<<a<<"\n";
				if(a == -1){
                    // cout<<"3.2.1 if a: "<<a<<"\n";
					n = c;
                    t = b;
                    R_Rotate(b);
                    b = t;
                    // cout<<"0rc->bf: "<<0<<endl;
					c->bf = a; 
				}
				else if(a == 1){
                    // cout<<"3.2.2 if a: "<<a<<"\n";
					n = c;
                    t = b;
                    L_Rotate(b);
                    // cout<<"0lc->bf: "<<0<<endl;
                    b = t;
					c->bf = a;
				}
			}
			//double rotation
			else if(c->bf == a){
                // cout<<"3.3 if: c->bf: "<<c->bf<<" a: "<<a<<"\n";
                //LR rotation
				if(a == -1){
                    // cout<<"LR_Rotation\n";
                    // cout<<"3.3.1 if a: "<<a<<"\n";
					n = c->RChild;
					// c->RChild = n->LChild;
					// n->LChild = c;
					// b->LChild = n->RChild;
					// n->RChild = b;
                    LeftBalance(b);
                    // t = c;
                    // cout<<"LRotation done ck: "<<c->key<<"\n";
                    // L_Rotate(c);
                    // c = t;
                    // cout<<"LRotation done ck: "<<c->key<<"\n";
                    // t = b;
                    // cout<<"RRotation start bk: "<<b->key<<"\n";
                    // R_Rotate(b);
                    // b = t;
                    // if(!n) cout<<"pakda gaya\n";
                    // cout<<"RRotation done bk: "<<b->key<<"nk: "<<n->key <<"\n";
                    // switch(n->bf){
                    //     case 0:
                    //         b->bf = 0;
                    //         c->bf = 0;
                    //         break;
                    //     case 1:
                    //         b->bf = -1;
                    //         c->bf = 0;
                    //         break;
                    //     case -1:
                    //         b->bf = -1;
                    //         c->bf = 1;
                    //         break;
                    // }
					// n->bf = 0;
                    // cout<<"here\n";
				}
                //RL rotation
				else if(a == 1){
                    // cout<<"RL_Rotation\n";
                    // cout<<"3.3.2 if a: "<<a<<"\n";
					n = c->LChild;
                    t = b;
                    RightBalance(b);
                    b = t;
					// c->LChild = n->RChild;
					// n->RChild = c;
					// b->RChild = n->LChild;
					// n->LChild = b;
					// b->bf = n->bf == 0 ? 0 : n->bf == 1 ? 0 : 1;
					// c->bf = n->bf == 0 ? 0 : n->bf == 1 ? -1 : 0;
					// n->bf = 0;
				}
			}
		}
        
        if(b == p->RChild) p->RChild = n;
        else p->LChild = n;	

        if(p == h) root = n;
        // cout<<"1\n";
		// if(p!=h){
        //     cout<<"2\n";
        //     if(b == p->RChild) cout<<"3\n", p->RChild = n;
        //     else p->LChild = n;	
        // }
        
        // //incase root is part of rotation
        // else {
        //     cout<<"4\n";
        //     if(b == p->RChild) {
        //         cout<<"5\n";
        //         p->RChild = n;
        //     }else {
        //         cout<<"6\n";
        //         p->LChild = n;
        //     }
        //     root = n;
        // }	
	}
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

	#ifdef __unix__
		system("display graph.png");

	#elif _WIN32
		system(filename);

	#endif

	//removing the source (graph.gv) file
	remove("graph.gv");
	outFile.close();

	cout<<"PNG file is generated\n";
}