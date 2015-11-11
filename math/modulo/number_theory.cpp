// (x, y) s.t. a x + b y = gcd(a, b)
long extgcd(long a, long b, long& x, long& y) {
    long g = a; x = 1, y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}
// inv[1] = 1; repi(i,2,n) inv[i] = inv[p%i] * (p - p/i) % p;
long mod_inv(long a, long m) {
    long x, y;
    if (extgcd(a, m, x, y) != 1) return 0;
    return (x % m + m) % m;
}
// a mod p where n! = a p^e in O(log_p n)
long mod_fact(long n, long p, long& e) {
    const int P = 1000010;
    static long fac[P] = {1};
    for (static int once = 1; once; --once) {
        repi(i,1,P) fac[i] = fac[i-1] * i % p;
    }
    e = 0;
    if (n == 0) return 1;
    long ret = mod_fact(n/p, p, e);
    e += n/p;
    return ret * (n/p%2 ? p - fac[n%p] : fac[n%p]) % p;
}
long mod_binom(long n, long k, long p) {
    if (k < 0 or n < k) return 0;
    long e1, e2, e3;
    long a1 = mod_fact(n, p, e1);
    long a2 = mod_fact(k, p, e2);
    long a3 = mod_fact(n - k, p, e3);
    if (e1 > e2 + e3) return 0;
    return a1 * mod_inv(a2 * a3 % p, p) % p;
}
long mod_pow(long a, long b, long m) {
    long ret = 1;
    do {
        if (b & 1) ret = ret * a % m;
        a = a * a % m;
    } while (b >>= 1);
    return ret;
}
inline long mod_mul(long a, long b, long m) {
    long ret = a * b - m * long(roundl((long double)(a) * b / m));
    return ret < 0 ? ret + m : ret;
}
