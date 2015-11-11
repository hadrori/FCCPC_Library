struct articulation {
    const int n; graph G;
    int cnt;
    vector<int> num, low, is_art;
    void dfs(int v) {
        num[v] = low[v] = ++cnt;
        for (int nv : G[v]) {
            if (num[nv] == 0) {
                dfs(nv);
                low[v] = min(low[v], low[nv]);
                if ((num[v] == 1 and num[nv] != 2) or
                    (num[v] != 1 and low[nv] >= num[v])) {
                    is_art[v] = true;
                }
            } else {
                low[v] = min(low[v], num[nv]);
            }
        }
    }
    articulation(const graph& G) : n(G.size()), G(G), cnt(0), num(n), low(n), is_art(n) {
        rep(i, n) if (num[i] == 0) dfs(i);
    }
};
