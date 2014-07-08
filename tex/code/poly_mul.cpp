vector<int> poly_mul(vector<int> f, vector<int> g){
    int N = max(f.size(),g.size())*2;
    f.resize(N); g.resize(N);
    f = fmt(f,0); g = fmt(g,0);
    rep(i,N) f[i] = 1LL*f[i]*g[i]%mod;
    f = fmt(f,1);
    return f;
}
