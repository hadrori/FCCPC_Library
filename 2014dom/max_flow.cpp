#include <queue>
#include <vector>

using namespace std;

#define rep(i,n) repi(i,0,n)
#define repi(i,a,b) for(int i=int(a);i<int(b);++i)

const int inf = 1e9;

struct edge { int to, cap, rev; };
typedef vector<vector<edge> > graph;

graph G;

void add_edge(int from, int to, int cap)
{
    G[from].push_back((edge) {to, cap, (int) G[to].size()});
    G[to].push_back((edge) {from, 0, (int) G[from].size() - 1});
}

vector<int> level, iter;

void bfs(int s)
{
    level.assign(G.size(), -1);
    queue<int> q;
    level[s] = 0; q.push(s);
    while (not q.empty()) {
        int v = q.front(); q.pop();
        rep(i, G[v].size()) {
            edge& e = G[v][i];
            if (e.cap > 0 and level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

int dfs(int v, int t, int f)
{
    if (v == t) return f;
    for (int& i = iter[v]; i < (int) G[v].size(); ++i) {
        edge& e = G[v][i];
        if (e.cap > 0 and level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t)
{
    int ret = 0;
    while (bfs(s), level[t] >= 0) {
        iter.assign(G.size(), 0);
        int d;
        while ((d = dfs(s, t, inf)) > 0) {
            ret += d;
        }
    }
    return ret;
}

int main() {}
