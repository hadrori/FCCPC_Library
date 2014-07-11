#include <queue>
#include <vector>

using namespace std;

#define rep(i,n) repi(i,0,n)
#define repi(i,a,b) for(int i=int(a);i<int(b);++i)

#define mp make_pair

const int inf = 1e9;

struct edge { int to, cap, cost, rev; };
typedef vector<vector<edge> > graph;

graph G;

void add_edge(int from, int to, int cap, int cost)
{
    G[from].push_back((edge) {to, cap, cost, (int) G[to].size()});
    G[to].push_back((edge) {from, 0, -cost, (int) G[from].size() - 1});
}

int min_cost_flow(int s, int t, int f)
{
    typedef pair<int, int> pii;

    const int n = G.size();
    vector<int> h, dist, prev, prev_e;

    int ret = 0;
    h.assign(n, 0);
    while (f > 0) {
        priority_queue<pii, vector<pii>, greater<pii> > q;
        dist.assign(n, inf);
        dist[s] = 0; q.push(mp(0, s));
        while (not q.empty()) {
            int d = q.top().first;
            int v = q.top().second;
            q.pop();
            if (dist[v] < d) continue;
            rep(i, G[v].size()) {
                edge& e = G[v][i];
                if (e.cap > 0 and dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prev[e.to] = v;
                    prev_e[e.to] = i;
                    q.push(mp(dist[e.to], e.to));
                }
            }
        }
        if (dist[t] == inf) return -1;
        rep(i, n) h[i] += dist[i];

        int d = f;
        for (int v = t; v != s; v = prev[v]) {
            d = min(d, G[prev[v]][prev_e[v]].cap);
        }
        f -= d;
        ret += d * h[t];
        for (int v = t; v != s; v = prev[v]) {
            edge& e = G[prev[v]][prev_e[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return ret;
}

int main() {}
