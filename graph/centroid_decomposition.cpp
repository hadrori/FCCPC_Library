const int N = 100010;
int level[N], par[N], done[N];
vector<int> bfs(int s) {
    vector<int> ret;
    queue<int> que;
    que.push(s), par[s] = -1;
    while (not que.empty()) {
        int v = que.front(); que.pop();
        ret.push_back(v);
        done[v] = true;
        for (int u : G[v]) {
            if (level[u] == 0 and not done[u]) {
                que.push(u), par[u] = v;
            }
        }
    }
    return ret;
}
int size[N], ch[N];
void update(int v) {
    size[v] = 1, ch[v] = 0;
    for (int u : G[v]) {
        if (u != par[v] and level[u] == 0) {
            size[v] += size[u];
            ch[v] = max(ch[v], size[u]);
        }
    }
}
void decompomposite() {
    auto ord = bfs(0);
    rep(i, 26) {
        fill_n(done, n, 0);
        for (int v : ord) {
            if (level[v] == 0 and not done[v]) {
                auto sub = bfs(v);
                reverse(all(sub));
                for (int u : sub) update(u);
                int whole = size[v], petal = ch[v];
                for (bool flag = true; flag; ) {
                    flag = false;
                    for (int c : G[v]) {
                        if (level[c] == 0) {
                            int tmp = max(ch[c], whole - size[c]);
                            if (petal > tmp) {
                                v = c, petal = tmp;
                                flag = true;
                                break;
                            }
                        }
                    }
                }
                // v is a centroid
                level[v] = i + 1;
            }
        }
    }
}
