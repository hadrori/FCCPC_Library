struct uedge {
    int u, v; long w;
    uedge(int u, int v, long w) : u(u), v(v), w(w) {}
    bool operator <(const uedge& t) const { return w < t.w; }
    bool operator >(const uedge& t) const { return w > t.w; }
};
graph kruskal(const graph& G) {
    const int n = G.size();
    vector<uedge> E;
    rep(i, n) for (const auto& e : G[i]) {
        if (i < e.to) E.eb(i, e.to, e.w);
    }
    sort(all(E));
    graph T(n);
    disjoint_set uf(n);
    for (const auto& e : E) {
        if (not uf.same(e.u, e.v)) {
            T[e.u].eb(e.v, e.w);
            T[e.v].eb(e.u, e.w);
            uf.merge(e.u, e.v);
        }
    }
    return T;
}
graph prim(const vector<vector<long> >& A, int s = 0) {
    const int n = A.size();
    graph T(n);
    vector<int> done(n);
    priority_queue<uedge, vector<uedge>, greater<uedge> > q;
    q.emplace(-1, s, 0);
    while (not q.empty()) {
        const auto e = q.top(); q.pop();
        if (done[e.v]) continue;
        done[e.v] = 1;
        if (e.u >= 0) {
            T[e.u].eb(e.v, e.w);
            T[e.v].eb(e.u, e.w);
        }
        rep(i, n) if (not done[i]) {
            q.emplace(e.v, i, A[e.v][i]);
        }
    }
    return T;
}
