/*
  not verified (AOJ1501)
 */

/* 拡張ユークリッドの互除法 */
// a x + b y = gcd(a, b)
ll extgcd(ll a, ll b, ll &x, ll &y) {
    ll g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g; // 1なら解あり
}

/* 逆元 */
ll mod_inverse(ll a, ll m){
    ll x, y;
    if(extgcd(a, m, x, y) != 1) return 0; // unsolvable
    return (m + x % m) % m;
}

ll mod_inv[MAX];
void gen_mod_inv(int n, ll mod){
    repi(i,2,n) mod_inv[i] = mod_inv[mod%i] * (mod - mod / i) % mod;
}

/* 冪剰余 */
// x^k % m
ll pow_mod(ll x, ll k, ll m) {
    if (k == 0)     return 1;
    if (k % 2 == 0) return pow_mod(x*x % m, k/2, m);
    else            return x*pow_mod(x, k-1, m) % m;
}

/* n! mod m */
//n! = a m^e としたときの a mod m を求める O(log_m n)
ll fact[MAX];
/*
 fact[0] = 1;
 repi(i,1,MAX) fact[i] = fact[i-1] * i % m;
 をどこかに入れること
 */
ll mod_fact(ll n, ll m, ll& e){
    e = 0;
    if(!n) return 1;
    //pの倍数の部分を計算
    ll res = mod_fact(n / m, m, e);
    e += n / m;
    // (p-1)! ≡ -1 (ウィルソンの定理)より (p-1)!^(n/p)はn/pの偶奇だけで計算できる
    if(n / m % 2) return res * (m - fact[n % m]) % m;
    return res * fact[n % m] % m;
}

/* nCk mod m */
ll mod_comb(ll n, ll k, ll m){
    if(n < 0 || k < 0 || n < k) return 0;
    ll e1, e2, e3;
    ll a1 = mod_fact(n, m, e1), a2 = mod_fact(k, m, e2), a3 = mod_fact(n - k, m, e3);
    if(e1 > e2 + e3) return 0; // m で割り切れる
    return a1 * mod_inverse(a2 * a3 % m, m) % m;
}
