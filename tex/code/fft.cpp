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
