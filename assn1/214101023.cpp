#include<iostream>
#include<limits>
#include <fstream>
#include "utils.h"

using namespace std;

int main() {
    int choice = -1, x, y;
    ThreadedBST *tbst = NULL;
    BSTNode *found;
    LLNode *head;
    cout<<"Program to perform different operations on Binary Search Tree\n";
    

    do{
        cout<<"\nPress 1. for Insert in BST\nPress 2. to search element in BST\nPress 3. to delete element in BST\nPress 4. to print reverse inorder of BST\nPress 5. to find successor of an element in BST\nPress 6. to split BST from one key value\nPress 7. to find nodes between k1 and k2\nPress 8. to find kth largest element\nPress 9. for printing BST\nPress 0. to exit\nEnter your choice: ";

        cin>>choice;

        switch(choice){
            case -1:
                {
                    ThreadedBST *tbst = new ThreadedBST();
                    tbst->insert(10);
                    tbst->insert(20);
                    tbst->insert(5);

                    ThreadedBST *tbst2(tbst);
                    cout<<tbst2->getRoot();
                    cout<<tbst2->getRoot()->left<<"\n";
                    // cout<<tbst2->getRoot()->right->key;
                    // tbst2->deleteNode(5);
                    // if(tbst->getRoot()->left == NULL)cout<<"hi";
                    cout<<tbst->getRoot()->left;
                    // cout<<"inorder 1 - ";
                    // head = tbst->inorder();
                    // while(head){
                    //     cout<<head->data<<" ";
                    //     head = head->next;
                    // }

                    // cout<<"\ninorder 2 - ";
                    // head = tbst2->inorder();
                    // while(head){
                    //     cout<<head->data<<" ";
                    //     head = head->next;
                    // }
                    break;
                }

            case 1:
                {
                    int x, n;
                    cout<<"Enter number of element to be inserted in BST: ";
                    cin>>n;
                    try{
                        for(int i=0; i<n; i++){
                            cout<<"Enter element to be inserted: ";cin>>x;
                            cout<<endl;
                            if(tbst == NULL){
                                tbst = new ThreadedBST();
                                tbst->insert(x);
                                // tbst->insert(25);
                                // tbst->insert(10);
                                // tbst->insert(30);
                                // tbst->insert(3);
                                // tbst->insert(12);
                                // tbst->insert(27);
                                // tbst->insert(35);
                                // tbst->insert(11);
                                // tbst->insert(15);
                                // tbst->insert(29);
                            }else{
                                tbst->insert(x);
                            }
                        }
                    }catch(const char* e){
                        cout<<e<<endl;
                    }
                    break;
                }
            case 2:
                {
                    int x;
                    cout<<"Enter element to be searched in BST: ";
                    cin>>x;
                    if(tbst == NULL){
                        cout<<"BST is empty\n";
                    }else{
                        found = tbst->search(x);
                        if(found){
                            cout<<"Element found\n";
                        }else{
                            cout<<"Element not found\n";
                        }
                    }
                    break;
                }
            case 3:
                {
                    int x;
                    cout<<"Enter element to be deleted in BST: ";
                    cin>>x;
                    if(tbst == NULL){
                        cout<<"BST is empty\n";
                    }else{
                        try{
                            tbst->deleteNode(x);
                        }catch(const char* c){
                            cout<<c<<endl;
                        }
                    }
                    break;
                }
            case 4:
                {
                    if(tbst == NULL){
                        cout<<"BST is empty\n";
                    }else{
                        head = tbst->reverseInorder();
                        if(head!=NULL){
                            cout<<"Reverse Inorder of the given tree - ";
                            while(head){
                                cout<<head->data<<" ";
                                head = head->next;
                            }
                            cout<<endl;
                        }else{
                            cout<<"BST is empty\n";
                        }
                    }
                    break;
                }
            case 5:
                {
                    int x;
                    cout<<"Enter element to find successor: ";
                    cin>>x;
                    found = tbst->search(x);
                    if(found){
                        if(tbst == NULL){
                            cout<<"BST is empty\n";
                        }else{
                            y = tbst->successor(found);
                            if(y!=INT_MIN){
                                cout<<"Successor of "<<x<<" is "<<y<<endl;
                            }else{
                                cout<<"No successor found\n";
                            }
                        }
                    }else{
                        cout<<"Element not found in BST\n";
                    }
                    break;
                }
            case 6:
                {
                    int x;
                    cout<<"Enter element to split BST: ";
                    cin>>x;
                    if(tbst == NULL){
                        cout<<"BST is empty, please insert some keys!\n";
                    }else{
                        ThreadedBST *lTbst, *rTbst;
                        tbst->split(x, lTbst, rTbst);

                        if(lTbst != NULL){
                            cout<<"left part - ";
                            head = lTbst->inorder();
                            if(head!=NULL)
                                while(head){
                                    cout<<head->data<<" ";
                                    head = head->next;
                                }
                            cout<<endl;
                        } 
                        if(rTbst != NULL){
                            cout<<"right part - ";
                            head = rTbst->inorder();
                            if(head)
                                while(head){
                                    cout<<head->data<<" ";
                                    head = head->next;
                                }
                            cout<<endl;
                        }
                    }
                    break;
                }
            case 7:
                {
                    int x,y;
                    cout<<"Enter two elements to find nodes between them: ";
                    cin>>x>>y;
                    if(tbst == NULL){
                        cout<<"BST is empty\n";
                    }else{
                        head = tbst->allElementsBetween(x,y);
                        if(head!=NULL){
                            cout<<"Nodes between "<<x<<" and "<<y<<" are - ";
                            while(head){
                                cout<<head->data<<" ";
                                head = head->next;
                            }
                            cout<<endl;
                        }else{
                            cout<<"No nodes found between "<<x<<" and "<<y<<endl;
                        }
                    }
                    break;
                }
            case 8:
                {
                    int k;
                    cout<<"Enter element to find kth largest element: ";
                    cin>>k;
                    if(tbst == NULL){
                        cout<<"BST is empty\n";
                    }else{
                        int x = tbst->kthElement(k);
                        if(x!=INT_MIN){
                            cout<<k<<"th largest element is "<<x<<endl;
                        }else{
                            cout<<"No "<<k<<"th largest element found\n";
                        }
                    }
                    break;
                }
            case 9:
                {
                    if(tbst == NULL){
                        cout<<"BST is empty\n";
                    }else{
                        tbst->printTree();
                        cout<<"Printing is successfull, file is saved as graph.png";
                    }
                    break;
                }
            case 0:
                {
                    cout<<"Exiting\n";
                    exit(0);
                    break;
                }
            default:
                {
                    cout<<"Invalid choice\n";
                    break;
                }
        }
                        
    }while(choice != 0);

	return 0;
} //end-main



/*
ThreadedBST bst, bst1;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(2);
    bst.insert(7);
    bst.insert(12);
    // try{
    //     bst.insert(15);
    // }catch(const char* e){
    //     cout << e << endl;
    // }

    bst1.insert(25);
    bst1.insert(10);
    bst1.insert(30);
    bst1.insert(3);
    bst1.insert(12);
    bst1.insert(27);
    bst1.insert(35);
    bst1.insert(11);
    bst1.insert(15);
    bst1.insert(29);

    // cout<<bst.getRoot()->key<<endl;
    // Test for split
    // cout<<"Testing split: \n";
    // ThreadedBST *left, *right;
    // bst1.split(30, left, right);
    // LLNode *h = left->inorder();
    // cout<<"left tree inorder - ";
    // while(h) {
    //     cout<<h->data<<" ";
    //     h = h->next;
    // }
    // cout<<"\nright tree inorder - ";
    // h = right->inorder();
    // while(h) {
    //     cout<<h->data<<" ";
    //     h = h->next;
    // }

    //reverse inorder
    LLNode* head = bst.reverseInorder();
    cout<<"reverse inorder - ";
    while(head != NULL) {
        cout << head->data << ", ";
        head = head->next;
    }
    cout<<endl;
    // bst.deleteNode(-1);
    // bst.deleteNode(15);
    // head = bst.reverseInorder();
    // cout<<"reverse inorder - ";
    // while(head != NULL) {
    //     cout << head->data << ", ";
    //     head = head->next;
    // }
    // cout<<endl;
    cout<<"root: "<<bst.getRoot()->key<<endl;
    //kth largest
    try{
        cout << "kth largest: " << bst.kthLargestElement(5) << endl;
    }catch(const char* e){
        cout << e << endl;
    }

    cout<<"checking k1 and k2\n";
    head = bst.allElementsBetween(5, 12);
    while(head != NULL) {
        cout << head->data << ", ";
        head = head->next;
    }
    cout<<endl;

/*








// class TreeNode {
//     public:
//         int data;
//         TreeNode *left, *right;
//         bool lthread, rthread;
//         TreeNode (){
//             data = -1;
//             left = right = NULL;
//             lthread = rthread = false;
//         }
//         TreeNode(int x) {
//             data = x;
//             left = right = NULL;
//             lthread = rthread = false;
//         }
// };

// class ThreadedBST {
//     private:
//         TreeNode *root;
//     public:
//         ThreadedBST();
//         void insert(int val);
//         void printTree();

// };

// ThreadedBST::ThreadedBST() {
//     root = new TreeNode();
//     root->left = root->right = root;
//     root->lthread = root->rthread = true;
//     root->data = 0;    
// }

// void ThreadedBST::insert(int x) {
//     TreeNode *p = root;
//     for (;;) {
//         if (p->data < x) {
//             if (p->rthread) 
//                 break;
//                 p = p->right;
//         } else if (p->data > x) {
//             if (p->lthread) 
//                 break;
//                 p = p->left;
//         }else {
//             /* redundant key */
//             return; 
//         }
//     }
    
//     TreeNode *tmp = new TreeNode();
//     tmp->data = x;
//     tmp->rthread = tmp->lthread = true;
//     if (p->data < x) { 
//         /* insert to right side */
//         tmp->right = p->right;
//         tmp->left = p;
//         p->right = tmp;
//         p->rthread = false;
//     } else {
//         tmp->right = p;
//         tmp->left = p->left;
//         p->left = tmp;
//         p->lthread = false;
//     }
// }

// void printTree() {
//     TreeNode *tmp = this->root;
//     TreeNode *p;
//     for (;;) {
//         p = tmp;
//         tmp = tmp->right;
//         if (!p->rthread) {
//             while (!tmp->lthread) {
//                 tmp = tmp->left;
//             }
//         }
//         if (tmp == this->root) 
//             break;
//         cout<<tmp->data<<"   ";
//     }
//     cout<<endl;
// }    

// int main(){
//     ThreadedBST *tbst = new ThreadedBST();
//     tbst->insert(10);
//     tbst->insert(5);
//     tbst->insert(15);
//     tbst->insert(1);
//     tbst->insert(20);
//     tbst->insert(2);
//     tbst->insert(3);
//     tbst->insert(40);
//     tbst->insert(30);
//     tbst->insert(25);

//     tbst->printTree();

// }