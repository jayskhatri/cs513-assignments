//implementing treap
#include<iostream>
#include<fstream>
#include<bits/stdc++.h>

using namespace std;

class TreapNode{
    private:
        int key;
        int priority;
        TreapNode *left, *right;
        friend class Treap;
    public:
        TreapNode(int k){
            key = k;
            priority = ((rand() << 4) + rand()) % INT_MAX;
            left = right = NULL;
        }
};

class Treap{
    private:
        TreapNode *root, *dummy;
    public:
        Treap(){
            dummy = new TreapNode(INT_MIN);
            dummy->left = dummy->right = dummy;
            dummy->priority = INT_MAX;
            root = dummy;
        }

        // right rotation
        void R_Rotate (TreapNode *&node) {
            
            TreapNode *lc = node->left; // LC pointing left child node of passed node
            node->left = lc->right; // right subtree node set lc p junction left subtree
            lc->right = node; // set the node as the right child node of lc
            node = lc; // node points to the new root node i.e. lc
        }

        // left rotation
        void L_Rotate(TreapNode *&node) {
            TreapNode *rc = node->right;
            node->right = rc->left;
            rc->left = node;
            node = rc;
        }
        
        // TreapNode* insertHelper(TreapNode* root, int k, int p){
        //     if(!root) return new TreapNode(k, p);

        //     if(root->key < k){
        //         root->left = insertHelper(root->left, k, p);

        //         if(root->left->priority > root->priority)
        //             root = R_Rotate(root);

        //     }
        //     else {
        //         root->right = insertHelper(root->right, k, p);

        //         if(root->right->priority > root->priority)
        //             root = L_Rotate(root);
        //     }
        // }

        // void update(Node *&p) {
        //     if (p != dummy) {
        //         p->c = p->l->c + p->r->c + 1;
        //     }
        // }

        // left rotate
        void lr(TreapNode *&p) {
            TreapNode *q = p->left;
            p->left = q->right;
            q->right = p;
            // update(p);
            // update(q);
            p = q;
        }

        // right rotate
        void rr(TreapNode *&p) {
            TreapNode *q = p->right;
            p->right = q->left;
            q->left = p;
            // update(p);
            // update(q);
            p = q;
        }

        void ins(TreapNode *&p, int x) {
            // cout<<"hi ins\n";
            if (p == dummy) {
                // cout<<"p == dummy\n";
                p = new TreapNode(x);
                p->left = p->right = dummy;
            // p->c = 1;
            } else if (x < p->key) {
                // cout<<"given key is < "<<p->key<<"\n";
                ins(p->left, x);
                
                if (p->left->priority < p->priority) lr(p);
            } else if(x > p->key){
                // cout<<"given key is > "<<p->key<<"\n";
                ins(p->right, x);
                if (p->right->priority < p->priority) rr(p);
            }else{
                throw "Element already exist\n";
            }
            // update(p);
        }
        void insert(int k){
            try{
                ins(root, k);
                cout<<"Successfully inserted: "<<k<<endl;
            }catch(const char* e){
                throw e;
            }
        }// insert ends

        void del(TreapNode *&p) {
            if (p->left == dummy && p->right == dummy) {
                delete p;
                p = dummy;
                return;
            }
            if (p->left->priority < p->right->priority) {
                lr(p);
                del(p->right);
            } else {
                rr(p);
                del(p->left);
            }
            // update(p);
        }
        void del(TreapNode *&p, int x) {
            if (p == dummy) return;
            
            if (p->key == x)
                del(p);
            else if (x < p->key)
                del(p->left, x);
            else
                del(p->right, x);
            
            // if (p != dummy) update(p);
        }

        bool find(TreapNode *&p, int x) {
            if (p == dummy) return false;
            if (x == p->key) return true;
            return (x < p->key) ? find(p->left, x) : find(p->right, x);
        }

        bool findNode(int k){
            return find(root, k);
        }
        void deleteNode(int k){
            del(root, k);
        }

        void inorder(TreapNode *node){
            // cout<<"inorder called:"<<node->key<<"\n";
            if(node == dummy || node == NULL){
                // cout<<"inorder:: Null aaya\n";
                return;
            }
            inorder(node->left);
            cout<<node->key<<"{"<<node->priority<<"}, ";
            inorder(node->right);
        }
        void print(){
            if(!root) cout<<"print, null aaya root\n";
           cout<<"inorder - ";
           inorder(root);
           cout<<endl;
        }
};

int main(){
    ofstream fout;
    //test case 1 generation
    fout.open("testcase1.txt");
    fout<<10000<<endl;
    fout<<"Insert 1"<<endl;
    fout<<"Insert 2"<<endl;
    fout<<"Insert 3"<<endl;
    for(int i=4; i<=10000; i++){
        float zeroOne = (float) rand()/RAND_MAX;

        if(zeroOne > 0.5) fout<<"Insert "<<i<<endl;

        else fout<<"Delete "<<i-2<<endl;
    }

    fout.close();
    fout.open("testcase2.txt");
    fout<<5000<<endl;
    fout<<"Insert 100"<<endl;
    fout<<"Insert 110"<<endl;
    fout<<"Insert 101"<<endl;
    fout<<"Insert 230"<<endl;

    for(int i=5; i<=5000; i++){
        float zeroOne = (float) rand()/RAND_MAX;

        if(zeroOne > 0.5) fout<<"Insert "<<i*12+i<<endl;

        else fout<<"Delete "<<(i-2)*i+1<<endl;
    }

    fout.close();

    Treap t;
    time_t start, end;

    ifstream fin;
    fin.open("testcase1.txt");
    int T;
    fin>>T;
    string op, sval;
    char delim;
    time(&start);
    while(fin >> op>>sval){
        cout<<op<<" "<<sval<<endl;
        if(op == "Insert"){
            try{
                t.insert(stoi(sval));
            }catch(const char* e){
                cout<<e;
            }
        }else if(op == "Delete"){
            t.deleteNode(stoi(sval));
        }
    }
    time(&end);
    double time_taken = double(end - start);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    fin.close();

    // Treap t;
    // t.insert(5, 4);
    // t.print();
    // t.insert(3, 2);
    // t.print();
    // t.insert(4, 3);
    // t.print();
    // t.insert(1, 1);
    // t.print();
    // t.insert(2, 5);
    // t.print();
    // t.insert(6, 6);
    // t.print();
    // t.deleteNode(5);
    // t.print();
    // t.deleteNode(2);
    // t.print();
    // t.findNode(5) == 1 ? cout<<"node found\n" : cout<<"node not found\n";
    // t.findNode(1) == 1 ? cout<<"node found\n" : cout<<"node not found\n";
    return 0;
}
