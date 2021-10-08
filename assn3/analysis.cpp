#include<bits/stdc++.h>
#include "Treap.h"
#include "AVL_Tree.h"
#include "BST.h"
using namespace std;

//set maintained to track which elements are inserted
unordered_set<int> s;

/*
 * tcsv - csv to maintain execution time of each tree
 * hcsv - csv to maintain height of tree
 * avgcsv - csv to maintain avg height of nodes 
 * ccsv - csv to maintain comparisons counts
 * rcsv - csv to maintain rotation counts
*/
ofstream tcsv, hcsv, avgcsv, ccsv, rcsv; 


//function to insert and delete into treap from testcase file
void makeTreap(string file_name){
    //treap pointer
    Treap *t = new Treap();
    //to track time
    time_t start, end;
    ifstream fin;
    //opening testcase file
    fin.open(file_name);
    //seeding
    srand(time(NULL));

    int T;
    //number of testcases
    fin>>T;
    
    string op, sval;

    //noting start time
    time(&start);

    //reading file
    while(fin >>op>>sval){
        if(op == "Insert"){
            //generating priority between 0-1000
            int p = rand()%1000;
            try{
                t->insertNode(stoi(sval), p);
            }catch(const char* e){
                cout<<e;
            }
        }else if(op == "Delete"){
            t->deleteNode(stoi(sval));
        }
    }
    //noting end time
    time(&end);

    //total time taken to insert and delete
    double time_taken = double(end - start);
    cout << "Time taken by Treap insertion and deletion for testcases "<<T<<" is: " << fixed
         << time_taken << setprecision(5)<<endl;

    // t->printTree("t.png");
    // system("pause");
    //writing all the csv
    tcsv<<T<<", "<<setprecision(5)<<time_taken;
    hcsv<<T<<", "<<t->heightOfTree();
    avgcsv<<T<<", "<<t->findAvgHeightofEachNode();
    ccsv<<T<<", "<<t->getComparisons();
    rcsv<<T<<", "<<t->getRotations();

    //destructor calling manually to destroy the tree
    t->~Treap(); 
    fin.close();   
    return;
}

//function to insert and delete into AVL from testcase files
void makeAVL(string file_name){
    //avl pointer
    AVL_Tree *t = new AVL_Tree();
    //to track time
    time_t start, end;
    ifstream fin;

    //opening testcase file
    fin.open(file_name);
    //number of testcases
    int T;
    fin>>T;

    string op, sval;
    
    //noting start time
    time(&start);
    
    //reading file
    while(fin >> op>>sval){
        //operation is insert
        if(op == "Insert"){
            try{
                t->AVL_Insert(stoi(sval));
            }catch(const char* e){
                cout<<e<<endl;
            }
        }
        //operation is deletion
        else if(op == "Delete"){
            try{
                t->AVL_Delete(stoi(sval));
            }catch(const char* e){
                cout<<e<<endl;
            }
        }
    }

    //noting end time
    time(&end);

    //total time taken to insert and delete
    double time_taken = double(end - start);
    cout << "Time taken by AVL insertion and deletion for testcases = "<<T<<" is: " << fixed
         << time_taken << setprecision(5)<<endl;
    
    // t->AVL_Print("t.png");
    // system("pause");
    //writing csv
    tcsv<<", "<<setprecision(5)<<time_taken;
    hcsv<<", "<<t->heightOfTree();
    avgcsv<<", "<<t->findAvgHeightofEachNode();
    ccsv<<", "<<t->getComparisons();
    rcsv<<", "<<t->getRotations()<<endl;

    //calling destructor manually to destroy tree
    t->~AVL_Tree();    
    fin.close();
    return;
}

//function to insert and delete into BST from testcase files
void makeBST(string file_name){
    //bst pointer
    BST *t = new BST();
    //to track time
    time_t start, end;
    ifstream fin;

    //opening testcase file
    fin.open(file_name);
    //number of testcase  
    int T;
    fin>>T;
    string op, sval;
    
    //noting start time
    time(&start);

    //reading testcase file
    while(fin >> op>>sval){
        // cout<<op<<" "<<sval<<" count: "<<cnt<<endl;
        if(op == "Insert"){
            try{
                t->addNode(stoi(sval));
            }catch(const char* e){
                cout<<e<<endl;
            }
        }else if(op == "Delete"){
            try{
                t->deleteNode(stoi(sval));
            }catch(const char* e){
                cout<<e<<endl;
            }
        }
    }

    //noting end time
    time(&end);

    //total time taken
    double time_taken = double(end - start);
    cout << "Time taken by BST insertion and deletion for testcases = "<<T<<" is: " << fixed
         << time_taken << setprecision(5)<<endl;
    
    // t->BST_Print("t.png");
    // system("pause");
    //writing details to csv files
    tcsv<<", "<<setprecision(5)<<time_taken<<endl;
    hcsv<<", "<<t->heightOfTree()<<endl;
    avgcsv<<", "<<t->findAvgHeightofEachNode()<<endl;
    ccsv<<", "<<t->getComparisons()<<endl;

    //calling destructor manually to destroy bst
    t->~BST();    
    fin.close();

    return;
}


//generating testcase file with given number of operations, threshold for deletion operations and name
void generateTestCase(int n, float thrshldForDeletion, string file_name, int &nInsert, int &nDelete){
    //testcase file
    ofstream fout;

    //seeding with current time
    srand((unsigned)time(NULL));

    // cout<<"threshold: "<<thrshldForDeletion<<" ins: "<<nInsert<<" ndele: "<<nDelete<<endl;
    
    //open file with given name
    fout.open(file_name);
    //writing number of operation first 
    fout<<n<<endl;
    //clearing set
    s.clear();

    //loop over all the operations
    for(int i=1; i<=n; i++){
        //deciding next operation should be insert or delete
        long double insertOrDelete = (long double) rand()/RAND_MAX;
        //deciding next element to be inserted - element range (0 - 2 * totalOperation)
        int element = rand()%(2*n);
        
        //finding unique element to insert
        while(s.find(element) != s.end())
            element = rand()%(2*n);

        //condition for insert
        //if set size is zero and current element to be inserted is nonzero then directly insert
        if((insertOrDelete > thrshldForDeletion || s.size() == 0) && element!=0) 
            nInsert++, fout<<"Insert "<<element<<endl, s.insert(element);

        //condition for deletion - it occurs only if element is inserted
        else if(s.size() > 0) {
            nDelete++;
            //generating random index for element to be deleted
            int ind = rand()%s.size();
            //pointer to that index
            auto it = s.begin();
            advance(it, ind);

            //deleting that element
            fout<<"Delete "<<*it<<endl;
            //remove that element from set
            s.erase(it);
        }

        //incase set size is zero and element to be inserted/deleted = 0
        else if(s.size() == 0){
            //decrease i to make equal to n operations
            i--;
        }
    }
    
    // cout<<"***********set size*******:::::"<<s.size()<<endl;
    //close testcase file
    fout.close();
    return;
}

//function to automatic generate testcase files ranging from 500 operations to 10000 operations by step of 500
void automatedTestCaseGenerations(int step, int start, int end){
    // T -  size of test file to be generated array
    // int T;
    
    // f - size of delete operations frequency array (threshold)
    int f;

    //object to write summary file
    ofstream fout;
    //saving the actual operations percentage in the summary file
    fout.open("Testcases/testcases_files_summary.txt");

    //threshold of delete operations
    float thrs[] = {20,30,40,50};

    //calculating size of testN array
    // T = sizeof(testN)/sizeof(testN[0]);
    //calculating size of thrs array
    f = sizeof(thrs)/sizeof(thrs[0]);

    //nInsert - number of insert generated
    //nDelete - number of delete generated
    int nInsert = 0, nDelete = 0;
    
    //loop over frequency
    for(int i = 0; i<f; i++){
        //loop over operations to be added in one testcase file
        for(int j= start; j<=end; j+=step){
            //name of file testcase{threshold}_{no. of ops}.txt
            string file_name = "Testcases/testcase"+to_string((int)thrs[i]) + "_" + to_string(j)+".txt";
            
            //resetting number of insertions and deletions for each test case files
            nInsert = 0, nDelete = 0;
            //generate test case file with given number of operations, threshold and given name
            generateTestCase(j, thrs[i]/100, file_name, nInsert, nDelete);
            
            //print summary on console as well save into summary file
            cout<<"File saved as "<<file_name<<", Contains total: "<<(nInsert*100)/(float)(nInsert+nDelete)<<" \% of insertions & "<<(nDelete*100)/(float)(nInsert + nDelete)<<"\% of deletions"<<endl;
            fout<<"File saved as "<<file_name<<", Contains total: "<<(nInsert*100)/(float)(nInsert+nDelete)<<" \% of insertions & "<<(nDelete*100)/(float)(nInsert + nDelete)<<"\% of deletions"<<endl;
            
            //make treap of that testcase file
            makeTreap(file_name);
            //make avl of that testcase file
            makeAVL(file_name);
            //make bst of that testcase file
            makeBST(file_name);
        }
    }
    
}

//function which takes number of test case files to be generated, number of operations and threshold for delete operations and manually generate testcase file 
void manualGeneration(){
    // T -  size of test file to be generated array
    int T, ops;
    //threshold for delete ops
    float threshold;

    //taking user input on how many files he/she wants to generate
    cout<<"How many test case files you want to generate? :"; cin>>T;
    int nInsert = 0, nDelete = 0;
    
    ofstream fout;
    //saving summary of testcase files
    fout.open("Testcases/testcases_files_summary.txt");
    
    //loop over total number of testcase files
    for(int i=0; i<T; i++){
        
        //taking input of operations and threshold for deletion operations 
        cout<<"How many total operation should be there? in file number "<<i+1<<": "; cin>>ops;
        cout<<"How much deletion should be there? (0-100): "; cin>>threshold;

        //name of testcase file
        string file_name = "Testcases/testcase"+to_string(threshold) + "_" + to_string(ops)+".txt";

        //resetting number of insertions and deletions occured for each new testcase file
        nInsert = nDelete = 0;
        
        //generate testcase
        generateTestCase(ops, threshold/100, file_name, nInsert, nDelete);
        
        //print summary on console as well save into summary file
        cout<<"File saved as "<<file_name<<", Contains total: "<<(nInsert*100)/(float)(nInsert+nDelete)<<" \% of insertions & "<<(nDelete*100)/(float)(nInsert + nDelete)<<"\% of deletions"<<endl;
        fout<<"File saved as "<<file_name<<", Contains total: "<<(nInsert*100)/(float)(nInsert+nDelete)<<" \% of insertions & "<<(nDelete*100)/(float)(nInsert + nDelete)<<"\% of deletions"<<endl;
        

        //make treap of that testcase file
        makeTreap(file_name);
        //make avl of that testcase file
        makeAVL(file_name);
        //make bst of that testcase file
        makeBST(file_name);
    }

    return;
}

int main(){
    
    //open the analysis files
    tcsv.open("Analysis/execution_time.csv");
    hcsv.open("Analysis/tree_height.csv");
    avgcsv.open("Analysis/avg_height_tree.csv");
    ccsv.open("Analysis/total_comparisons.csv");
    rcsv.open("Analysis/total_rotations.csv");

    //writing header in csv files
    tcsv<<"Iterations,Treaps,AVL,BST"<<endl;
    hcsv<<"Iterations,Treaps,AVL,BST"<<endl;
    avgcsv<<"Iterations,Treaps,AVL,BST"<<endl;
    ccsv<<"Iterations,Treaps,AVL,BST"<<endl;
    rcsv<<"Iterations,Treaps,AVL"<<endl;

    int choice;

    cout<<"Press 1. for automated testcase generation and analysis\nPress 2. for manual testcase generation and analysis\nEnter your choice: ";
    cin>>choice;

    if(choice == 1){
        int isDefault, start = 500, end = 10000, step = 500;
        cout<<"\n\n**Automated testcase generation and analysis**\n"<<endl;
        cout<<"\n-> If you want to generate testcase files from minimum 500 operations and maximum 10000 operations \n-> then enter start value to 500 and end value to 10000.\n-> specify steps like if you want after 500 operation we should generate 1000 testcases then you should enter 500"<<endl;
        cout<<"\nFor example - I want to generate testcases operations in 1000, 2000, 3000, 4000, 5000 then my start = 1000, end = 5000, step = 1000"<<endl;

        cout<<"\nDo you want to take start = 500, end = 10000, step = 500 ? \nPress 1 to proceed with default values\nPress any other key to take enter parameter values manually: "; cin>>isDefault;
        if(isDefault == 1){
            cout<<"\nYou can find testcases_files_summary.txt into Testcases/ folder which has all the summary of the files which are generated\n";
            cin.get();
            //calling automatic testcase generation function
            automatedTestCaseGenerations(step, start, end);
        }
        else{
            cout<<"Enter start: ";cin>>start;
            cout<<"\nEnter end: ";cin>>end;
            cout<<"\nEnter step: ";cin>>step; 
            cout<<endl;
            cout<<"\nYou can find testcases_files_summary.txt into Testcases/ folder which has all the summary of the files which are generated\n";
            cin.get();
            //calling automatic testcase generation function
            automatedTestCaseGenerations(step, start, end);
        }
        cout<<"\n\n\n**Don't forget to check these 2 folders\n1. Testcases/ which contains all the testcase files which are generated and summary of testcases\n2. Analysis/ folder which contains 5 csv for average height of tree, height of tree, number of rotations, number of comparisons, execution time\n";
    }else if(choice == 2){
        cout<<"\n**Manual testcase generation and analysis**\n"<<endl;
        cout<<"\nIn manual generation you'll be asked for - \n\t1. total number of testcase file you want to generate\n\t2. parameter values like - total number of operations and threshold for number of deletions\n\nthen it will generate the testcase file and does analysis on it :)\n\n";
        cout<<"\nYou can find testcases_files_summary.txt into Testcases/ folder which has all the summary of the files which are generated\n";
        cin.get();
        //calling manualGeneration function
        manualGeneration();


        cout<<"\n\n\n**Don't forget to check these 2 folders\n1. Testcases/ which contains all the testcase files which are generated and summary of testcases\n2. Analysis/ folder which contains 5 csv for average height of tree, height of tree, number of rotations, number of comparisons, execution time\n";
    }else{
        cout<<"Invalid choice"<<endl;
    }

    //close the analysis files
    tcsv.close();
    hcsv.close();
    avgcsv.close();
    ccsv.close();
    rcsv.close();

    return 0;
}