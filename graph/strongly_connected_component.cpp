struct scc {
    const int n;
    graph G;
    int cnt;
    vector<int> num, low, in;
    stack<int> stk;
    vector<vector<int> > comp;
    void dfs(int v) {
        num[v] = low[v] = ++cnt;
        stk.push(v), in[v] = true;
        for (const int nv : G[v]) {
            if (num[nv] == 0) {
                dfs(nv);
                low[v] = min(low[v], low[nv]);
            } else if (in[nv]) {
                low[v] = min(low[v], num[nv]);
            }
        }
        if (low[v] == num[v]) {
            comp.eb();
            int w; do {
                w = stk.top();
                stk.pop(), in[w] = false;
                comp.back().pb(w);
            } while (w != v);
        }
    }
    scc(const graph& G) : n(G.size()), G(G), cnt(0), num(n), low(n), in(n) {
        rep(i, n) if (num[i] == 0) dfs(i);
    }
};
