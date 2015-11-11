long discrete_log(long a, long m) {
    if (a == 0) return -1;
    long b = sqrt(m)+1, t = 1;
    unordered_map<long,long> mem;
    rep(i, b) {
        mem[t] = i;
        t = t * a % m;
        if (t == 1) return i+1;
    }
    long u = t;
    for (int i = b; i < m; i += b) {
        if (mem.find(mod_inv(u, m)) != mem.end()) {
            return mem[mod_inv(u, m)] + i;
        }
        u = u * t % m;
    }
    return -1;
}
