pair<long,long> crt(const vector<pair<long,long> >& rems) {
    long x = 0, m = 1, y, n;
    for (auto& p : rems) {
        tie(y, n) = p;
        long g = __gcd(m, n), u = x - y % m + m;
        if (u % g != 0) return {-1, -1};
        m /= g;
        long t = mod_inv(n/g, m) * (u/g) % m;
        m *= n, x = (t * n + y) % m;
    }
    return {x, m};
}
