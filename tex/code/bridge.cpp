typedef vector<vector<int> > graph;

class bridge {
    const int n;
    graph G;
    int cnt;
    vector<int> num, low, in;
    stack<int> stk;
    vector<pair<int, int> > brid;
    vector<vector<int> > comp;
    void dfs(int v, int p) {
        num[v] = low[v] = ++cnt;
        stk.push(v), in[v] = true;
        for (const int nv : G[v]) {
            if (num[nv] == 0) {
                dfs(nv, v);
                low[v] = min(low[v], low[nv]);
            } else if (nv != p and in[nv]) {
                low[v] = min(low[v], num[nv]);
            }
        }
        if (low[v] == num[v]) {
            if (p != n) brid.eb(min(v, p), max(v, p));
            comp.eb();
            int w;
            do {
                w = stk.top();
                stk.pop(), in[w] = false;
                comp.back().pb(w);
            } while (w != v);
        }
    }
public:
    bridge(const graph& G) : n(G.size()), G(G), cnt(0), num(n), low(n), in(n) {
        rep(i, n) if (num[i] == 0) dfs(i, n);
    }
    vector<pair<int, int> > get() {
        return brid;
    }
    vector<vector<int> > components() {
        return comp;
    }
};
