/* nCk mod m */
ll mod_combi(ll n, ll k, ll m){
    if(n < 0 || k < 0 || n < k) return 0;
    ll e1, e2, e3;
    ll a1 = mod_fact(n, m, e1), a2 = mod_fact(k, m, e2), a3 = mod_fact(n - k, m, e3);
    if(e1 > e2 + e3) return 0; // m で割り切れる
    return a1 * mod_inverse(a2 * a3 % m, m) % m;
}
