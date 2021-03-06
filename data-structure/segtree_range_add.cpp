template<class T> struct segtree {
    int N;
    vector<T> dat, sum;
    segtree(int n) {
        N = 1;
        while(N < n) N <<= 1;
        dat.assign(2*N-1,0);
        sum.assign(2*N-1,0);
    }
    void add(int a, int b, T x) { add(a,b,x,0,0,N);}
    T add(int a, int b, T x, int k, int l, int r) {
        if(b <= l or r <= a) return dat[k];
        if(a <= l and r <= b) {
            sum[k] += x;
            return dat[k] += x;
        }
        int m = (l+r)/2;
        return dat[k] = min(add(a,b,x,2*k+1,l,m),add(a,b,x,2*k+2,m,r))+sum[k];
    }
    T minimum(int a, int b) { return minimum(a,b,0,0,N);}
    T minimum(int a, int b, int k, int l, int r) {
        if(b <= l or r <= a) return 1e9;
        if(a <= l and r <= b) return dat[k];
        int m = (l+r)/2;
        return min(minimum(a,b,2*k+1,l,m),minimum(a,b,2*k+2,m,r))+sum[k];
    }
};
