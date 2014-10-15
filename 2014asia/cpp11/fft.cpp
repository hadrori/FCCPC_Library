#include <bits/stdc++.h>
using namespace std;
#define repi(i,a,b) for(int i = (a); i < int(b); i++)
#define rep(i,a) repi(i,0,a)
#define pb push_back
const double pi = acos(-1.0);
const double eps = 1e-5;
const int MAX = 1<<21;
typedef complex<double> cd;

vector<cd> fft(vector<cd> f, bool inv){
    int n, N = f.size();
    for(n=0;;n++) if(N == (1<<n)) break;
    rep(m,N){
        int m2 = 0;
        rep(i,n) if(m&(1<<i)) m2 |= (1<<(n-1-i));
        if(m < m2) swap(f[m], f[m2]);
    }

    for(int t=1;t<N;t*=2){
        double theta = acos(-1.0) / t;
        cd w(cos(theta), sin(theta));
        if(inv) w = cd(cos(theta), -sin(theta));
        for(int i=0;i<N;i+=2*t){
            cd power(1.0, 0.0);
            rep(j,t){
                cd tmp1 = f[i+j] + f[i+t+j] * power;
                cd tmp2 = f[i+j] - f[i+t+j] * power;
                f[i+j] = tmp1;
                f[i+t+j] = tmp2;
                power = power * w;
            }
        }
    }
    if(inv) rep(i,N) f[i] /= N;
    return f;
}

int a[MAX], n, m, N, M;
vector<cd> b;
vector<int> ans;

void solve(){
    b = fft(b,0);
    rep(i,N) b[i] *= b[i];
    b = fft(b,1);
    rep(i,M) {
        if(!a[i] and (b[i].real() > 1-eps)) { puts("NO"); return;}
        if(a[i] and (b[i].real() < eps)) ans.pb(i);
    }
    puts("YES");
    cout << ans.size() << endl;
    rep(i,(int)ans.size()) cout << ans[i] << " ";
    cout << endl;
}

void input(){
    cin >> n >> m;
    N = 1; M = m+1;
    while(N < 2*M) N <<= 1;
    b.resize(N,cd(0,0));
    rep(i,n){
        int x; cin >> x;
        a[x] = 1; b[x] = cd(1.,0);
    }
}

int main(){
    input();
    solve();
    return 0;
}
