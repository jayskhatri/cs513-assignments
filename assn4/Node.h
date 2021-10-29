#include "Edge.h"
#include <vector>
using namespace std;

class Node{
    private:
        vector<Edge> edges;
        friend class Graph;

    public:
        Node(){}
        Node(vector<Edge> e): edges(e){}
};