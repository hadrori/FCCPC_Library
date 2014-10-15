#include "macro.cpp"

struct edge {
    int to; long w;
    edge(int to, long w) : to(to), w(w) {}
};
typedef vector<vector<edge> > graph;

graph rev(const graph& G) {
    const int n = G.size();
    graph ret(n);
    rep(i, n) for (const auto& e : G[i]) {
        ret[e.to].eb(i, e.w);
    }
    return ret;
}
