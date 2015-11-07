namespace HLD {
const int N = 200010;
vector<vector<int>> chains, childs;
int V, dep[N], par[N], heavy[N], head[N], chain[N], id[N], size[N], q[N];

void calc_heavy() {
    int root = -1;
    childs.assign(V,vector<int>());
    for(int v = 0; v < V; v++) {
        size[v] = 0;
        heavy[v] = -1;
        if(par[v] < 0) root = v;
        else childs[par[v]].push_back(v);
    }
    int l = 0, r = 0;
    q[r++] = root;
    while(l < r) {
        int v = q[l++];
        for(auto &w: childs[v]) {
            if(w == par[v]) continue;
            dep[w] = dep[v]+1;
            q[r++] = w;
        }
    }
    reverse(q,q+V);
    for(int i = 1; i < V; i++) {
        int v = q[i], &u = par[v];
        size[u] += ++size[v];
        if(heavy[u] == -1 or size[v] > size[heavy[u]]) heavy[u] = v;
    }
}
void calc_chain() {
    chains.clear();
    int idx = 0;
    for (int v = 0; v < V; v++) {
        if(par[v] < 0 or heavy[par[v]] != v) {
            chains.push_back(vector<int>());
            for (int w = v; w != -1; w = heavy[w]) {
                chain[w] = idx;
                head[w] = v;
                id[w] = chains.back().size();
                chains.back().push_back(w);
            }
            idx++;
        }
    }
}
void make_par(const vector<vector<int>> &g, int root = 0) {
    memset(par,-1,sizeof(par));
    par[root] = 0;
    int l = 0, r = 0;
    q[r++] = root;
    while(l < r) {
        int v = q[l++];
        for(const int &w: g[v]) if(par[w] < 0) q[r++] = w, par[w] = v;
    }
    par[root] = -1;
}
void build(const vector<vector<int>> &g, int root = 0) {
    V = g.size();
    make_par(g,root);
    calc_heavy();
    calc_chain();
}
int lca(int u, int v) {
    while (chain[u] != chain[v]) {
        if (dep[head[u]] > dep[head[v]]) swap(u,v);
        v = par[head[v]];
    }
    return dep[u] < dep[v]? u: v;
}
}
