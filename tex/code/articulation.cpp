typedef vector<vector<int> > graph;

class articulation {
    const int n;
    graph G;
    int cnt;
    vector<int> num, low, art;
    void dfs(int v) {
        num[v] = low[v] = ++cnt;
        for (int nv : G[v]) {
            if (num[nv] == 0) {
                dfs(nv);
                low[v] = min(low[v], low[nv]);
                if ((num[v] == 1 and num[nv] != 2) or
                    (num[v] != 1 and low[nv] >= num[v])) {
                    art[v] = true;
                }
            } else {
                low[v] = min(low[v], num[nv]);
            }
        }
    }
public:
    articulation(const graph& G) : n(G.size()), G(G), cnt(0), num(n), low(n), art(n) {
        rep(i, n) if (num[i] == 0) dfs(i);
    }
    vector<int> get() {
        return art;
    }
};
