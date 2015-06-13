const int inf = 1e9;
struct edge {
    int to, cap, rev;
    edge(int to, int cap, int rev) : to(to), cap(cap), rev(rev) {}
};
typedef vector<vector<edge> > graph;

void add_edge(graph& G, int from, int to, int cap) {
    G[from].eb(to, cap, G[to].size());
    G[to].eb(from, 0, G[from].size() - 1);
}

class max_flow {
    const int n;
    graph& G;
    vector<int> level, iter;
    void bfs(int s, int t) {
        level.assign(n, -1);
        queue<int> q;
        level[s] = 0, q.push(s);
        while (not q.empty()) {
            const int v = q.front();
            q.pop();
            if (v == t) return;
            for (const auto& e : G[v]) {
                if (e.cap > 0 and level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int& i = iter[v]; i < (int) G[v].size(); ++i) {
            edge& e = G[v][i];
            if (e.cap > 0 and level[v] < level[e.to]) {
                const int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d, G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
public:
    max_flow(graph& G) : n(G.size()), G(G) {}
    int calc(int s, int t) {
        int ret = 0, d;
        while (bfs(s, t), level[t] >= 0) {
            iter.assign(n, 0);
            while ((d = dfs(s, t, inf)) > 0) ret += d;
        }
        return ret;
    }
};
