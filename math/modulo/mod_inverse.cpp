ll mod_inverse(ll a, ll m){
    ll x, y;
    if(extgcd(a, m, x, y) != 1) return 0; // unsolvable
    return (m + x % m) % m;
}
ll mod_inv[MAX];
void gen_mod_inv(int n, ll mod){
    mod_inv[1] = 1;
    repi(i,2,n) mod_inv[i] = mod_inv[mod%i] * (mod - mod / i) % mod;
}
