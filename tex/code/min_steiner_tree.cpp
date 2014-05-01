int minimum_steiner_tree(vi &T, vvi &g){
    int n = g.size(), t = T.size();
    if(t <= 1) return 0;
    vvi d(g);    // all-pair shortest
    rep(k,n)rep(i,n)rep(j,n)    //Warshall Floyd
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    
    int opt[1 << t][n];
    rep(S,1<<t) rep(x,n)
        opt[S][x] = INF;

    rep(p,t) rep(q,n)   // trivial case
        opt[1 << p][q] = d[T[p]][q];

    repi(S,1,1<<t){   // DP step
        if(!(S & (S-1))) continue;
        rep(p,n) rep(E,S)
            if((E | S) == S)
                opt[S][p] = min(opt[S][p], opt[E][p] + opt[S-E][p]);
        rep(p,n) rep(q,n)
            opt[S][p] = min(opt[S][p], opt[S][q] + d[p][q]);
    }

    int ans = INF;
    rep(S,1<<t) rep(q,n)
        ans = min(ans, opt[S][q] + opt[((1<<t)-1)-S][q]);
    return ans;
}
