ll pow_mod(ll x, ll k, ll m) {
    if (k == 0)     return 1;
    if (k % 2 == 0) return pow_mod(x*x % m, k/2, m);
    else            return x*pow_mod(x, k-1, m) % m;
}
