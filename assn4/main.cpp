#include <bits/stdc++.h>
#include "Graph.h"
using namespace std;

//random generation of the graph
string generateRandomTestGraph(){
    //seeding
    srand((unsigned)time(0));
    cout<<"Generating random graph, max. node which can be present in the random graph is 20"<<endl;
    
    //max number of nodes are 20
    int nodes = rand()%20+1;
    int maxEdges = nodes * (nodes-1) / 2;
    int edges = rand()%maxEdges+1;
    string filename = "graph_"+to_string(nodes) + "_" + to_string(edges) + ".txt";
    
    //open file to write
    ofstream fout(filename);
    fout<<nodes<<" "<<edges<<endl;
    set<pair<int, int>> addedEdges;

    //generating edges
    for(int i=0; i<edges; i++){
        int u = rand()%nodes+1;
        int v = rand()%nodes+1;
        int w = rand()%30+1;
        //if edge is not already added
        if(addedEdges.find(make_pair(u, v)) == addedEdges.end()){
            fout<<u<<" "<<v<<" "<<w<<endl;
            addedEdges.insert(make_pair(u, v));
        }
        //if edge is already generated
        else{
            i--;
        }
    }

    fout.close();
    return filename;
}

int main(int argc, char const *argv[]){

    cout<<"This program is a graph implementation using adjacency list\nAuthored by Jay Khatri\n\n";
    char ch = ' ';
    if(argv[1] == NULL){
        cout<<"Please enter the input file name in command line i.e. a <filename>.txt"<<endl;
        cout<<"As you have not passed testcase filename as command line argument, program will take random graph and proceed with it.\nDo you want to continue with random graph? (y/n) ";
        cin>>ch;
        if(ch == 'n' || ch == 'N') return 1;
    }
    Graph g;
    int edges, nodes;
    int u, v, w;
    ifstream fin;

    //if user wants to generate the random graph
    if(ch == 'y' || ch == 'Y'){
        string filename = generateRandomTestGraph();
        fin.open(filename);
        fin>>nodes >> edges;
        Graph gf(nodes);
        //creating graph
        for(int i=0; i<edges; i++){
            fin>> u >> v >> w;
            gf.add_edge(u, v, w);
        }
        cout<<"Graph is successfully loaded from the file "<<filename<<endl;
        g = gf;
    }else {
        fin.open(argv[1]);
        if(!fin){
            cout<<"File not found. Please enter the correct filename"<<endl;
            return 1;
        }
        fin>>nodes >> edges;
        Graph gf(nodes);

        //creating graph
        for(int i=0; i<edges; i++){
            fin>> u >> v >> w;
            gf.add_edge(u, v, w);
        }
        cout<<"Graph is successfully loaded from the file "<<argv[1]<<endl;
        g = gf;
    }
    g.printGraph();

    char choice;
    do{
        cout<<"\n\nPress 1. for DFS on the graph\nPress 2. for running Tarjan Algo (SCC finding)\nPress 3. for finding subgraph of the graph\nPress 4. to check whether graph is semiconnected or not\nPress 5. to find distance between 2 nodes using Dijkstra Algorithm\nPress 6. to print graph\nPress 7. to generate the random graph\nPress 0. to exit\nEnter your choice: "; cin>>choice;

        switch (choice)
        {
            case '1':
                {
                    g.dfs();
                    break;
                }
            
            case '2':
                {
                    vector<vector<int>> comp;
                    g.tarjan(comp);
                    g.printSCC(comp);
                    break;
                }

            case '3': 
                {
                    g.minimiseGraph();
                    break;
                }

            case '4':
                {
                    if(g.isSemiconnected()){
                        cout<<"Graph is semiconnected"<<endl;
                    }
                    else{
                        cout<<"Graph is not semiconnected"<<endl;
                    }
                    break;
                }
            
            case '5':
                {
                    int src, dest;
                    cout<<"Enter source and destination (src dest): "; cin>>src>>dest;
                    int ans = g.dijkstra(src, dest);
                    ans == INT_MAX ? cout<<"Distance between "<<src<<" and "<<dest<<" is Unreachable"<<endl : cout<<"Distance between "<<src<<" and "<<dest<<" is "<<ans<<endl;
                    break;
                }

            case '6':
                {
                    g.printGraph();
                    break;
                }
            
            case '7':
                {
                    string filename = generateRandomTestGraph();
                    char wantToPerform;
                    cout<<"Graph is successfully generated and saved in the file "<<filename<<endl;
                    cout<<"Do you want to perform all operations on that graph? (y/n) "; cin>>wantToPerform;
                    if(wantToPerform == 'y'){
                        cout<<endl<<"Program will take some larger amount of time, please don't close it\n";
                        ifstream f(filename);
                        f>>nodes>>edges;
                        Graph newG(nodes);
                        
                        for(int i=0; i<edges; i++){
                            f>>u>>v>>w;
                            newG.add_edge(u, v, w);
                        }
                        g = newG;
                    }
                    break;
                }
            
            case '0':
                {
                    fin.close();
                    g.~Graph();
                    exit(0);
                    break;
                }

            default:
                break;
        }
    } while(choice != '0');

    fin.close();
    return 0;
}