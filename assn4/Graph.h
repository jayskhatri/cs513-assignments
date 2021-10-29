#include <bits/stdc++.h>
#include "Node.h"
using namespace std;

//class definition of Graph
class Graph{
    private:
        int vertices;
        vector<Node> adjList;

        //dfs helper function
        void dfs_visit(int u, vector<int> &color, vector<int> &d, vector<int> &f, vector<int> &parent, int &time, ofstream &fout);

        //helper function for tarjan's algorithm 
        void tarjanHelp(int u, vector<int>&disc, vector<int>&low, stack<int> &st, vector<int> &color, int &time, vector<vector<int>> &comp);
        
        //helper fucntion for topological sorting
        void topologicalSortHelp(int u, vector<bool> &visited, stack<int> &st);

        //function to find topological sort
        void topologicalSort(vector<int> &topo);

        //function to check whether 2 vertices are either way connected or not
        bool isConnected(int src, int dest);

        //cloning graph
        Graph cloneGraph(const Graph &g);

        //destroy graph
        void destroyGraph();

        //condense graph
        void condenseGraph(vector<vector<int>> &comp, Graph &g);

        //direct connected
        bool isDirectConnected(int src, int dest);

        //helper function to minimise the function
        void minimiseGraphHelper(int u, vector<int>&, vector<int> &parent, vector<int> &startTime, vector<int> &low, int &time, Graph &, set<pair<int, int>> &connectedCompo, unordered_map<int, pair<int, int>> &);
    public:

        //constructor
        Graph();

        //parameterised constructor
        Graph(int vertices);

        //parameterised constructor
        Graph(int n, vector<Node> &edges);

        //copy constructor
        Graph(const Graph &g);

        //destructor
        ~Graph();
        
        //add edge
        void add_edge(int src, int dest, int wt);

        //remove edge
        void remove_edge(int src, int dest);
        
        //dfs of a graph
        void dfs();

        //tarjan algorithm to find stringly connected components
        vector<int> tarjan(vector<vector<int>> &comp);

        //creating a G' graph as small as possible
        void minimiseGraph();

        //function to find whether the graph is semi-connected or not
        bool isSemiconnected();

        //dijkstra algorithm to find distance between 2 nodes
        int dijkstra(int src, int dest);
        
        //print the graph using graphviz
        void printGraph();

        //function to print all the stongly connected components
        void printSCC(vector<vector<int>> &comp);   
};