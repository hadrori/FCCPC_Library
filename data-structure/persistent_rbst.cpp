template <class T, size_t N>
struct mempool {
    static T buf[N], *head;
    static size_t cnt() { return head - buf; }
    static void clear() { head = buf; }
    void *operator new(size_t _ __attribute__((unused))) { return head++; }
    void operator delete(void *_ __attribute__((unused))) {}
};
template <class T, size_t N> T  mempool<T, N>::buf[N];
template <class T, size_t N> T *mempool<T, N>::head = mempool<T, N>::buf;

struct node;
long sum(node *u);
size_t size(node *u);
struct node : mempool<node, M> {
    const long val = 0, sum = 0, lazy = 0;
    const size_t size = 1;
    node *const left = NULL, *const right = NULL;
    node() {}
    node(long val) : val(val), sum(val) {}
    node(long val, long lazy, node *left, node *right)
        : val(val),
          sum(val + ::sum(left) + ::sum(right)),
          lazy(lazy),
          size(1 + ::size(left) + ::size(right)),
          left(left),
          right(right) {}
};
inline long sum(node *u) { return u ? u->sum + u->lazy * u->size : 0; }
inline size_t size(node *u) { return u ? u->size : 0; }
inline node *add(node *u, long x) { return u ? new node(u->val, u->lazy + x, u->left, u->right) : NULL; }
node *merge(node *u, node *v) {
    if (!u) return v;
    if (!v) return u;
    if (rand() * long(size(u) + size(v)) < long(size(u)) * RAND_MAX) {
        return new node(u->val + u->lazy, 0, add(u->left, u->lazy), merge(add(u->right, u->lazy), v));
    } else {
        return new node(v->val + v->lazy, 0, merge(u, add(v->left, v->lazy)), add(v->right, v->lazy));
    }
}
pair<node *, node *> split(node *u, size_t k) {
    if (!u or k == 0) return {NULL, u};
    if (k == size(u)) return {u, NULL};
    if (size(u->left) >= k) {
        auto p = split(add(u->left, u->lazy), k);
        return {p.first, new node(u->val + u->lazy, 0, p.second, add(u->right, u->lazy))};
    } else {
        auto p = split(add(u->right, u->lazy), k - size(u->left) - 1);
        return {new node(u->val + u->lazy, 0, add(u->left, u->lazy), p.first), p.second};
    }
}
template <class OutputIterator>
OutputIterator dump(OutputIterator it, const node *u, long lazy = 0) {
    if (!u) return it;
    lazy += u->lazy;
    it = dump(it, u->left, lazy);
    *it++ = u->val + lazy;
    return dump(it, u->right, lazy);
}
template <class ForwardIterator>
node *construct_from(ForwardIterator first, ForwardIterator last) {
    if (first == last) return NULL;
    auto mid = next(first, (last - first) / 2);
    return new node(*mid, 0, construct_from(first, mid), construct_from(next(mid), last));
}
