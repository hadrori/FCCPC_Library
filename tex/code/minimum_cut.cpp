int minimum_cut(const graph &g) {
    int n = g.size();
    vector< vector<int> > h(n, vector<int>(n)); // make adj. matrix
    rep(u,n) for(auto &e: g[u]) h[e.src][e.dst] += e.weight;
    vector<int> V(n); rep(u, n) V[u] = u;

    int cut = 1e9;
    for(int m = n; m > 1; m--) {
        vector<int> ws(m, 0);
        int u, v;
        int w;
        rep(k, m) {
            u = v; v = max_element(ws.begin(), ws.end())-ws.begin();
            w = ws[v]; ws[v] = -1;
            rep(i, m) if (ws[i] >= 0) ws[i] += h[V[v]][V[i]];
        }
        rep(i, m) {
            h[V[i]][V[u]] += h[V[i]][V[v]];
            h[V[u]][V[i]] += h[V[v]][V[i]];
        }
        V.erase(V.begin()+v);
        cut = min(cut, w);
    }
    return cut;
}
