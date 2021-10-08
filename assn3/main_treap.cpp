#include<iostream>
#include "Treap.h"

using namespace std;

int main(){

    int choice;
    Treap treap;
    srand(time(NULL));

    cout<<"Code is authored by- Jay Khatri(214101023)\n";

    do{
        cout<<"\nPress 1. for Insert in Treap\nPress 2. to search element in Treap\nPress 3. to delete element in Treap\nPress 4. for printing inorder of treap\nPress 5. for printing Treap\nPress 0. to exit\nEnter your choice: ";

        cin>>choice;

        switch(choice){
            case 1:
                //insert node
                {
                    int x, n;
                    cout<<"\nEnter number of element to be inserted in Treap: ";
                    cin>>n;
                    try{
                        for(int i=0; i<n; i++){
                            cout<<"Enter element to be inserted: ";cin>>x;
                            cout<<endl;
                            //generating priority between 0 - 1000
                            int p = rand()%1000;
                            treap.insertNode(x, p);
                        }
                    }catch(const char* e){
                        cout<<e<<endl;
                    }
                    break;
                }
            case 2:
                //search node
                {
                    int x;
                    cout<<"Enter element to be searched in Treap: ";
                    cin>>x;   
                    if(treap.searchNode(x)){
                        cout<<"Element found\n";
                    }else{
                        cout<<"Element not found\n";
                    }
                    break;
                }
            case 3:
                //delete node
                {
                    int x;
                    cout<<"Enter element to be deleted in Treap: ";
                    cin>>x;
                    treap.deleteNode(x);
                    // cout<<"deletion is successful, try choice number 5 to print and see it\n";
                    break;
                }

            case 4:
                {
                    cout<<"Inorder - ";
                    treap.inorderTraversal();
                    cout<<endl;
                    break;
                }

            case 5:
                {
                    string s;
                    cout<<"Enter filename: "; cin>>s;
                    s += ".png";
                    treap.printTree(s.c_str());
                    cout<<endl;
                    break;
                }

            case 0:
                //exit from code
                {
                    cout<<"Exiting\n";
                    treap.~Treap();
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
}