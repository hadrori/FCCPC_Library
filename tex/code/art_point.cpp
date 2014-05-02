vi G[MAX], art; // artに関節点のリストが入る
int num[MAX], low[MAX], t, V;

void visit(int v, int u){
    low[v] = num[v] = ++t;
    repit(e,G[v]){
        int w = *e;
        if (num[w] == 0) {
            visit(w, v);
            low[v] = min(low[v], low[w]);
            if ((num[v] == 1 && num[w] != 2) ||
                (num[v] != 1 && low[w] >= num[v])) art.pb(v);
        }
        else low[v] = min(low[v], num[w]);
    }
}
void art_point(){
    memset(low, 0, sizeof(low));
    memset(num, 0, sizeof(num));
    art.clear();
    rep(u,V) if (num[u] == 0) {
        t = 0;
        visit(u, -1);
    }
    /*
    sort(all(art));
    UNIQUE(art);
    */
}
