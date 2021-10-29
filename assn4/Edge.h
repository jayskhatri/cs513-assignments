class Edge{
    private:
        // int src;
        int dest;
        int wt;
        friend class Graph;

    public:
        Edge(){
            // src = 0;
            dest = 0;
            wt = 0;
        }
        Edge(int v, int w): dest(v), wt(w){}        
};