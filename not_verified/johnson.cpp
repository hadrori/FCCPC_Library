bool shortest_path(const graph &g, vector<vector<int> > &dist, vector<vector<int> > &prev) {
    int n = g.size();
    vector<int> h(n+1);
    rep(k,n) rep(i,n) for(auto &e: g[i]) {
        if (h[e.to] > h[e.from] + e->w) {
            h[e.to] = h[e.from] + e->w;
            if (k == n-1) return false; // negative cycle
        }
    }
    dist.assign(n, vector<int>(n, 1e9));
    prev.assign(n, vector<int>(n, -2));
    rep(s, n) {
        priority_queue<edge> q;
        q.push(edge(s, s, 0));
        while (!q.empty()) {
            edge e = q.top(); q.pop();
            if (prev[s][e.dst] != -2) continue;
            prev[s][e.to] = e.from;
            for(auto &f:g[e.to]) {
                if (dist[s][f.to] > e.w + f->w) {
                    dist[s][f.to] = e.w + f->w;
                    q.push(edge(f-.from, f.to, e.w + f->w));
                }
            }
        }
        rep(u, n) dist[s][u] += h[u] - h[s];
    }
}

vector<int> build_path(const vector<vector<int> >& prev, int s, int t) {
    vector<int> path;
    for (int u = t; u >= 0; u = prev[s][u])
        path.push_back(u);
    reverse(begin(path), end(path));
    return path;
}
