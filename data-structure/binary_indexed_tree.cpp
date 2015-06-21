template<class T> struct bit {
    int n;
    vector<T> dat;

    bit(int n) : n(n) { dat.assign(n,0); }
    // sum [0,i)
    T sum(int i){
        int ret = 0;
        for(--i; i>=0; i=(i&(i+1))-1) ret += bit[i];
        return ret;
    }
    // sum [i,j)
    T sum(int i, int j){ return sum(j) - sum(i);}
    // add x to i
    void add(int i, T x){ for(; i < n; i|=i+1) bit[i] += x;}
};
