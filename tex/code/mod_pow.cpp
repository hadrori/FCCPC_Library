int pow_mod(int x, int k, int m) {
    int ret = 1;
    for(x%=m; k>0; x=1LL*x*x%m,k>>=1) if(k&1) ret = 1LL*ret*x%m;
    return ret;
}
