bool shortest_path(const graph &g, Matrix &dist, vector<vector<int> > &prev) {
    int n = g.size();
    Array h(n+1);
    REP(k,n) REP(i,n) FOR(e,g[i]) {
        if (h[e->dst] > h[e->src] + e->weight) {
            h[e->dst] = h[e->src] + e->weight;
            if (k == n-1) return false; // negative cycle
        }
    }
    dist.assign(n, Array(n, INF));
    prev.assign(n, vector<int>(n, -2));
    REP(s, n) {
        priority_queue<Edge> Q;
        Q.push(Edge(s, s, 0));
        while (!Q.empty()) {
            Edge e = Q.top(); Q.pop();
            if (prev[s][e.dst] != -2) continue;
            prev[s][e.dst] = e.src;
            FOR(f,g[e.dst]) {
                if (dist[s][f->dst] > e.weight + f->weight) {
                    dist[s][f->dst] = e.weight + f->weight;
                    Q.push(Edge(f->src, f->dst, e.weight + f->weight));
                }
            }
        }
        REP(u, n) dist[s][u] += h[u] - h[s];
    }
}

vector<int> buildPath(const vector< vector<int> >& prev, int s, int t) {
    vector<int> path;
    for (int u = t; u >= 0; u = prev[s][u])
        path.push_back(u);
    reverse(ALL(path));
    return path;
}
