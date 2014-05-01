vi G[MAX];
vector<pii> brdg;
stack<int> roots, S;
int num[MAX], inS[MAX], t, V;

void visit(int v, int u){
    num[v] = ++t;
    S.push(v); inS[v] = 1;
    roots.push(v);
    repit(e, G[v]){
        int w = *e;
        if(!num[w]) visit(w, v);
        else if(u != w && inS[w])
            while(num[roots.top()] > num[w])
                roots.pop();
    }
    if(v == roots.top()){
        int tu = u, tv = v;
        if(tu > tv) swap(tu, tv);
        brdg.pb(pii(tu, tv)); 
        while(1){
            int w = S.top(); S.pop();
            inS[w] = 0;
            if(v == w) break;
        }
        roots.pop();
    }
}

void bridge(){
    memset(num, 0, sizeof(num));
    memset(inS, 0, sizeof(inS));
    brdg.clear();
    while(S.size()) S.pop();
    while(roots.size()) roots.pop();
    t = 0;
    rep(u,V) if(num[u] == 0){
        visit(u,V);
        brdg.pop_back();
    }
}
