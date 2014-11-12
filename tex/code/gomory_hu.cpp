#define RESIDUE(s,t) (capacity[s][t]-flow[s][t])
graph cutTree(const graph &g) {
    int n = g.size();
    Matrix capacity(n, Array(n)), flow(n, Array(n));
    rep(u,n) for(auto &e: g[u]) capacity[e.from][e.to] += e.w;

    vector<int> p(n), prev;
    vector<int> w(n);
    for (int s = 1; s < n; ++s) {
        int t = p[s]; // max-flow(s, t)
        rep(i,n) rep(j,n) flow[i][j] = 0;
        int total = 0;
        while (1) {
            queue<int> Q; Q.push(s);
            prev.assign(n, -1); prev[s] = s;
            while (!Q.empty() && prev[t] < 0) {
                int u = Q.front(); Q.pop();
                for(auto &e: g[u]) if (prev[e.to] < 0 && RESIDUE(u, e.to) > 0) {
                    prev[e.to] = u;
                    Q.push(e.to);
                }
            }
            if (prev[t] < 0) goto esc;
            int inc = 1e9;
            for (int j = t; prev[j] != j; j = prev[j])
                inc = min(inc, RESIDUE(prev[j], j));
            for (int j = t; prev[j] != j; j = prev[j])
                flow[prev[j]][j] += inc, flow[j][prev[j]] -= inc;
            total += inc;
        }
    esc:w[s] = total; // make tree
        rep(u, n) if (u != s && prev[u] != -1 && p[u] == t)
            p[u] = s;
        if (prev[p[t]] != -1)
            p[s] = p[t], p[t] = s, w[s] = w[t], w[t] = total;
    }
    graph T(n); // (s, p[s]) is a tree edge of weight w[s]
    rep(s, n) if (s != p[s]) {
        T[  s ].push_back( Edge(s, p[s], w[s]) );
        T[p[s]].push_back( Edge(p[s], s, w[s]) );
    }
    return T;
}

// Gomory-Hu tree を用いた最大流 O(n)
int max_flow(const graph &T, int u, int t, int p = -1, int w = 1e9) {
    if (u == t) return w;
    int d = 1e9;
    for(auto &e: T[u]) if (e.to != p)
        d = min(d, max_flow(T, e.to, t, u, min(w, e.w)));
    return d;
}
