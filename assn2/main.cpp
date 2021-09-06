#include "AVL_Tree.h"
#include<iostream>
#include<fstream>

using namespace std;

int main(){

    AVL_Tree tree;
    int choice, k;
    string filename; 

    cout<<"Jay Khatri - 214101023"<<endl;

    do{
        cout<<"\nPress 1 for inserting the element into tree\nPress 2 for searching the node inside AVL tree\nPress 3 for deleting the node from tree\nPress 4 to print the tree\nPress 0 for exit\nEnter your choice: "; 
        cin>>choice;

        switch (choice){
            case 1:
                cout<<"Enter the element to be inserted: "; cin>>k;
                try{
                    tree.AVL_Insert(k);
                    cout<<"---> key : "<<k<<" is successfully inserted.\n";
                }catch(const char* e){
                    cout<<e<<endl;
                }
                break;

            case 2:
                cout<<"Enter the element to be searched: "; cin>>k;
                if(tree.AVL_Search(k)){
                    cout<<"Element found\n";
                }else {
                    cout<<"Element not found\n";
                }
                break;

            case 3:
                cout<<"Enter the element to be deleted: "; cin>>k;
                try{
                    tree.AVL_Delete(k);
                    cout<<"---> key : "<<k<<" is successfully deleted.\n";
                }catch(const char* e){
                    cout<<e<<endl;
                }
                break;

            case 4:
                cout<<"Enter filename: "; cin>>filename;
                filename += ".png";
                tree.AVL_Print(filename.c_str());
                break;

            case 0:
                tree.~AVL_Tree();
                cout<<"exiting...\n";
                exit(0);

            default:
                cout<<"Please select valid option i.e. from 0-4.\n";
                break;
        }
    }while(choice!=0);

    return 0;
}
/*
    Code to check copy constructor and = operator overloading
    AVL_Tree tree;
    tree.AVL_Insert(25);
    tree.AVL_Insert(15);
    tree.AVL_Insert(10);
    tree.AVL_Insert(20);
    tree.AVL_Insert(17);
    tree.AVL_Insert(22);
    tree.AVL_Insert(30);
    tree.AVL_Insert(28);
    tree.AVL_Insert(35);
    tree.AVL_Insert(40);

    AVL_Tree tree2(tree);
    tree.AVL_Delete(15);    
    AVL_Tree tree3 = tree;
    tree3.AVL_Insert(16);
    tree.AVL_Print("photo.png");
    tree2.AVL_Print("photo2.png");
    tree3.AVL_Print("photo3.png");

    cout<<"addr1: "<<tree.getRoot()<<" addr2: "<<tree2.getRoot()<<" addr3: "<<tree3.getRoot()<<endl;

*/