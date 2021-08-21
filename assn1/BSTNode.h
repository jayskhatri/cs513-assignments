//Binary search Tree Node class
class BSTNode {
public:
	int key, rCount;
	BSTNode* left, *right;
	bool leftLinkType, rightLinkType; 

	// When the node is first created, it is a leaf node. So, both links must be THREAD
	BSTNode(int key) { this->key = key; this->rCount = 0; left = right = NULL; leftLinkType = rightLinkType = THREAD; }
	
};
