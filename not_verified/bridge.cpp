/*
  from Spaghetti Source
  O(V+E)
  verified ACAC003 D
  edgeはそのときに必要な変数だけ使えばいい
  重複はしない
*/
struct edge{
    int to, cap, rev;
    edge(){}
    edge(int to):to(to){}
    edge(int to, int cap):to(to),cap(cap){}
    edge(int to, int cap, int rev):to(to),cap(cap),rev(rev){}
};

typedef vector<edge> Edges;
typedef vector<Edges> Graph;
typedef pair<int,int> pii;

void visit(const Graph& g, int v, int u, vector<pii>& brdg, vector<vector<int> >& tecomp,
           stack<int>& roots, stack<int>& S, vector<bool>& inS, vector<int>& num, int& time){
    num[v] = ++time;
    S.push(v); inS[v] = true;
    roots.push(v);
    repit(e, g[v]){
        int w = e->to;
        if(!num[w]) visit(g, w, v, brdg, tecomp, roots, S, inS, num, time);
        else if(u != w && inS[w])
            while(num[roots.top()] > num[w])
                roots.pop();
    }
    if(v == roots.top()){
        int tu = u, tv = v;
        if(tu > tv) swap(tu, tv); // 常にu <= vになるように入れる.
        brdg.pb(pii(tu, tv)); 
        tecomp.pb(vector<int>());
        while(1){
            int w = S.top(); S.pop();
            inS[w] = false;
            tecomp.back().pb(w);
            if(v == w) break;
        }
        roots.pop();
    }
}

void bridge(const Graph& g, vector<pii>& brdg, vector<vector<int> >& tecomp){
    const int n = g.size();
    vector<int> num(n);
    vector<bool> inS(n);
    stack<int> roots, S;
    int time = 0;
    rep(u,n) if(num[u] == 0){
        visit(g, u, n, brdg, tecomp, roots, S, inS, num, time);
        brdg.pop_back();
    }
}
