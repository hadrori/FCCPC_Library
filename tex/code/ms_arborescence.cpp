void visit(Graph &h, int v, int s, int r,
           vector<int> &no, vector< vector<int> > &comp,
           vector<int> &prev, vector< vector<int> > &next, vector<int> &mcost,
           vector<int> &mark, int &cost, bool &found) {
    const int n = h.size();
    if (mark[v]) {
        vector<int> temp = no;
        found = true;
        do {
            cost += mcost[v];
            v = prev[v];
            if (v != s) {
                while (comp[v].size() > 0) {
                    no[comp[v].back()] = s;
                    comp[s].push_back(comp[v].back());
                    comp[v].pop_back();
                }
            }
        } while (v != s);
        for(auto &j: comp[s]) if (j != r) for(auto &e: h[j])
            if (no[e.from] != s) e.w -= mcost[temp[j]];
    }
    mark[v] = true;
    for(auto &i: next[v]) if (no[i] != no[v] && prev[no[i]] == v)
        if (!mark[no[i]] || i == s)
            visit(h, i, s, r, no, comp, prev, next, mcost, mark, cost, found);
}
int minimum_spanning_arborescence(const graph &g, int r) {
    const int n = g.size();
    graph h(n);
    rep(u,n) for(auto &e: g[u]) h[e.to].push_back(e);

    vector<int> no(n);
    vector< vector<int> > comp(n);
    rep(u, n) comp[u].push_back(no[u] = u);

    for (int cost = 0; ;) {
        vector<int> prev(n, -1);
        vector<int> mcost(n, INF);

        rep(j,n) if (j != r) for(auto &e: g[j])
            if (no[e.from] != no[j])
                if (e.w < mcost[no[j]])
                    mcost[no[j]] = e.w, prev[no[j]] = no[e.from];

        vector< vector<int> > next(n);
        rep(u,n) if (prev[u] >= 0)
            next[prev[u]].push_back(u);

        bool stop = true;
        vector<int> mark(n);
        rep(u,n) if (u != r && !mark[u] && !comp[u].empty()) {
            bool found = false;
            visit(h, u, u, r, no, comp, prev, next, mcost, mark, cost, found);
            if (found) stop = false;
        }
        if (stop) {
            rep(u,n) if (prev[u] >= 0) cost += mcost[u];
            return cost;
        }
    }
}
