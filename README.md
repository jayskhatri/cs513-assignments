# cs513-assignments

## [Assignment 1](https://github.com/jayskhatri/cs513-assignments/tree/main/assn1): Threaded Binary Search Tree
1) insert(x)
2) delete(x)
3) search(x)
4) reverseInorder()
5) successor(ptr)
6) split(k)
7) allElementsBetween(k1, k2)
8) kthElement(k)
9) printTree()

## [Assignment 2](https://github.com/jayskhatri/cs513-assignments/tree/main/assn2): AVL Tree without maintaining height
### structure of classes

- Class AVL_Node
```
class AVL_Node{ 
  private: 
    int key; 
    int bf;  // balance factor bf = height(left subtree) – height(right subtree) 
    AVL_Node *LChild, *RChild; 
  friend class AVL_Tree; 
};
```
- Class AVL_Tree
```
class AVL_Tree{ 
  private: 
    AVL_Node *root; 
public: 
    AVL_Tree(); 
    AVL_Tree(const AVL_Tree &T); 
    AVL_Tree &operator=(const AVL_Tree &T); 
    void AVL_Insert(int k); 
    void AVL_Delete(int k); 
    bool AVL_Search(int k); 
    void AVL_Print(const char *filename); 
    ~AVL_Tree(); 
}; 
```

## [Assignment 3](https://github.com/jayskhatri/cs513-assignments/tree/main/assn3): Treap + Theoritical and Empirical comparison between BST, AVL and Treap


## [Assignment 4](https://github.com/jayskhatri/cs513-assignments/tree/main/assn4): Graph and operations

1) Performing DFS traversal on the graph and classifying all the edges (tree/forward/back/cross).

2) Finding all strongly connected components using Tarjan’s algorithm.

3) Creating another graph G’= (V, E’), where E’ is a subset of E, such that (a) G’ has the same strongly connected components as G, (b) G’ has the same component graph as G, and (c) E’ is as small as possible.

4) Finding whether the graph is semiconnected or not.

5) Dijkstra's algorithm