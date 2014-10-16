#include "poly_inv.cpp"
const int inv2 = (mod+1)/2;
vector<int> poly_sqrt(const vector<int> &f) {
    int N = f.size();
    vector<int> s(1,1); // s[0] = sqrt(f[0])
    for(int k = 2; k <= N; k <<= 1) {
        s.resize(k);
        vector<int> ns = poly_mul(poly_inv(s), vector<int>(f.begin(),f.begin()+k));
        ns.resize(k);
        rep(i,k) s[i] = 1LL*(s[i]+ns[i])*inv2%mod;
    }
    return s;
}
