/*
 verified (AOJ1501)
 */

using namespace std;
const long long MAX = 1024;

/* 拡張ユークリッドの互除法 */
// a x + b y = gcd(a, b)
long long extgcd(long long a, long long b, long long &x, long long &y) {
    long long g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g; // 1なら解あり
}

/* 逆元 */
long long mod_inverse(long long a, long long m){
    long long x, y;
    if(extgcd(a, m, x, y) != 1) return 0; // unsolvable
    return (m + x % m) % m;
}

int mod_inv[MAX];
void gen_mod_inv(int n, int mod){
    for(int i = 2; i < n; i++)
        mod_inv[i] = (ll) mod_inv[mod%i] * (mod - mod / i) % mod;
}

/* 冪剰余 */
// x^k % m
long long pow_mod(long long x, long long k, long long m) {
    if (k == 0)     return 1;
    if (k % 2 == 0) return pow_mod(x*x % m, k/2, m);
    else            return x*pow_mod(x, k-1, m) % m;
}

/* n! mod m */
//n! = a m^e としたときの a mod m を求める O(log_m n)
long long fact[MAX];
/*
 fact[0] = 1;
 repi(i,1,MAX) fact[i] = fact[i-1] * i % m;
 をどこかに入れること
 */
long long mod_fact(long long n, long long m, long long& e){
    e = 0;
    if(!n) return 1;

    //pの倍数の部分を計算
    long long res = mod_fact(n / m, m, e);
    e += n / m;

    // (p-1)! ≡ -1 (ウィルソンの定理)より (p-1)!^(n/p)はn/pの偶奇だけで計算できる
    if(n / m % 2) return res * (m - fact[n % m]) % m;
    return res * fact[n % m] % m;
}

/* nCk mod m */
long long mod_comb(long long n, long long k, long long m){
    if(n < 0 || k < 0 || n < k) return 0;
    long long e1, e2, e3;
    long long a1 = mod_fact(n, m, e1), a2 = mod_fact(k, m, e2), a3 = mod_fact(n - k, m, e3);
    if(e1 > e2 + e3) return 0; // m で割り切れる
    return a1 * mod_inverse(a2 * a3 % m, m) % m;
}