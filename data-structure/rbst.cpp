struct node {
    long val, sum;
    size_t size = 1;
    node *left = NULL, *right = NULL;
    node(long val) : val(val), sum(val) {}
    ~node() { delete left, delete right; }
};
inline long sum(node *u) { return u ? u->sum : 0; }
inline size_t size(node *u) { return u ? u->size : 0; }
inline node *pull(node *u) {
    u->sum = u->val + sum(u->left) + sum(u->right);
    u->size = 1 + size(u->left) + size(u->right);
    return u;
}
node *merge(node *u, node *v) {
    if (!u) return v;
    if (!v) return u;
    if (rand() * long(size(u) + size(v)) < long(size(u)) * RAND_MAX) {
        u->right = merge(u->right, v);
        return pull(u);
    } else {
        v->left = merge(u, v->left);
        return pull(v);
    }
}
pair<node*,node*> split(node *u, size_t k) {
    if (!u or k == 0) return {NULL, u};
    if (k == size(u)) return {u, NULL};
    if (size(u->left) >= k) {
        auto p = split(u->left, k);
        u->left = p.second;
        return {p.first, pull(u)};
    } else {
        auto p = split(u->right, k - size(u->left) - 1);
        u->right = p.first;
        return {pull(u), p.second};
    }
}
template <class ForwardIterator>
node *construct_from(ForwardIterator first, ForwardIterator last) {
    if (first == last) return NULL;
    auto mid = next(first, (last - first) / 2);
    node *u = new node(*mid);
    u->left  = construct_from(first, mid);
    u->right = construct_from(next(mid), last);
    return pull(u);
}
