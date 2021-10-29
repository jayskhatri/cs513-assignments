#include "Graph.h"
#include <bits/stdc++.h>
#define WHITE 0
#define GRAY 1
#define BLACK 2

using namespace std;

Graph::Graph(){
    vertices = 0;
}

Graph::Graph(int n){
    adjList.resize(n);
    vertices = n;
}

Graph::Graph(int n, vector<Node> &adj){
    adjList.resize(n);
    adjList = adj;
    vertices = n;
}

Graph::Graph(const Graph &g){
    Graph copy = cloneGraph(g);
    adjList = copy.adjList;
    vertices = copy.vertices;
}

Graph::~Graph(){
    destroyGraph();
}

//destroy graph and free memory
void Graph::destroyGraph(){
    for(int i = 0; i < vertices; i++){
        adjList[i].edges.clear();
    }
    adjList.clear();
    vertices = -1;
}

//makes the copy of the graph
Graph Graph::cloneGraph(const Graph &g){
    Graph newGraph(g.vertices);
    for(int i = 0; i < g.vertices; i++){
        for(int j = 0; j < g.adjList[i].edges.size(); j++){
            newGraph.adjList[i].edges.push_back(g.adjList[i].edges[j]);
        }
    }
    return newGraph;
}

// function which adds the edge with the given source, destination and edge weight
void Graph::add_edge(int src, int dest, int wt){
    //1 <= src, dest <= number of vertices
    assert(src <= vertices && dest <= vertices && src > 0 && dest > 0);
    Edge e(dest, wt);
    adjList[src-1].edges.push_back(e);
}

//function which removed the edge between given source and destination
void Graph::remove_edge(int src, int dest){
    //1 <= src, dest <= number of vertices
    assert(src <= vertices && dest <= vertices && src > 0 && dest > 0);
    for(int i = 0; i < adjList[src-1].edges.size(); i++){
        if(adjList[src-1].edges[i].dest == dest){
            adjList[src-1].edges.erase(adjList[src-1].edges.begin() + i);
            break;
        }
    }
}

// DFS helper function
void Graph:: dfs_visit(int u, vector<int> &color, vector<int> &d, vector<int> &f, vector<int> &parent, int &time, ofstream &fout){
    color[u-1] = GRAY;
    time++; 
    d[u-1] = time; 
    for(auto &i : adjList[u-1].edges){ //explore all the adjacent nodes
        // cout<<"from :"<<u<<" to: "<<i.dest<<endl;
        if(color[i.dest-1] == WHITE){ //if the adjacent node is not visited
            parent[i.dest-1] = u; //set the parent of the adjacent node to the current node
            dfs_visit(i.dest, color, d, f, parent, time, fout); //recursive call
            fout<< "\t\"" << u << "\" -> \"" << i.dest <<"\"" << endl;
        }
        else if(color[i.dest-1] == GRAY){
            // cout<<"Back edge "<<u<<" to "<<i.dest<<"\n";
            fout<< "\t\"" << u << "\" -> \"" << i.dest <<"\"[style=dotted, label=\"b\"]" << endl;
        }

        else if(d[i.dest-1] > d[u-1] && parent[i.dest-1] != u){
            fout<<"\tedge [color = blue]\n";
            // cout << "forward edge " << u << " " << i.dest << endl;
            fout<< "\t\"" << u << "\" -> \"" << i.dest <<"\"[style=dotted, label=\"f\"]" << endl;
            fout<<"\tedge [color = black]\n";
        }
        else if(d[i.dest-1] < d[u-1] && parent[i.dest-1] != u){
            fout<<"\tedge [color = red]\n";
            // cout << "cross edge " << u << " " << i.dest << endl;
            fout<< "\t\"" << u << "\" -> \"" << i.dest <<"\"[style=dotted, label=\"c\"]" << endl;
            fout<<"\tedge [color = black]\n";
        }
    }
    color[u-1] = BLACK; //mark the current node as visited
    time++; //increment the time
    f[u-1] = time; //set the finishing time of the current node
}

//helper function to find the strongly connected components using the low number
void Graph::tarjanHelp(int u, vector<int>&disc, vector<int>&low, stack<int> &st, vector<int> &color, int &time, vector<vector<int>> &comp){
    //set discovery time and low number of the current node
    disc[u-1] = low[u-1] = ++time;
    color[u-1] = GRAY;
    st.push(u);

    //explore all the adjacent nodes
    for(auto &i : adjList[u-1].edges){
        // if the adjacent node is not visited
        if(color[i.dest-1] == WHITE){
            //recursive call to tarjanHelp
            tarjanHelp(i.dest, disc, low, st, color, time, comp);
            //set the low number of the current node
            low[u-1] = min(low[u-1], low[i.dest-1]);
        }
        // if the adjacent node is already explored
        else if(color[i.dest-1] == GRAY){
            //set the low number of the current node
            low[u-1] = min(low[u-1], disc[i.dest-1]);
        }
    }

    //if discovery time and low number are equal then all vertex belong to same component
    if(disc[u-1] == low[u-1]){
        vector<int> temp;
        int t;
        //pop all the vertices from the stack and add them to the component
        while(st.top() != u){
            t = st.top();
            st.pop();
            color[t-1] = BLACK;
            temp.push_back(t);
        }
        t = st.top();
        st.pop();
        color[t-1] = BLACK;
        temp.push_back(t);
        comp.push_back(temp);
    }
}

//function to print the graph using graphviz
void Graph::printGraph(){
    ofstream fout("graph.gv");
    fout << "digraph dirGraph {" << endl;
    
    //adding edges
    for(int i=1; i<=adjList.size(); i++){
        for(auto &j : adjList[i-1].edges){
            fout<< "\t\"" << i << "\" -> \"" << j.dest <<"\"[label = \""<<j.wt<<"\"]" << endl;
        }
    }
    //adding nodes
    for(int i=1; i<=adjList.size(); i++){
        fout<<"\t"<<i<<"[label=\""<<i<<"\"]" << endl;
    }
    fout<<"}"<<endl;

    char choice;
    cout<<"Do you want to print the graph? (y/n) :"; cin>>choice;
    if(choice == 'y' || choice == 'Y'){
        //calling the system command to generate the tree png 
        char command[30];
        strcpy(command, "dot -Tpng graph.gv -o ");
        strcat(command, "graph.png");
        system(command);

        #ifdef _WIN32
            system("graph.png");
        #endif
    }
    fout.close();
}

// function to find the depth first search
void Graph::dfs(){
    vector<int> color(vertices, WHITE);
    vector<int> d(vertices, -1);
    vector<int> f(vertices, -1);
    vector<int> parent(vertices, -1);
    int time = 0;
    ofstream fout("graph.gv");
    fout << "digraph dirGraph {" << endl;

    //loop over all the vertices
    for(int i = 1; i <= adjList.size(); i++){
        //if vertex is unvisited call the helper function
        if(color[i-1] == WHITE){
            dfs_visit(i, color, d, f, parent, time, fout);
        }
    }

    //add the vertices to the graph with start time and finish time
    for(int i = 1; i <= adjList.size(); i++){
        fout<<"\t"<<i<<"[label=\""<<i<<"{"<<d[i-1]<<"/"<<f[i-1]<<"}\"]" << endl;
        // cout << "Node " << i << ": " << "d = " << d[i-1] << ", f = " << f[i-1] << endl;
    }
    fout<<"}"<<endl;

    char choice;
    cout<<"Do you want to print the DFS graph? (y/n) :"; cin>>choice;
    if(choice == 'y' || choice == 'Y'){
        //calling the system command to generate the tree png 
        char command[30];
        strcpy(command, "dot -Tpng graph.gv -o ");
        strcat(command, "graph.png");
        system(command);

        #ifdef _WIN32
            system("graph.png");
        #endif
    }

    //removing the source (graph.gv) file
    remove("graph.gv");
    fout.close();
}

//function to get strongly connected components
vector<int> Graph::tarjan(vector<vector<int>> &comp){
    vector<int> disc(vertices, -1);
    vector<int> low(vertices, -1);
    vector<int> color(vertices, WHITE);
    stack<int> st;
    int time = 0;

    //loop over all the vertices
    for(int i=1; i<=vertices; i++)
        //if vertex is not yet discovered call the helper function
        if(color[i-1] == WHITE)
            tarjanHelp(i, disc, low, st, color, time, comp);
    
    return low;
}

//function to find the minimum distance from source to destination
int Graph::dijkstra(int src, int dest){
    vector<int> d(vertices, INT_MAX);
    vector<int> parent(vertices, -1);
    vector<bool> visited(vertices, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, src));
    d[src-1] = 0;

    //loop over all the vertices accoriding to the min distance
    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();
        visited[u-1] = true;
        //traverse all the edges of the node
        for(auto &i: adjList[u-1].edges){
            // if the node is not visited and the found distance is greater than the current distance (until node + edge weight) then update the distance
            if(!visited[i.dest-1] && d[i.dest-1] > d[u-1] + i.wt){
                //update distance
                d[i.dest-1] = d[u-1] + i.wt;
                //update parent node
                parent[i.dest-1] = u;
                //push the node to the priority queue with new min. distance
                pq.push(make_pair(d[i.dest-1], i.dest));
            }
        }
    }
    //return the distance of destination node
    return d[dest-1];
}

//helper function for topological sort
void Graph::topologicalSortHelp(int u, vector<bool> &visited, stack<int> &st){
    //mark the node u as visited
    visited[u-1] = true;
    //explore all the adjacent nodes of u
    for(auto &i: adjList[u-1].edges){
        if(!visited[i.dest-1]){
            topologicalSortHelp(i.dest, visited, st);
        }
    }
    //push the node u to the stack
    st.push(u);
}

//function which returns the topological sort of the graph
void Graph::topologicalSort(vector<int> &topo){
    vector<bool> visited(vertices, false);
    stack<int> seq;

    //visit all the vertices
    for(int i=1; i<=vertices; i++){
        if(!visited[i-1]){
            topologicalSortHelp(i, visited, seq);
        }
    }

    while(!seq.empty()){
        topo.push_back(seq.top());
        seq.pop();
    }
}

//function which checks whether there exist a path from src to destination
bool Graph::isConnected(int src, int dest){
    vector<bool> visited(vertices, false);
    stack<int> st;
    //applying dfs on given vertices
    topologicalSortHelp(src, visited, st);
    // if the destination is not visited then there is no path
    while(!st.empty()){
        if(st.top() == dest){
            return true;
        }
        st.pop();
    }
    return false;
}

//function to check whether the given graph is semiconnected or not
bool Graph::isSemiconnected(){
    //find scc
    vector<vector<int>> comp;
    tarjan(comp);

    //base case
    if(comp.size() == 1){
        return true;
    }

    //Take each strong connected component as a virtual vertex and create a new virtual graph - component graph
    Graph cGraph(comp.size());
    condenseGraph(comp, cGraph);

    //finding topological order of the component graph
    vector<int> topo;
    cGraph.topologicalSort(topo);

    //checking if the graph is semiconnected
    for(int i=0; i<topo.size(); i++){
        //if both path does not exist then given graph is not semiconnected
        if(!cGraph.isConnected(topo[i], topo[i+1]) || !cGraph.isConnected(topo[i+1], topo[i])){
            return false;
        }
    }

    return true;
}

//function to print the strongly connected component in different colors
void Graph:: printSCC(vector<vector<int>> &comp){ 
    // colors for scc
    string colors[] = {"antiquewhite4", "aquamarine3", "aquamarine4", "aqua", "azure4", "blue","bisque", "brown","blueviolet", 
    "cadetblue","chartreuse3","chartreuse4","chocolate","chocolate4","coral","coral4","cornflowerblue","cornsilk3","crimson",
    "cyan", "cyan4", "darkgoldenrod", "darkgreen", "darkkhaki", "darkolivegreen", "darkorange", "darkorchid", "darkred", "darksalmon",
    "darkseagreen", "darkslateblue", "darkslategray", "darkturquoise", "darkviolet", "deeppink", "deepskyblue", "firebrick", "cornsilk1" }; 
    
    
    ofstream fout("graph.gv");
    fout << "digraph dirGraph {" << endl;

    //adding edges
    for(int i=1; i<=adjList.size(); i++){
        for(auto &j : adjList[i-1].edges){
            fout<< "\t\"" << i << "\" -> \"" << j.dest <<"\"[label = \""<<j.wt<<"\"]" << endl;
        }
    }

    //adding vertices with colors
    int cnt = 1;
    for(auto &i : comp){
        cout<<"Component "<<cnt<<": ";
        int compoInd = i[0];
        for(auto &j : i){
            cout<<j<<" ";
            fout<<"\t"<<j<<"[label=\""<<j<<" { "<<cnt<<" }\", color="<<colors[compoInd-1]<<",style=filled]" << endl;
        }
        cout<<endl;
        cnt++;
    }

    fout<<"}"<<endl;

    char choice;
    cout<<"Do you want to print the SCC graph? (y/n) :"; cin>>choice;
    if(choice == 'y' || choice == 'Y'){
        //calling the system command to generate the tree png 
        char command[30];
        strcpy(command, "dot -Tpng graph.gv -o ");
        strcat(command, "graph.png");
        system(command);

        #ifdef _WIN32
            system("graph.png");
        #endif
    }
}

//function to check whether the src and dest are connected with the edge
bool Graph::isDirectConnected(int src, int dest){
    for(int i=0; i<adjList[src-1].edges.size(); i++){
        if(adjList[src-1].edges[i].dest == dest){
            return true;
        }
    }
    return false;
}

//condense graph and make scc as vertex
void Graph::condenseGraph(vector<vector<int>> &comp, Graph &cGraph){
    
    //print component
    // int cnt = 1;
    // for(auto &i : comp){
    //     cout<<"Component "<<cnt++<<" contains vertices : ";
    //     for(auto &j : i){
    //         cout<<j<<" ";
    //     }
    //     cout<<endl;
    // }

    set<pair<int, int>> connectedComponent;

    for(int i=0; i<comp.size(); i++){
        for(int j = 0; j<comp.size(); j++){
            //checking if the components are different
            if(i != j){
                //checking if the vertices are connected
                for(int k=0; k<comp[i].size(); k++){
                    for(int l=0; l<comp[j].size(); l++){
                        // if vertices are direct connnected and any parellel edge is not added before
                        if(isDirectConnected(comp[i][k], comp[j][l]) && connectedComponent.find(make_pair(i+1, j+1)) == connectedComponent.end()){
                            cGraph.add_edge(i+1, j+1, 1); //weight will be one only
                            connectedComponent.insert(make_pair(i+1, j+1)); //adding the edge to the set
                        }
                    }
                }
            }
        }
    }
    // print condensed graph where vertices are the strongly connected component's id
    // cGraph.printGraph();
}


//helper function which helps in minimising the graph
void Graph::minimiseGraphHelper(int u, vector<int> &color, vector<int> &parent, vector<int> &startTime, vector<int> &low, int &time, Graph &graph, set<pair<int, int>> &connectedCompo, unordered_map<int, pair<int, int>> &sccSize){
    color[u-1] = GRAY; //mark vertex as exploring
    startTime[u-1] = ++time; //start time of the vertex

    for(auto &i : adjList[u-1].edges){ //explore all the adjacent nodes
        //tree edge
        if(color[i.dest-1] == WHITE){ //if the adjacent node is not visited
            parent[i.dest-1] = u; //set the parent of the adjacent node to the current node
            minimiseGraphHelper(i.dest, color, parent, startTime, low, time, graph, connectedCompo, sccSize); //recursive call
            if(!graph.isDirectConnected(i.dest, u) || sccSize[u].second == 2 || isConnected(i.dest, u)){
                graph.add_edge(u, i.dest, i.wt); //add the edge between the current node and the adjacent node
                if(sccSize[u].first != sccSize[i.dest].first){ // if edge between different component then add the id of component to set 
                    connectedCompo.insert(make_pair(sccSize[u].first, sccSize[i.dest].first));
                }
            }
        }

        //back edge
        else if(color[i.dest-1] == GRAY){
            //if the destination node has the lower low value then current node
            if(sccSize[i.dest].first == sccSize[u].first && sccSize[u].second >= 2 && isConnected(i.dest, u)){
                graph.add_edge(u, i.dest, i.wt);
            } 
        }

        //cross edge
        else if(startTime[i.dest-1] < startTime[u-1]){
            if(connectedCompo.find(make_pair(sccSize[u].first, sccSize[i.dest].first)) == connectedCompo.end()){
                graph.add_edge(u, i.dest, i.wt);
                connectedCompo.insert(make_pair(sccSize[u].first, sccSize[i.dest].first));
            }
        }

        //forward edge
        else if(startTime[i.dest-1] > startTime[u-1]){
            if(sccSize[u].first != sccSize[i.dest-1].first && connectedCompo.find(make_pair(sccSize[u].first, sccSize[i.dest].first)) == connectedCompo.end()){
                graph.add_edge(u, i.dest, i.wt);
                connectedCompo.insert(make_pair(sccSize[u].first, sccSize[i.dest].first));
            }
        }
    }
    color[u-1] = BLACK; //mark the current node as visited
    time++; //increment the time
}

// create new graph from same graph which has the same strongly connected components, has the same component graph as G minimum edges 
void Graph::minimiseGraph(){
    //running tarjan algo to get SCC and it will return the low values
    vector<vector<int>> comp;
    vector<int> low = tarjan(comp);

    //make one representative from each scc i.e. id
    //adding the pair of representative and size into map with id as index
    unordered_map<int, pair<int, int>> sccSize;
    int id = 1;
    for(int i=0; i<comp.size(); i++){
        for(int j=0; j<comp[i].size(); j++){
            sccSize[comp[i][j]] = make_pair(id, comp[i].size());
        }
        id++;
    }

    //new graph
    Graph nGraph(vertices);
    //required data structure
    vector<int> color(vertices, WHITE);
    vector<int> parent(vertices, -1);
    vector<int> startTime(vertices, -1);
    set<pair<int, int>> connectedComponent;
    int time = 0;

    //running dfs over the graph
    for(int i=1; i<=vertices; i++){
        //if the node is not visited
        if(color[i-1] == WHITE){
            minimiseGraphHelper(i, color, parent, startTime, low, time, nGraph, connectedComponent, sccSize);
        }
    }

    cout<<"low values: ";
    for(auto &i : low){
        cout<<i<<" ";
    }
    cout<<endl;
    
    // print the graph
    nGraph.printGraph();
}


//remove extra edges from given strongly connected component
// void Graph::removeEdges(vector<int> &scc, Graph &nGraph, set<pair<int, int>> &connectedComponent){
//     //remove the extra edges from the graph with the property of strongly connected


//     set<pair<int, int>> cycleEdges;
//     for(int i=0; i<scc.size(); i++){
//         for(int j=0; j<scc.size(); j++){
//             if(i != j){
//                 if(isDirectConnected(scc[i], scc[j])){
//                     cycleEdges.insert(make_pair(scc[i], scc[j]));
//                 }
//             }
//         }
//     }
    

//     //add the cycle edges into the new graph
//     for(auto &i : cycleEdges){
//         if(connectedComponent.find(i) == connectedComponent.end()){
//             nGraph.add_edge(i.first, i.second, 1);
//             // connectedComponent.insert(i);
//         }
//     } 

//     //print the cycle edges
//     cout<<"Cycle Edges: ";
//     for(auto &i : cycleEdges){
//         cout<<"("<<i.first<<", "<<i.second<<") ";
//     }
//     cout<<endl;
    
// }

// void Graph::createSubsetGraph(){
//     vector<vector<int>> comp;
//     tarjan(comp);

//     Graph nGraph(vertices);
//     // nGraph.adjList = adjList;

//     // nGraph.printGraph();
//     set<pair<int, int>> connectedComponents;

//     for(int i=0; i<comp.size(); i++){
//         for(int j = 0; j<comp.size(); j++){
//             //between different scc
//             if(i != j){
//                 for(int k=0; k<comp[i].size(); k++){
//                     for(int l=0; l<comp[j].size(); l++){
//                         //if the vertices are directly connected and components are not connected
//                         if(isDirectConnected(comp[i][k], comp[j][l]) && connectedComponents.find(make_pair(i+1, j+1)) == connectedComponents.end()){
//                             nGraph.add_edge(comp[i][k], comp[j][l], 1); //weight will be one only
//                             connectedComponents.insert(make_pair(i+1, j+1));
//                         }
//                     }
//                 }
//             }
//             //in the same scc we remove the edges! 
//             else if(i==j) {
//                 //remove extra edges from given strongly connected component
//                 removeEdges(comp[i], nGraph, connectedComponents);
//             }
//         }
//     }

//     nGraph.printGraph();

//     // for(int i=0; i<scc.size(); i++){
//     //     if(scc[i].size() > 1){
//     //         cout<<"Component "<<i+1<<" : "<<endl;
//     //         removeEdges(scc[i], nGraph);
//     //     }
//     // }

// }

//helper function which helps in minimising the graph
// void Graph::minimiseGraphHelper2(int u, vector<int> &color, vector<int> &parent, vector<int> &startTime, vector<int> &low, int &time, Graph &graph, set<pair<int, int>> &connectedCompo, unordered_map<int, pair<int, int>> &sccSize){
//     color[u-1] = GRAY; //mark vertex as exploring
//     startTime[u-1] = ++time; //start time of the vertex

//     for(auto &i : adjList[u-1].edges){ //explore all the adjacent nodes
//         //tree edge
//         if(color[i.dest-1] == WHITE){ //if the adjacent node is not visited
//             parent[i.dest-1] = u; //set the parent of the adjacent node to the current node
//             minimiseGraphHelper(i.dest, color, parent, startTime, low, time, graph, connectedCompo, sccSize); //recursive call
//             if(sccSize[u].first != sccSize[i.dest].first) // if edge between different component then add the id of component to set 
//                 connectedCompo.insert(make_pair(sccSize[u].first, sccSize[i.dest].first));
//             graph.add_edge(u, i.dest, i.wt); //add the edge between the current node and the adjacent node
//         }

//         //back edge
//         else if(color[i.dest-1] == GRAY){
//             // cout<<"Back edge found between "<<u<<" and "<<i.dest<<" low: "<<low[u-1]<<" "<<low[i.dest-1]<<"scc size: "<<sccSize[i.dest-1]<<" connectd: "<<isDirectConnected(i.dest, u)<<endl;
//             //if the destination node has the lower low value then current node
//             if(sccSize[i.dest].first == sccSize[u].first && sccSize[u].second > 2 && isConnected(i.dest, u)){
//                 cout<<"Back edge "<<u<<" "<<i.dest<<" size: "<<sccSize[u].second<<endl;
//                 graph.add_edge(u, i.dest, i.wt);
//                 // connectedCompo.insert(make_pair(sccSize[u].first, sccSize[i.dest].first));
//             }
//         }

//         //cross edge
//         else if(startTime[i.dest-1] < startTime[u-1]){
//             cout<<"Cross edge: "<<u<<" to "<<i.dest<<" between scc id "<<sccSize[u].first<<" to "<<sccSize[i.dest].first<<endl;
//             if(connectedCompo.find(make_pair(sccSize[u].first, sccSize[i.dest].first)) == connectedCompo.end()){
//                 graph.add_edge(u, i.dest, i.wt);
//                 connectedCompo.insert(make_pair(sccSize[u].first, sccSize[i.dest].first));
//             }
//         }
//     }
//     color[u-1] = BLACK; //mark the current node as visited
//     time++; //increment the time
// }