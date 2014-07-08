const int MAX_V=16;
const int mod = 10009;
int N[MAX_V], I[1<<MAX_V], V;
inline int mpow(int a, int k){ return k==0? 1: k%2? a*mpow(a,k-1)%mod: mpow(a*a%mod,k/2);}

bool can(int k){
    int res = 0;
    rep(S, 1<<V){
        if(__builtin_popcountll(S)%2) res -= mpow(I[S], k);
        else res += mpow(I[S],k);
    }
    return (res%mod+mod)%mod;
}

int color_number(){
    memset(I, 0, sizeof(I));
    I[0] = 1;
    repi(S,1,1<<V){
        int v = 0;
        while(!(S&(1<<v))) v++;
        I[S] = I[S-(1<<v)] + I[S&(~N[v])];
    }
    int lb = 0, ub = V, mid;
    while(ub-lb>1){
        mid = (lb+ub)/2;
        if(can(mid)) ub = mid;
        else lb = mid;
    }
    return ub;
}
