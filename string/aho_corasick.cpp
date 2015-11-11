const int C = 128;
struct pma_node {
    pma_node *next[C]; // use next[0] as failure link
    vector<int> match;
    pma_node() { fill(next, next + C, (pma_node *) NULL); }
    ~pma_node() { rep(i, C) if (next[i] != NULL) delete next[i]; }
};
pma_node *construct_pma(const vector<string>& pat) {
    pma_node *const root = new pma_node();
    root->next[0] = root;
    // construct trie
    rep(i, pat.size()) {
        const string& s = pat[i];
        pma_node *now = root;
        for (const char c : s) {
            if (now->next[int(c)] == NULL) now->next[int(c)] = new pma_node();
            now = now->next[int(c)];
        }
        now->match.pb(i);
    }
    // make failure links with BFS
    queue<pma_node *> q;
    repi(i, 1, C) {
        if (root->next[i] == NULL) root->next[i] = root;
        else {
            root->next[i]->next[0] = root;
            q.push(root->next[i]);
        }
    }
    while (not q.empty()) {
        auto now = q.front();
        q.pop();
        repi(i, 1, C) if (now->next[i] != NULL) {
            auto next = now->next[0];
            while (next->next[i] == NULL) next = next->next[0];
            now->next[i]->next[0] = next->next[i];
            vector<int> tmp;
            set_union(all(now->next[i]->match), all(next->next[i]->match), back_inserter(tmp));
            now->next[i]->match = tmp;
            q.push(now->next[i]);
        }
    }
    return root;
}
void match(pma_node*& now, const string s, vector<int>& ret) {
    for (const char c : s) {
        while (now->next[int(c)] == NULL) now = now->next[0];
        now = now->next[int(c)];
        for (const int e : now->match) ret[e] = true;
    }
}
