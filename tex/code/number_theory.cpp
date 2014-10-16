#include "macro.cpp"

// (x, y) s.t. a x + b y = gcd(a, b)
long extgcd(long a, long b, long& x, long& y) {
    long g = a; x = 1, y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}

// repi(i, 2, n) mod_inv[i] = mod_inv[m % i] * (m - m / i) % m
long mod_inv(long a, long m) {
    long x, y;
    if (extgcd(a, m, x, y) != 1) return 0;
    return (x % m + m) % m;
}

// a mod p where n! = a p^e in O(log_p n)
long mod_fact(long n, long p, long& e) {
    const int P = 1000010;
    static long fact[P] = {1};
    static bool done = false;
    if (not done) {
        repi(i, 1, P) fact[i] = fact[i - 1] * i % p;
        done = true;
    }
    e = 0;
    if (n == 0) return 1;
    long ret = mod_fact(n / p, p, e);
    e += n / p;
    if (n / p % 2) return ret * (p - fact[n % p]) % p;
    return ret * fact[n % p] % p;
}

// nCk mod p
long mod_binom(long n, long k, long p) {
    if (k < 0 or n < k) return 0;
    long e1, e2, e3;
    long a1 = mod_fact(n, p, e1);
    long a2 = mod_fact(k, p, e2);
    long a3 = mod_fact(n - k, p, e3);
    if (e1 > e2 + e3) return 0;
    return a1 * mod_inv(a2 * a3 % p, p) % p;
}

// a^b mod m
long mod_pow(long a, long b, long m) {
    long ret = 1;
    do {
        if (b & 1) ret = ret * a % m;
        a = a * a % m;
    } while (b >>= 1);
    return ret;
}
