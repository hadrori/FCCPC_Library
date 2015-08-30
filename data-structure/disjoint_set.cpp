class disjoint_set {
    vector<int> p;
public:
    disjoint_set(int n) : p(n, -1) {}
    int root(int i) { return p[i] >= 0 ? p[i] = root(p[i]) : i; }
    bool same(int i, int j) { return root(i) == root(j); }
    int size(int i) { return -p[root(i)]; }
    void merge(int i, int j) {
        i = root(i), j = root(j);
        if (i == j) return;
        if (p[i] > p[j]) swap(i, j);
        p[i] += p[j], p[j] = i;
    }
};
