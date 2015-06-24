pair<ll, ll> crt(const vector<pair<ll, ll> >& rems) {
    ll x = 0, m = 1, y, n;
    for (const auto& p : rems) {
        tie(y, n) = p;
        const ll g = __gcd(m, n), u = x - y % m + m;
        if (u % g != 0) return {-1, -1};
        m /= g;
        const ll t = mod_inverse(n/g, m) * (u/g) % m;
        m *= n, x = (t * n + y) % m;
    }
    return {x, m};
}
