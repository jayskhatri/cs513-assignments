#include<iostream>
//linkedlist node class
class LLNode {
	public:
		int data;
		LLNode *next;
		LLNode(int x){
			this->data = x;
			this->next = NULL;
		}
};
