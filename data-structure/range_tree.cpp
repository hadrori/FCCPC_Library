vector<pair<int,int> > ps;
struct node {
    int a, b;
    node *l, *r;
    vector<int> ys, bit;
    node(int a, int b) : a(a), b(b), l(NULL), r(NULL) {}
};
inline int leftmost(node *v) { return ps[v->a].first; }
inline int rightmost(node *v) { return ps[v->b - 1].first; }
node *construct(int a, int b) {
    if (a == b) return NULL;
    node *ret = new node(a, b);
    if (a == b-1) {
        ret->ys.push_back(ps[a].second);
        ret->bit.push_back(0);
    } else {
        int m = (a+b)/2;
        if ((ret->l = construct(a, m))) {
            ret->ys.insert(ret->ys.end(), all(ret->l->ys));
        }
        if ((ret->r = construct(m, b))) {
            ret->ys.insert(ret->ys.end(), all(ret->r->ys));
        }
        sort(all(ret->ys));
        ret->bit.resize(b-a);
    }
    return ret;
}
void insert(node *v, int x, int y) {
    if (!v) return;
    if (make_pair(x, y) < ps[v->a]) return;
    if (make_pair(x, y) > ps[v->b - 1]) return;
    int k = lower_bound(all(v->ys), y) - v->ys.begin();
    for (; k < (int)v->bit.size(); k |= k+1) {
        ++v->bit[k];
    }
    insert(v->l, x, y);
    insert(v->r, x, y);
}
int query(node *v, int x, int y) {
    if (!v or leftmost(v) > x) return 0;
    if (rightmost(v) <= x) {
        int ret = 0, k = upper_bound(all(v->ys), y) - v->ys.begin();
        for (; k; k &= k - 1) {
            ret += v->bit[k-1];
        }
        return ret;
    }
    return query(v->l, x, y) + query(v->r, x, y);
}
