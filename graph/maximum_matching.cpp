#define rep(i,n) repi(i,0,n)
#define repi(i,a,b) for(int i=(int)(a);i<(int)(b);++i)

#define even(x) (mu[x] == x or phi[mu[x]] != mu[x])
#define out(x) (mu[x] != x and phi[mu[x]] == mu[x] and phi[x] == x)
int maximum_matching(const vector<vector<int>>& G, vector<pair<int,int>>& ret) {
    const int n = G.size();
    vector<int> mu(n), phi(n), rho(n), done(n);
    rep(v, n) mu[v] = phi[v] = rho[v] = v;
    for (int x = -1; ; ) {
        if (x < 0) {
            for (x = 0; x < n and (done[x] or !even(x)); ++x);
            if (x == n) break;
        }
        int y = -1;
        for (int v : G[x]) if (out(v) or (even(v) and rho[v] != rho[x])) y = v;
        if (y == -1) {
            done[x] = true, x = -1;
        } else if (out(y)) {
            phi[y] = x;
        } else {
            vector<int> dx(n, -2), dy(n, -2); // x % 2 --> x >= 0
            for (int k = 0, w = x; dx[w] < 0; w = k % 2 ? mu[w] : phi[w]) dx[w] = k++;
            for (int k = 0, w = y; dy[w] < 0; w = k % 2 ? mu[w] : phi[w]) dy[w] = k++;
            bool disjoint = true;
            rep(v, n) if (dx[v] >= 0 and dy[v] > 0) disjoint = false;
            if (disjoint) {
                rep(v, n) if (dx[v] % 2) mu[phi[v]] = v, mu[v] = phi[v];
                rep(v, n) if (dy[v] % 2) mu[phi[v]] = v, mu[v] = phi[v];
                mu[x] = y; mu[y] = x; x = -1;
                rep(v, n) phi[v] = rho[v] = v, done[v] = false;
            } else {
                int r = x, d = n;
                rep(v, n) if (dx[v] >= 0 and dy[v] >= 0 and rho[v] == v and d > dx[v]) d = dx[v], r = v;
                rep(v, n) if (dx[v] <= d and dx[v] % 2 and rho[phi[v]] != r) phi[phi[v]] = v;
                rep(v, n) if (dy[v] <= d and dy[v] % 2 and rho[phi[v]] != r) phi[phi[v]] = v;
                if (rho[x] != r) phi[x] = y;
                if (rho[y] != r) phi[y] = x;
                rep(v, n) if (dx[rho[v]] >= 0 or dy[rho[v]] >= 0) rho[v] = r;
            }
        }
    }
    ret.clear();
    rep(v, n) if (v < mu[v]) ret.emplace_back(v, mu[v]);
    return ret.size();
}
