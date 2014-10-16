const int inf = 1e9;
struct edge {
    int to, cap, cost, rev;
    edge(int to, int cap, int cost, int rev) : to(to), cap(cap), cost(cost), rev(rev) {}
};
typedef vector<vector<edge> > graph;

void add_edge(graph& G, int from, int to, int cap, int cost) {
    G[from].eb(to, cap, cost, G[to].size());
    G[to].eb(from, 0, -cost, G[from].size() - 1);
}

int min_cost_flow(graph& G, int s, int t, int f) {
    const int n = G.size();
    struct state {
        int v, d;
        state(int v, int d) : v(v), d(d) {}
        bool operator <(const state& t) const { return d > t.d; }
    };

    int ret = 0;
    vector<int> h(n, 0), dist, prev(n), prev_e(n);
    while (f > 0) {
        dist.assign(n, inf);
        priority_queue<state> q;
        dist[s] = 0, q.emplace(s, 0);
        while (not q.empty()) {
            const int v = q.top().v;
            const int d = q.top().d;
            q.pop();
            if (dist[v] <= d) continue;
            rep(i, G[v].size()) {
                const edge& e = G[v][i];
                if (e.cap > 0 and dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prev[e.to] = v, prev_e[e.to] = i;
                    q.emplace(e.to, dist[e.to]);
                }
            }
        }
        if (dist[t] == inf) return -1;
        rep(i, n) h[i] += dist[i];

        int d = f;
        for (int v = t; v != s; v = prev[v]) {
            d = min(d, G[prev[v]][prev_e[v]].cap);
        }
        f -= d, ret += d * h[t];
        for (int v = t; v != s; v = prev[v]) {
            edge& e = G[prev[v]][prev_e[v]];
            e.cap -= d, G[v][e.rev].cap += d;
        }
    }
    return ret;
}
