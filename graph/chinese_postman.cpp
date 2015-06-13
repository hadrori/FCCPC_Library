long chinesePostman(const graph &g) {
    long total = 0;
    vector<int> odds;
    rep(u, g.size()) {
        for(auto &e: g[u]) total += e.w;
        if (g[u].size() % 2) odds.push_back(u);
    }
    total /= 2;
    int n = odds.size(), N = 1 << n;
    int w[n][n]; // make odd vertices graph
    rep(u,n) {
        int s = odds[u]; // dijkstra's shortest path
        vector<int> dist(g.size(), 1e9); dist[s] = 0;
        vector<int> prev(g.size(), -2);
        priority_queue<edge> Q;
        Q.push( edge(-1, s, 0) );
        while (!Q.empty()) {
            edge e = Q.top(); Q.pop();
            if (prev[e.to] != -2) continue;
            prev[e.to] = e.src;
            for(auto &f: g[e.to]) {
                if (dist[f->to] > e.w+f->w) {
                    dist[f->to] = e.w+f->w;
                    Q.push(edge(f->src, f->to, e.w+f->w));
                }
            }
        }
        rep(v,n) w[u][v] = dist[odds[v]];
    }
    long best[N]; // DP for general matching 
    rep(S,N) best[S] = INF;
    best[0] = 0;

    for (int S = 0; S < N; ++S)
        for (int i = 0; i < n; ++i)
            if (!(S&(1<<i)))
                for (int j = i+1; j < n; ++j)
                    if (!(S&(1<<j)))
                        best[S|(1<<i)|(1<<j)] = min(best[S|(1<<i)|(1<<j)], best[S]+w[i][j]);
    return total + best[N-1];
}
