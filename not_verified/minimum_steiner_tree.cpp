/*
   from Spaghetti Source
    O(4^t n)
    t = 11 が限界
    tはTの大きさ
    verified (AOJ 1040)
    Dreyfus-Wagner法
    g:隣接行列．無向性（対称性）を仮定する．つながっていない場合は INF
    T:部分頂点集合．同じものが複数入っていても平気．
    ans:シュタイナー木の重み
*/

typedef vector<int> Array;
typedef vector<Array> Matrix;

int minimum_steiner_tree(vector<int>& T, Matrix &g){
    int n = g.size(), t = T.size();
    if(t <= 1) return 0;
    Matrix d(g);    // all-pair shortest

    rep(k,n)rep(i,n)rep(j,n)    //Warshall Floyd
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

    int OPT[1 << t][n];
    rep(S,1<<t) rep(x,n)
        OPT[S][x] = INF;

    rep(p,t) rep(q,n)   // trivial case
        OPT[1 << p][q] = d[T[p]][q];

    repi(S,1,1<<t){   // DP step
        if(!(S & (S-1))) continue;
        rep(p,n) rep(E,S)
            if((E | S) == S)
                OPT[S][p] = min(OPT[S][p], OPT[E][p] + OPT[S-E][p]);
        rep(p,n) rep(q,n)
            OPT[S][p] = min(OPT[S][p], OPT[S][q] + d[p][q]);
    }

    int ans = INF;
    rep(S,1<<t) rep(q,n)
        ans = min(ans, OPT[S][q] + OPT[((1 << t) - 1) - S][q]);
    return ans;
}
