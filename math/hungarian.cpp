int hungarian(const vector<vector<int>> &a) {
    int n = a.size(), p, q;
    vector<int> fx(n, inf), fy(n, 0), x(n, -1), y(n, -1);
    rep(i,n) rep(j,n) fx[i] = max(fx[i], a[i][j]);

    for (int i = 0; i < n; ) {
        vector<int> t(n, -1), s(n+1, i);
        for (p = q = 0; p <= q && x[i] < 0; ++p)
            for (int k = s[p], j = 0; j < n && x[i] < 0; ++j)
                if (fx[k] + fy[j] == a[k][j] && t[j] < 0) {
                    s[++q] = y[j], t[j] = k;
                    if (s[q] < 0)
                        for (p = j; p >= 0; j = p)
                            y[j] = k = t[j], p = x[k], x[k] = j;
                }
        if (x[i] < 0) {
            int d = inf;
            rep(k,q+1) rep(j,n) if (t[j] < 0) d = min(d, fx[s[k]] + fy[j] - a[s[k]][j]);
            rep(j,n) fy[j] += (t[j] < 0 ? 0 : d);
            rep(k,q+1) fx[s[k]] -= d;
        } else i++;
    }
    int ret = 0;
    rep(i,n) ret += a[i][x[i]];
    return ret;
}
