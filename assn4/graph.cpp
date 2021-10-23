#include <bits/stdc++.h>
using namespace std;

#define WHITE 0
#define GRAY 1
#define BLACK 2

int nodes, edges, u, v, w;
vector<vector<pair<int,int>>> listt;

void add_edge(int u, int v, int w){
    listt[u-1].push_back({v-1,w});
}

//kahn's algorithm
void kahnsAlgo(){
    vector<int> color(nodes, WHITE);
    vector<int> dist(nodes, INT_MAX);
    vector<int> parent(nodes, -1);
    vector<int> pq;
    int s = 0;
    dist[s] = 0;
    pq.push_back(s);
    while(!pq.empty()){
        int u = pq.back();
        pq.pop_back();
        for(auto &i : listt[u]){
            int v = i.first;
            int w = i.second;
            if(color[v] == WHITE){
                color[v] = GRAY;
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push_back(v);
            }
        }
        color[u] = BLACK;
    }
}

//finding strongly connected component using tarjan's algo
void tarjan(int u, int p, vector<int> &low, vector<int> &num, vector<int> &color, vector<int> &st, vector<int> &fin, vector<vector<int>> &comp){
    low[u] = num[u] = ++nodes;
    st.push_back(u);
    color[u] = GRAY;
    for(auto &i: listt[u]){
        if(i.first == p){
            continue;
        }
        if(color[i.first] == WHITE){
            tarjan(i.first, u, low, num, color, st, fin, comp);
            low[u] = min(low[u], low[i.first]);
        }
        else if(color[i.first] == GRAY){
            low[u] = min(low[u], num[i.first]);
        }
    }
    if(low[u] == num[u]){
        vector<int> temp;
        int v;
        do{
            v = st.back();
            st.pop_back();
            color[v] = BLACK;
            temp.push_back(v);
        }while(v != u);
        comp.push_back(temp);
    }
}


void dfs_visit(int u, vector<int> &color, vector<int> &d, vector<int> &f, vector<int> &parent, int &time, ofstream &fout){
    color[u] = GRAY;
    time++; 
    d[u] = time; 
    for(auto &i : listt[u]){ //explore all the adjacent nodes
        if(color[i.first] == WHITE){ //if the adjacent node is not visited
            parent[i.first] = u; //set the parent of the adjacent node to the current node
            dfs_visit(i.first, color, d, f, parent, time, fout); //recursive call
            fout<< "\t\"" << u+1 << "\" -> \"" << i.first+1 <<"\"" << endl;
        }
        else if(color[i.first] == GRAY){
            if(parent[u] != i.first){
                cout<<"Back edge "<<u+1<<" to "<<i.first+1<<"\n";
                fout<< "\t\"" << u+1 << "\" -> \"" << i.first+1 <<"\"[style=dotted, label=\"b\"]" << endl;
            }
        }
    }
    color[u] = BLACK; //mark the current node as visited
    time++; //increment the time
    f[u] = time; //set the finishing time of the current node

    for(auto &i : listt[u]){
        if(d[i.first] > d[u] && parent[i.first] != u){
            fout<<"\tedge [color = blue]\n";
            cout << "forward edge " << u+1 << " " << i.first+1 << endl;
            fout<< "\t\"" << u+1 << "\" -> \"" << i.first+1 <<"\"[style=dotted, label=\"f\"]" << endl;
            fout<<"\tedge [color = black]\n";
        }
        else if(d[i.first] < d[u] && parent[i.first] != u){
            fout<<"\tedge [color = red]\n";
            cout << "cross edge " << u+1 << " " << i.first+1 << endl;
            fout<< "\t\"" << u+1 << "\" -> \"" << i.first+1 <<"\"[style=dotted, label=\"c\"]" << endl;
            fout<<"\tedge [color = black]\n";
        }
    }
}

//dfs of graph
void dfs(){
    vector<int> color(nodes, WHITE);
    vector<int> d(nodes, -1);
    vector<int> f(nodes, -1);
    vector<int> parent(nodes, -1);
    int time = 0;
    ofstream fout("graph.gv");
    fout << "digraph dirGraph {" << endl;

    for(int i = 0; i < nodes; i++){
        if(color[i] == WHITE){
            dfs_visit(i, color, d, f, parent, time, fout);
        }
    }

    for(int i = 0; i < nodes; i++){
        fout<<"\t"<<i+1<<"[label=\""<<i+1<<"{"<<d[i]<<"/"<<f[i]<<"}\"]" << endl;
        cout << "Node " << i+1 << ": " << "d = " << d[i] << ", f = " << f[i] << endl;
    }
    fout<<"}"<<endl;

    char choice;
    cout<<"Do you want to print the graph? (y/n) :"; cin>>choice;
    if(choice == 'y'){
        //calling the system command to generate the tree png 
        char command[30];
        strcpy(command, "dot -Tpng graph.gv -o ");
        strcat(command, "p.png");
        system(command);

        #ifdef _WIN32
            system("p.png");
        #endif
    }

	//removing the source (graph.gv) file
	remove("graph.gv");
    fout.close();
}

void printGraph(){
    ofstream fout("graph1.gv");
    fout << "digraph dirGraph {" << endl;

    for(int i=0; i<nodes; i++){
        for(auto &j : listt[i]){
            fout<< "\t\"" << i+1 << "\" -> \"" << j.first+1 <<"\"[label = \""<<j.second<<"\"]" << endl;
        }
    }

    for(int i=0; i<nodes; i++){
        fout<<"\t"<<i+1<<"[label=\""<<i+1<<"\"]" << endl;
    }
    fout<<"}"<<endl;

    char choice;
    cout<<"Do you want to print the graph? (y/n) :"; cin>>choice;
    if(choice == 'y'){
        //calling the system command to generate the tree png 
        char command[30];
        strcpy(command, "dot -Tpng graph1.gv -o ");
        strcat(command, "q.png");
        system(command);

        #ifdef _WIN32
            system("q.png");
        #endif
    }
    fout.close();
}

int dijkstra(int source, int destination){
    vector<int> cost(nodes);
    for(int i=0; i<nodes ; i++) cost[i] = 1e9;
    set<pair<int,int> > st;
    cost[source] = 0;
    st.insert({0,source});
    while(st.size()){
        int current_node = st.begin()->second;
        int weight = st.begin()->first;
        st.erase(st.begin());
        if(current_node == destination )
            return weight;

        for(int i = 0 ; i < listt[current_node].size() ; i++){
            int nxt = listt[current_node][i].first;
            int nxt_weight = listt[current_node][i].second;
            if(cost[nxt]> weight + nxt_weight){
                cost[nxt] =  weight + nxt_weight;
                st.insert({cost[nxt],nxt});
            }
        }
    }
    return -1;
}

int main(int argc, char const *argv[]){
    ios_base::sync_with_stdio(false);
    if(argv[1] == NULL){
        cout<<"Please enter the input file name in command line"<<endl;
        return 1;
    }

    ifstream fin(argv[1]);
    fin>>nodes >> edges;
    listt.resize(nodes);
    
    //creating graph
    for(int i=0; i<edges; i++){
        fin>> u >> v >> w;
        add_edge(u, v, w);
    }

    cout<<"dijkstra distance between s = 0 and t = 3: "<<dijkstra(0,3)<<endl;

    cout<<"dfs"<<endl;
    printGraph();
    dfs();

    cout<<"tarjan"<<endl;
    vector<int> low(nodes, -1);
    vector<int> num(nodes, -1);
    vector<int> color(nodes, WHITE);
    vector<int> st;
    vector<int> finish;
    vector<vector<int>> comp;
    tarjan(0, -1, low, num, color, st, finish, comp);
    for(auto &i : comp){
        cout<<"Component: ";
        for(auto &j : i){
            cout<<j+1<<" ";
        }
        cout<<endl;
    }

    // cout<<"dfs with classification"<<endl;
    // vector<int> d(nodes, -1);
    // vector<int> f(nodes, -1);
    // vector<int> parent(nodes, -1);
    // vector<int> st1;
    // comp.clear();
    // dfs(0, color, d, f, parent, st1, finish, comp);
    // for(auto &i : comp){
    //     cout<<"Component: ";
    //     for(auto &j : i){
    //         cout<<j+1<<" ";
    //     }
    //     cout<<endl;
    // }

    return 0;
}
