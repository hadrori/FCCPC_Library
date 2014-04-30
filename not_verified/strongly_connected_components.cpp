/*
 from Spaghetti Source
 O(V+E)
 not verified (UVa 247)
 */

typedef int Weight;
struct Edge{
    int src, dst;
    Weight weight;
    Edge(int src, int dst, Weight weight) :
        src(src), dst(dst), weight(weight){};
};
typedef vector<Edge> Edges;
typedef vector<Edges> Graph; //有向グラフ

void visit(const Graph &g, int v, vector<vector<int> >& scc,
           stack<int> &S, vector<bool> &inS,
           vector<int> &low, vector<int> &num, int& time){
    low[v] = num[v] = ++time;
    S.push(v); inS[v] = true;
    for(__typeof(g[v].begin()) i = g[v].begin(); i != g[v].end(); i++){
        int w = e -> dst;
        if(num[w] == 0){
            visit(g, w, scc, S, inS, low, num, time);
            low[v] = min(low[v], low[w]);
        }else if(inS[w]) low[v] = min(low[v], num[w]);
    }
    if(low[v] == num[v]){
        scc.push_back(vector<int>());
        while(true){
            int w = S.top(); S.pop(); inS[w] = false;
            scc.back().push_back(w);
            if(v == w) break;
        }
    }
}

void stronglyConnectedComponents(const Graph& g, vector<vector<int> >& scc){
    const int n = g.size();
    vector<int> num(n), low(n);
    stack<int> S;
    vector<bool> inS(n);
    int time = 0;
    for(int u = 0; u < n; u++) if(num[u] == 0)
        visit(g, u, scc, S, inS, low, num, time);
}