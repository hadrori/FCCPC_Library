inline long mod_mul(long a, long b, long m) {
    long ret = a * b - m * long(roundl((long double)(a) * b / m));
    return ret < 0 ? ret + m : ret;
}
long mod_powl(long a, long b, long m) {
    long ret = 1;
    do {
        if (b & 1) ret = mod_mul(ret, a, m);
        a = mod_mul(a, a, m);
    } while (b >>= 1);
    return ret;
}
