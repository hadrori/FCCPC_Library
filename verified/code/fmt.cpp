#include <bits/stdc++.h>
using namespace std;
#define repi(i,a,b) for(int i = (a); i < (b); i++)
#define rep(i,a) repi(i,0,a)
const int MAX = 1<<20;

int extgcd(int a, int b, int &x, int &y) {
    int g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}

int mod_inverse(int a, int m){
    int x, y;
    if(extgcd(a, m, x, y) != 1) return 0; // unsolvable
    return (m + x % m) % m;
}

int pow_mod(int x, int k, int m) {
    int ret = 1;
    for(x%=m; k>0; x=1LL*x*x%m,k>>=1) if(k&1) ret = 1LL*ret*x%m;
    return ret;
}

const int mod = 7*17*(1<<23)+1;
// mod = a*2^k+1 and prime
// N = 2^e
vector<int> fmt(vector<int> f, bool inv){
    int e, N = f.size();
    assert((N&(N-1))==0 and "f.size() must be power of 2");
    for(e=0;;e++) if(N == (1<<e)) break;
    rep(m,N){
        int m2 = 0;
        rep(i,e) if(m&(1<<i)) m2 |= (1<<(e-1-i));
        if(m < m2) swap(f[m], f[m2]);
    }
    for(int t=1; t<N; t*=2){
        int r = pow_mod(3,(mod-1)/(t*2),mod);
        if(inv) r = mod_inverse(r,mod);
        for(int i=0; i<N; i+=2*t){
            int power = 1;
            rep(j,t){
                int x = f[i+j], y = 1LL*f[i+t+j]*power%mod;
                f[i+j] = (x+y)%mod;
                f[i+t+j] = (x-y+mod)%mod;
                power = 1LL*power*r%mod;
            }
        }
    }
    if(inv) for(int i=0,ni=mod_inverse(N,mod);i<N;i++) f[i] = 1LL*f[i]*ni%mod;
    return f;
}

vector<int> poly_mul(vector<int> f, vector<int> g){
    int N = max(f.size(),g.size())*2;
    f.resize(N); g.resize(N);
    f = fmt(f,0); g = fmt(g,0);
    rep(i,N) f[i] = 1LL*f[i]*g[i]%mod;
    f = fmt(f,1);
    return f;
}

vector<int> poly_inv(vector<int> f){
    int N = f.size();
    vector<int> r(1,mod_inverse(f[0],mod));
    for(int k = 2; k <= N; k <<= 1){
        vector<int> nr = poly_mul(poly_mul(r,r), vector<int>(f.begin(),f.begin()+k));
        nr.resize(k);
        rep(i,k/2) {
            nr[i] = (2*r[i]-nr[i]+mod)%mod;
            nr[i+k/2] = (mod-nr[i+k/2])%mod;
        }
        r = nr;
    }
    return r;
}

const int inv2 = (mod+1)/2;
vector<int> poly_sqrt(vector<int> f){
    int N = f.size();
    vector<int> s(1,1);
    for(int k = 2; k <= N; k <<= 1){
        s.resize(k);
        vector<int> ns = poly_mul(poly_inv(s), vector<int>(f.begin(),f.begin()+k));
        ns.resize(k);
        rep(i,k) s[i] = 1LL*(s[i]+ns[i])*inv2%mod;
    }
    return s;
}

int N, M;
vector<int> c, f;

void solve(){
    c[0] = 1;
    c = poly_sqrt(c);
    c[0] = (c[0]+1)%mod;
    f = poly_inv(c);
    rep(i,M) cout << f[i+1]*2%mod << endl;;
}

void input(){
    cin >> N >> M;
    int n = 1;
    while(n <= M) n <<= 1;
    c.resize(n,0);
    rep(i,N){
        int a; cin >> a;
        if(a > M) continue;
        c[a] = mod-4;
    }
    N = n;
}

int main(){
    input();
    solve();
    return 0;
}
