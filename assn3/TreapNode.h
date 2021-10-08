#include<bits/stdc++.h>
#include<time.h>
//TreapNode class definition
class TreapNode{
    private:
        int key;
        int priority;
        TreapNode *left, *right;
        friend class Treap;
    public:
        //constructor
        TreapNode(int k){
            key = k;            
            priority = 0;
            left = right = NULL;
        }
        //constructor
        TreapNode(int k, int p){
            key = k;            
            priority = p;
            left = right = NULL;
        }
};