#include "macro.cpp"

template<class T> class rbtree
{
public:
        enum COL { BLACK, RED,};
        struct node
        {
                T val;
                int color;
                int rnk, size;
                node *left, *right;

                node(){}
                node(T v) : val(v), color(BLACK), rnk(0), size(1)
                {
                        left = right = NULL;
                }
                node(node *l, node *r, int c) : color(c)
                {
                        left = l;
                        right = r;
                        update();
                }
                void update()
                {
                        rnk = max((left? left->rnk+(left->color==BLACK): 0),(right? right->rnk+(right->color==BLACK): 0));
                        size = (left? left->size: 0)+(right? right->size: 0)+(!left and !right);
                }
        };

        node *root;

        rbtree()
        {
                root = NULL;
        }

        rbtree(T val)
        {
                root = new_node(val);
        }

        node *new_node(T v) { return new node(v);}
        node *new_node(node *l, node *r, int c) { return new node(l,r,c);}

        node *build(const vector<T> &vs)
        {
                if(!vs.size()) return NULL;
                if((int)vs.size() == 1) return new_node(vs[0]);
                int m = vs.size()/2;
                return merge(build(vector<T>(begin(vs),begin(vs)+m)), build(vector<T>(begin(vs)+m,end(vs))));
        }

        int size() { return root->size;}
        void clear()
        {
                root = NULL;
        }

        void get(vector<T> &vs) { get(root,vs);}
        void get(node *v, vector<T> &vs)
        {
                if(!v->left and !v->right) vs.push_back(v->val);
                else {
                        if(v->left) get(v->left,vs);
                        if(v->right) get(v->right,vs);
                }
        }

        node *add(T val)
        {
                node *v = new_node(val);
                return root = merge(root,v);
        }

        node *right_rotate(node *v)
        {
                node *w = v->left;
                v->left = w->right;
                w->right = v;
                v->left->update();
                v->update();
                w->right->update();
                v->color = RED;
                w->color = BLACK;
                return w;
        }

        node *left_rotate(node *v)
        {
                node *w = v->right;
                v->right = w->left;
                w->left = v;
                v->right->update();
                v->update();
                w->left->update();
                v->color = RED;
                w->color = BLACK;
                return w;
        }

        node *merge(node *u, node *v)
        {
                if(!u) return v;
                if(!v) return u;
                u = merge_sub(u,v);
                u->color = BLACK;
                return u;
        }

        node *merge_sub(node *u, node *v)
        {
                if(u->rnk < v->rnk) {
                        node *w = merge_sub(u,v->left);
                        v->left = w;
                        v->update();
                        if(v->color == BLACK and w->color == RED and w->left->color == RED) {
                                if(v->right->color == BLACK)  return right_rotate(v);
                                else {
                                        v->color = RED;
                                        v->right->color = BLACK;
                                        w->color = BLACK;
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
                                if(u->left->color == BLACK) return left_rotate(u);
                                else {
                                        u->color = RED;
                                        u->left->color = BLACK;
                                        w->color = BLACK;
                                        return u;
                                }
                        }
                        else return u;
                }
                else return new_node(u,v,RED);
        }

        pair<node*,node*> split(node *v, int k)
        {
                if(!k) return pair<node*,node*>(NULL,v);
                if(k == v->size) return pair<node*,node*>(v,NULL);
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

        // insert val at k
        node *insert(T val, int k)
        {
                return insert(new_node(val),k);
        }
        // insert tree v at k
        node *insert(node *v, int k)
        {
                auto p = split(root,k);
                return root = merge(merge(p.first,v),p.second);
        }

        // delete at k
        node *erase(int k)
        {
                auto p = split(root,k+1);
                return root = merge(split(p.first,k).first, p.second);
        }
};
