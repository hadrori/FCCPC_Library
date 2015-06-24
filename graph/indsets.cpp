typedef vector<vector<int>> graph;
class maximal_indsets {
    const int n;
    const graph& G;
    vector<vector<int>> ret;
    vector<int> cur, exists, deg, block;
    void erase(int v) {
        if (exists[v]) {
            exists[v] = false;
            for (int nv : G[v]) --deg[nv];
        }
    }
    void restore(int v) {
        exists[v] = true;
        for (int nv : G[v]) ++deg[nv];
    }
    void select(int v) {
        cur.push_back(v);
        ++block[v], erase(v);
        for (int nv : G[v]) ++block[nv], erase(nv);
    }
    void unselect(int v) {
        cur.pop_back();
        --block[v], restore(v);
        for (int nv : G[v]) {
            if (--block[nv] == 0) restore(nv);
        }
    }
    void dfs() {
        int mn = n, v = -1;
        rep(u, n) if (exists[u]) {
            if (deg[u] < mn) mn = deg[u], v = u;
        }
        if (v == -1) {
            ret.push_back(cur);
        } else {
            select(v), dfs(), unselect(v);
            for (int nv : G[v]) {
                if (exists[nv]) select(nv), dfs(), unselect(nv);
            }
        }
    }
public:
    maximal_indsets(const graph& G) : n(G.size()), G(G), exists(n, true), deg(n), block(n) {
        rep(v, n) deg[v] = G[v].size();
        dfs();
    }
    const vector<vector<int>>& get() const { return ret; }
};
