vi G[MAX];
vvi scc; // ここに強連結成分分解の結果が入る
stack<int> S;
int inS[MAX], low[MAX], num[MAX], t, V;

void visit(int v){
    low[v] = num[v] = ++t;
    S.push(v); inS[v] = 1;
    repit(e,G[v]){
        int w = *e;
        if(num[w] == 0){
            visit(w);
            low[v] = min(low[v], low[w]);
        }
        else if(inS[w]) low[v] = min(low[v], num[w]);
    }
    if(low[v] == num[v]){
        scc.pb(vi());
        while(1){
            int w = S.top(); S.pop();
            inS[w] = 0;
            scc.back().pb(w);
            if(v == w) break;
        }
    }
}

void stronglyCC(){
    t = 0;
    scc.clear();
    memset(num, 0, sizeof(num));
    memset(low, 0, sizeof(low));
    memset(inS, 0, sizeof(inS));
    while(S.size()) S.pop();
    rep(u,V) if(num[u] == 0) visit(u);
}

