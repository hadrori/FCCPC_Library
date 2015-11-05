template <class T>
class meldable_heap {
    struct node {
        node *l = NULL, *r = NULL;
        T val;
        node(const T& val) : val(val) {}
        ~node() { delete l, delete r; }
    };
    node *meld(node *a, node *b) {
        if (!a) return b;
        if (!b) return a;
        if (a->val > b->val) swap(a, b);
        a->r = meld(a->r, b);
        swap(a->l, a->r);
        return a;
    }
    node *root = NULL;
    meldable_heap(node *root) : root(root) {}
public:
    meldable_heap() {}
    bool empty() const { return !root; }
    const T& top() const { return root->val; }
    void meld(const meldable_heap<T>&& t) { root = meld(root, t.root); }
    void push(const T& val) { root = meld(root, new node(val)); }
    void pop() {
        node *t = root;
        root = meld(t->l, t->r);
        t.l = t.r = NULL;
        delete t;
    }
};
