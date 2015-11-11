// verified: http://www.spoj.com/problems/{SARRAY,SUBLEX}/
int n, k;
vector<int> rnk, tmp, sa, lcp;
bool compare_sa(int i, int j) {
    if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
    else {
        int ri = i+k <= n ? rnk[i+k] : -1;
        int rj = j+k <= n ? rnk[j+k] : -1;
        return ri < rj;
    }
}
void construct_sa(const string &s) {
    n = s.size();
    rnk.assign(n+1, 0);
    tmp.assign(n+1, 0);
    sa.assign(n+1, 0);
    lcp.assign(n+1, 0);
    rep(i,n+1) {
        sa[i] = i;
        rnk[i] = i < n ? s[i] : -1;
    }
    for (k = 1; k <= n; k *= 2) {
        sort(sa.begin(), sa.end(), compare_sa);
        tmp[sa[0]] = 0;
        repi(i,1,n+1) tmp[sa[i]] = tmp[sa[i-1]] + (compare_sa(sa[i-1], sa[i]) ? 1 : 0);
        rep(i,n+1) rnk[i] = tmp[i];
    }
}
void construct_lcp(const string &s) {
    rep(i,n+1) rnk[sa[i]] = i;
    int h = lcp[0] = 0;
    rep(i,n) {
        int j = sa[rnk[i] - 1];
        if (h > 0) h--;
        for (; j+h < n and i+h < n; h++) {
            if (s[j+h] != s[i+h]) break;
        }
        lcp[rnk[i] - 1] = h;
    }
}
