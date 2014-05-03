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
