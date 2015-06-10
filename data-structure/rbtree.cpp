template<class T> class rbtree {
    enum COL { BLACK, RED,};
    struct node {
        T val, lazy, min_val;
        int color, rnk, size;
        node *left, *right;
        // if !left then this node is leaf
        node(){}
        node(T v) : val(v), min_val(v), color(BLACK), rnk(0), size(1) {
            lazy = 0;
            left = right = NULL;
        }
        node(node *l, node *r, int c) : color(c) {
            lazy = 0;
            left = l;
            right = r;
            update();
        }
        void update() {
            eval();
            if(left) {
                rnk = max(left->rnk+(left->color==BLACK),
                          right->rnk+(right->color==BLACK));
                size = left->size+right->size;
                left->eval(); right->eval();
                min_val = min(left->min_val, right->min_val);
            }
        }
        void eval() {
            min_val += lazy;
            if(!left) val += lazy;
            else {
                left->lazy += lazy;
                right->lazy += lazy;
            }
            lazy = 0;
        }
    };
        
    node *new_node(T v) { return new node(v);}
    node *new_node(node *l, node *r, int c) { return new node(l,r,c);} 
    node *rotate(node *v, int d) {
        node *w = d? v->right: v->left;
        if(d) {
            v->right = w->left;
            w->left = v;
            v->right->update();
        }
        else {
            v->left = w->right;
            w->right = v;
            v->left->update();
        }
        v->update(); w->update();
        v->color = RED;
        w->color = BLACK;
        return w;
    }
    node *merge_sub(node *u, node *v) {
        u->eval(); v->eval();
        if(u->rnk < v->rnk) {
            node *w = merge_sub(u,v->left);
            v->left = w;
            v->update();
            if(v->color == BLACK and w->color == RED and w->left->color == RED) {
                if(v->right->color == BLACK)  return rotate(v,0);
                else {
                    v->color = RED;
                    v->left->color = v->right->color = BLACK;
                    return v;
                }
            }
            else return v;
        }
        else if(u->rnk > v->rnk) {
            node *w = merge_sub(u->right,v);
            u->right = w;
            u->update();
            if(u->color == BLACK and w->color == RED and w->right->color == RED) {
                if(u->left->color == BLACK) return rotate(u,1);
                else {
                    u->color = RED;
                    u->left->color = u->right->color = BLACK;
                    return u;
                }
            }
            else return u;
        }
        else return new_node(u,v,RED);
    }
    node *insert(node *v, int k) {
        auto p = split(root,k);
        return root = merge(merge(p.first,v),p.second);
    }
    void add(node *v, int res, T val) {
        if(res < 1) return;
        v->eval();
        if(v->size == res) {
            v->lazy += val;
            return;
        }
        add(v->left, min(v->left->size, res), val);
        add(v->right, res-v->left->size, val);
        v->update();
    }
    T get(node *v, int k) {
        v->eval();
        if(!v->left) return v->val;
        if(v->left->size > k) return get(v->left, k);
        return get(v->right, k-v->left->size);
    }
    T minimum(node *v, int l, int r) {
        if(r-l < 1) return inf;
        v->eval();
        if(v->size == r-l) return v->min_val;
        return min(minimum(v->left, l, min(r, v->left->size)),
                   minimum(v->right, l-min(l, v->left->size), r-v->left->size));
    }
    T inf;
public:
        
    node *root;
    rbtree() {
        inf = (((1LL<<(sizeof(T)*8-2))-1)<<1)+1;
        root = NULL;
    }
    void clear() { delete root; root = NULL;}
    node *build(const vector<T> &vs) {
        if(!vs.size()) return root = NULL;
        if((int)vs.size() == 1) return root = new_node(vs[0]);
        int m = vs.size()/2;
        return root = merge(build(vector<T>(begin(vs),begin(vs)+m)),
                            build(vector<T>(begin(vs)+m,end(vs))));
    }
    int size() { return root? root->size: 0;}
    node *push_back(T val) { return root = merge(root,new_node(val));}
    node *push_front(T val) { return root = merge(new_node(val),root);}
    node *merge(node *u, node *v) {
        if(!u) return v;
        if(!v) return u;
        u = merge_sub(u,v);
        u->color = BLACK;
        return u;
    }
    pair<node*,node*> split(node *v, int k) {
        if(!k) return pair<node*,node*>(NULL,v);
        if(k == v->size) return pair<node*,node*>(v,NULL);
        v->eval();
        if(k < v->left->size) {
            auto p = split(v->left,k);
            return pair<node*,node*>(p.first,merge(p.second,v->right));
        }
        else if(k > v->left->size) {
            auto p = split(v->right,k-v->left->size);
            return pair<node*,node*>(merge(v->left,p.first),p.second);
        }
        else return pair<node*,node*>(v->left,v->right);
    }
 
    node *insert(int k, T val) { return insert(new_node(val),k);}
    node *erase(int k) {
        auto p = split(root,k+1);
        return root = merge(split(p.first,k).first, p.second);
    }
    void add(int l, int r, T val) { add(root, r, val); add(root, l, -val);}
    T get(int k) { return get(root, k);}
    T minimum(int l, int r) { return minimum(root, l, r);}
    T operator[](const int &i) { return get(i);}
};
