// ordered
struct node {
    vector<node*> child;
};
bool otreeIsomorphism(node *n, node *m) {
    if (n->child.size() != m->child.size()) return false;
    rep(i, n->child.size())
        if (!otreeIsomorphism(n->child[i], m->child[i])) return false;
    return true;
}

// not ordered
struct node {
    vector<node *> child;
    vector<int> code;
};
void code(node *n) {
    int size = 1;
    vector< pair<vector<int>, int> > codes;
    rep(i, n->child.size()) {
        code(n->child[i]);
        codes.push_back( make_pair(n->child[i]->code, i) );
        size += codes[i].first[0];
    }
    sort(codes.rbegin(), codes.rend()); // !reverse
    n->code.push_back(size);
    for (int i = 0; i < n->child.size(); ++i) {
        swap(n->child[i], n->child[ codes[i].second ]);
        n->code.insert(n->code.end(),
                       codes[i].first.begin(), codes[i].first.end());
    }
}
bool utreeIsomorphism(node *n, node *m) {
    code(n); code(m); return n->code == m->code;
}
  
