//Including required header files
#include <bits/stdc++.h>
#include<fstream>
#include "AVL_Tree.h"
using  namespace std;

//default constructor
AVL_Tree::AVL_Tree(){
    root = new AVL_Node(-1);
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
    //create new node with same value
    AVL_Node *new_node = new AVL_Node(root->key);
    //clone left subtree, recursively
    new_node->LChild = clone(root->LChild);
    //clone right subtree, recursively
    new_node->RChild = clone(root->RChild);
    //copy balance factor
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
    
//link function gives the child node which side balancing is required 
AVL_Node*  AVL_Tree:: link(AVL_Node *P, int dir){
     return dir==1 ? P->LChild : P->RChild;
}

//insert function
void AVL_Tree::AVL_Insert(int key){
    
    AVL_Node *parent = root;
    bool flag=1;
    AVL_Node *balance;
    AVL_Node *n;
    balance=n=root->RChild;
    AVL_Node  *temp_n,*child;
    
    temp_n=child=NULL;
    
    //base case
    if(!n){
        root->RChild = new AVL_Node(key);
        totalNodes++;
        return;
    }
    
    //Creating new node with key
    AVL_Node *new_node = new AVL_Node(key);
    while(flag == 1){ 
        totalComparisons++;
        //duplicate key
        if(key == n->key){
            // cout<<"Element "<<key<<" is already present in AVL\n";
            return;
        }  
        //If key is greater than current node's key, go to right subtree
        else if(key > n->key){
            temp_n=n->RChild;
            
            //temp_n is null, means we have reached end of tree
            if(!temp_n){
                n->RChild=new_node;
                temp_n=n->RChild;
                flag=0;
            }

            else{
                //if temp_n bf is -1 or +1, means if we insert our new node here, it will cause inbalance
                if(temp_n->bf!=0){
                parent = n;
                balance = temp_n;
                }
                n=temp_n;
            }
        }
        // if no above conditions satisfied
        else if(key < n->key) {
            temp_n = n->LChild;
            //reached end, insert here
            if(!temp_n){
                n->LChild=new_node;
                temp_n=n->LChild;
                flag=0;
            }
            else{
            //update balance and parent pointers
            if(temp_n->bf){
                parent=n;
                balance=temp_n;
            }
            n=temp_n;
        }
        }
    }
    cout<<"AVL::Insertion of "<<key<<" is successful\n";
    //element inserted
    totalNodes++;

    int dir = key >= balance->key ? -1 : 1;
    //there was already imbalance and node is being added
    child=link(balance, dir);
    
    n=child;
    while(n!=temp_n){  
        totalComparisons++;  
        //We are inserting on rigth side so bf=-1, update balance factor
        if(key>n->key)
            n->bf=-1;

        //We are inserting on left side so bf=-1, update
        else
            n->bf=1;
        
        //go to right subtree
        if(key > n->key){
            n=n->RChild;
        }

        //go to left subtree
        else{
            n=n->LChild;
        }
    }

    //if node is being added in opposite side, so we are making tree more stable, update to bf = 0
    if(balance->bf == -1*dir){
        balance->bf = 0;
        return;
    }
    
    //if node was already balanced then after inserting we are making it imbalanced, so update bf = dir.
    else if(balance->bf==0){
        balance->bf=dir;
        return;
    }
    
    // when all the above cases are not happened means we need rotations
    else{   
        //Single rotation
        if(dir==child->bf){
            //LL rotation
            totalRotations++;
            if(dir == -1){
                balance->bf=child->bf=0;
                n=child;
                balance->RChild=child->LChild;
                child->LChild=balance;
            }
            //RR rotation
            else{
                balance->bf=child->bf=0;
                n=child;
                balance->LChild=child->RChild;
                child->RChild=balance;
            }
        }
        //Double rotation is required.
        else if(child->bf == dir*-1){
                totalRotations+=2;
                //RL rotation
                if(dir==-1){
                    n=child->LChild;
                    child->LChild=n->RChild;
                    n->RChild=child;
                    balance->RChild=n->LChild;
                    n->LChild=balance;
                    
                    //updating bf balance node
                    if(n->bf==0) 
                        balance->bf=0;
                    else{
                       if(n->bf==1)
                         balance->bf=0;
                       else
                          balance->bf=1;
                    }
                    //updating bf of child node
                    if(n->bf==0)
                        child->bf=0;
                    else {
                        if(n->bf==1)
                            child->bf=-1;
                        
                        else
                            child->bf=0;
                    }
                    n->bf=0;
                }
                //LR rotation
                else{
                    n=child->RChild;
                    child->RChild=n->LChild;
                    n->LChild=child;
                    balance->LChild=n->RChild;
                    n->RChild=balance;
                    
                    //updating bf balance node
                    if(n->bf==0)
                        balance->bf=0;
                    
                    else {
                        if(n->bf==1)
                            balance->bf=-1;
                        
                        else
                            balance->bf=0;
                    }
                    //updating bf of child node
                    if(n->bf==0)
                        child->bf=0;
                    
                    else {
                        if(n->bf==1)
                            child->bf=0;
                        
                        else
                            child->bf=1;
                    }
                    n->bf=0;
                }
            }
       }
    //n should be left child of parent node or right
    if(balance == parent->RChild)  parent->RChild = n;
    else parent->LChild = n;
}

void  AVL_Tree:: AVL_Delete(int k){ 
    //variable to find node to be deleted
    AVL_Node *n = root->RChild; 
	
    // base case
    if(!n) cout<<"No element inside tree, Please insert some elements into AVL first!!\n";
    
    // balance - AVL_Node to be balanced
	// parent - parent of the AVL_Node to be balanced
	// child - left/right child of the AVL_Node to be balanced
    
    // rootToNode - stack which will help us to store all nodes on the path from root to deleted element/successor element in LIFO order.
    stack<AVL_Node*> rootToNode;
    AVL_Node *parent, *balance, *child;
    
    rootToNode.push(root);

    //finding node to be deleted and tracking path from root to node in rootToNode
    while(n){
        totalComparisons++;
        //if node is found.
        if(k == n->key){
            break;
        }
        
        else if(k > n->key){
            rootToNode.push(n);
            n=n->RChild;
        }

        else if (k < n->key){
            rootToNode.push(n);
            n=n->LChild;
        }
    }
    
    // AVL_Node *temp=NULL;
    AVL_Node *stack_top=NULL;
    //if n is null means we couldn't find target node
    if(!n){
        cout<<"given element "<<k<<" does not exist in a tree\n";
        return;
    }
    //n points to node to be deleted
    //if n has single child
    if(!n->LChild || !n->RChild){
            
            AVL_Node *temp = n->LChild ? n->LChild : n->RChild;
            stack_top=rootToNode.top();
            
            //if n has single child
             if(n->LChild || n->RChild){
                if(n->LChild){
                  n->LChild=temp->LChild;
                  n->RChild=temp->RChild;
                }
                if(n->RChild){
                  n->RChild=temp->RChild;
                  n->LChild=temp->LChild;
                }
                n->bf=temp->bf;
                n->key=temp->key;
                delete temp;
            }
            
            //if n is a leaf
            else{
                temp=n;
                //if n is the left child of parent
                if(n->key < stack_top->key){
                    stack_top->LChild = NULL;
                    n = NULL;
                    delete temp;
                }
                // if n is right child of parent
                else {
                    stack_top->RChild = NULL;
                    n = NULL;
                    delete temp;
                }
            }
        }
    
    //if n has both child
    else if(n->RChild && n->LChild){    
         AVL_Node *t = NULL;
		 rootToNode.push(n);
		 
         //finding successor
         AVL_Node *succ=n->RChild;
         
         while(succ->LChild!=NULL){
			 rootToNode.push(succ);
			 succ=succ->LChild;
		 }
         
         k=succ->key;
		 n->key=k;
		 
         t = succ->RChild ? succ->RChild : succ->LChild;
         
		 stack_top=rootToNode.top();
        
        // if successor has no child
		if(!t){
             t = succ;
             if(succ == stack_top->LChild)
                stack_top->LChild = NULL;
             else  
                 stack_top->RChild = NULL;
            succ = NULL;
			delete t;
        }
        
        //successor has single child
		else if(succ->LChild || succ->RChild){ 
             succ->bf=t->bf;
             succ->key=t->key;
             succ->LChild=t->LChild;
             succ->RChild=t->RChild;
             delete t;
        }
    }
    
    cout<<"AVL::Deletion of "<<k<<" is successful\n";
    totalNodes--;
    
    //processing the path from root to node and balancing all nodes which came into path of node
    while(root!=rootToNode.top()){
        
        balance = rootToNode.top();
        rootToNode.pop();
        parent = rootToNode.top();
        
        //to keep track of side from which node is deleted 
        int dir = k < balance->key ? 1 : -1;
        
        //if node to be balanced was already balanced and deleting of the node has made imbalance here so we update the bf accordingly
        if(balance->bf == 0){
            //node is added and imbalance will be opposite
            balance->bf=dir*-1;
            return;
        }
        
        //there was already imbalance and node is being deleted from that side
        else if(balance->bf == dir){
            balance->bf=0;
            continue;
        }
        //If above 2 cases are not satisfied balencing is required
        else{
            child= link(balance, balance->bf);
            
            //single rotation
            if(child->bf == -1 * dir){  
                totalRotations++;
                //LL rotation
                if(dir == 1){  
                    balance->bf=child->bf=0;
                    n=child;
                    balance->RChild=child->LChild;
                    child->LChild=balance;
                }
                //RR rotation
                else{
                    balance->bf=child->bf=0;
                    n=child;
                    balance->LChild=child->RChild;
                    child->RChild=balance;
                }
            }
            
            //single rotation
            else if(child->bf == 0){
                totalRotations++;
                n=child;
                //LL rotation
                if(dir == 1){
                    balance->RChild=child->LChild;
                    child->LChild=balance;
                }
                //RR rotation
                else if(dir == -1){
                    balance->LChild=child->RChild;
                    child->RChild=balance;
                }
                child->bf=dir;
            }
            
            //double rotation
            else if(child->bf == dir){    
                totalRotations+=2;
                 //RL rotation
                  if(dir == 1){
                        n=child->LChild;
                        child->LChild=n->RChild;
                        n->RChild=child;
                        balance->RChild=n->LChild;
                        n->LChild=balance;
                       
                        //deciding bf of balance node
                        if(n->bf == 0)
                            balance->bf=0;
                        else {
                            if(n->bf == 1)
                                balance->bf=0;
                            else
                                balance->bf=1;
                        }
                        //deciding bf of child node
                        if(n->bf == 0)
                            child->bf=0;
                        else {
                            if(n->bf == 1)
                                child->bf=-1;
                            else
                                child->bf=0;
                        }
                       
                   }
                  //LR rotation
                  else{
                        n=child->RChild;
                        child->RChild=n->LChild;
                        n->LChild=child;
                        balance->LChild=n->RChild;
                        n->RChild=balance;
                        
                        //deciding bf of balance node  
                        if(n->bf == 0){
                            balance->bf=0;
                        }
                        else {
                            if(n->bf == 1)
                                balance->bf=-1;
                            
                            else
                                balance->bf=0;
                        }
                        //deciding bf of child node
                        if(n->bf == 0){
                            child->bf=0;
                        }
                        else {
                            if(n->bf == 1)
                                child->bf=0;
                            
                            else
                                child->bf=1;
                        }
                      
                  }
                  n->bf=0;
            }
                  
            if(n->bf == -1 || n->bf == 1){
                if(balance == parent->RChild) parent->RChild = n;
                else parent->LChild = n;
                return;
            }
       }
    
      if(balance == parent->RChild) parent->RChild = n;
      else parent->LChild = n;
   }
}

// writing the node to the file
void AVL_Tree::printNode(AVL_Node*& node, ofstream& outFile) {
	//if it's leaf return from there
	if(node->LChild == NULL && node->RChild == NULL) return;
	//if it's not leaf and it has left child
	if(node->LChild != NULL) {
        // cout<<"left: "<<node->LChild->key<<"\n";
		outFile << "\t"<<node->LChild->key<<"[label=\""<<node->LChild->key<<" {"<<node->LChild->bf<<"}\"]" << endl;
		outFile << "\t\"" << node->key << "\" -> \"" << node->LChild->key <<"\"" << endl;

		//recursively call the function for left child
		this->printNode(node->LChild, outFile);
	}
	//if it's not leaf and it has right child
	if(node->RChild != NULL) {
        // cout<<"right: "<<node->RChild->key<<"\n";
		outFile << "\t"<<node->RChild->key<<"[label=\""<<node->RChild->key<<" {"<<node->RChild->bf<<"}\"]" << endl;
		outFile << "\t\"" << node->key << "\" -> \"" << node->RChild->key <<"\"" << endl;
		//recursively call the function for right child
		this->printNode(node->RChild, outFile);
	}
}

// printing the tree using graphwiz
void AVL_Tree::AVL_Print(const char* filename) {
	AVL_Node* temp = root->RChild;
	ofstream outFile;
    if(temp == NULL) cout<<"Tree is empty\n";
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

//search function
bool  AVL_Tree:: AVL_Search(int k){
    //Initialising temp pointer with rigth child of dummy root or original root.
    AVL_Node *temp = root->RChild;
    while(temp!=NULL){
        //if key is found
        if(temp->key==k){
            cout<<k<<" is  found in the tree"<<endl;
            return true;
        }
        //if key is greater than the current node than discarding the right subtree
        else if(temp->key>k) {
            temp=temp->LChild;
        }
        //if key is less than the current node than discarding the left subtree
        else{
            temp=temp->RChild;
        }
    }
    
    cout<<k<<" is not found in the tree"<<endl;
    return false;
}

//recursive function to get height of the node
int AVL_Tree::getHeight(AVL_Node *&node){
    if(!node) return -1;

    return max(getHeight(node->LChild), getHeight(node->RChild)) + 1;
}

//total height helper
int AVL_Tree::totalHeightHelper(AVL_Node *&node){
    if(!node) return 0;

    return totalHeightHelper(node->LChild) + getHeight(node) + totalHeightHelper(node->RChild);
}

int AVL_Tree::size(){
    return totalNodes;
}

//driver fucntion to call calculate and return total height
double AVL_Tree::findAvgHeightofEachNode(){
    int tH = totalHeightHelper(root->RChild);
    // cout<<"totalheight: "<<tH<<" size of avl: "<<size()<<endl;
    if(size() != 0)
        return tH/(double) size();
    return 0;
}

int AVL_Tree::heightOfTree(){
    return getHeight(root->RChild);
}

long int AVL_Tree::getComparisons(){
    return totalComparisons;
}

long int AVL_Tree::getRotations(){
    return totalRotations;
}