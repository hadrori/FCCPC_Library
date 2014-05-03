ll fact[MAX];
void gen_fact(ll m){
    fact[0] = 1;
    repi(i,1,m) fact[i] = fact[i-1] * i % m;
}
ll mod_fact(ll n, ll m, ll& e){
    e = 0;
    if(!n) return 1;
    ll res = mod_fact(n / m, m, e);
    e += n / m;
    if(n / m % 2) return res * (m - fact[n % m]) % m;
    return res * fact[n % m] % m;
}
