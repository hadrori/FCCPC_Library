#include <bits/stdc++.h>
using namespace std;

class fidict
{
    typedef unsigned long long ull;
    vector<ull> bs;
    vector<int> sum[2];
    int N, M;
    int popcount(int r) const { return sum[1][r/64]+__builtin_popcountll(bs[r/64]&((1ULL<<r%64)-1ULL));}
    int popcount(int l, int r) const { return popcount(r)-popcount(l);}
    
    int _select(ull x, int i) const {
        ull a, b, c, d; int t, s;
        a = (x & 0x5555555555555555ULL) + ((x >> 1) & 0x5555555555555555ULL);
        b = (a & 0x3333333333333333ULL) + ((a >> 2) & 0x3333333333333333ULL);
        c = (b & 0x0f0f0f0f0f0f0f0fULL) + ((b >> 4) & 0x0f0f0f0f0f0f0f0fULL);
        d = (c & 0x00ff00ff00ff00ffULL) + ((c >> 8) & 0x00ff00ff00ff00ffULL);
        t = (d & 0xffff) + ((d >> 16) & 0xffff);
        s = 0;
        s += ((t - i) & 256) >> 3; i -= t & ((t - i) >> 8);
        t = (d >> s) & 0x1f;
        s += ((t - i) & 256) >> 4; i -= t & ((t - i) >> 8);
        t = (c >> s) & 0xf;
        s += ((t - i) & 256) >> 5; i -= t & ((t - i) >> 8);
        t = (b >> s) & 0x7;
        s += ((t - i) & 256) >> 6; i -= t & ((t - i) >> 8);
        t = (a >> s) & 0x3;
        s += ((t - i) & 256) >> 7; i -= t & ((t - i) >> 8);
        t = (x >> s) & 0x1;
        s += ((t - i) & 256) >> 8;
        return s;
    }
public:
    fidict(){}
    fidict(const vector<bool> &a) {
        N = a.size(); M = (N+63)/64;
        bs.assign(M,0);
        sum[0].assign(M+1,0);
        sum[1].assign(M+1,0);
        for(int i = 0; i < N; ++i) {
            ull k = ull(a[i])<<(i%64);
            bs[i/64] |= k;
            sum[k>0][i/64+1]++;
        }
        for (int i = 0; i < M; ++i) {
            sum[0][i+1] += sum[0][i];
            sum[1][i+1] += sum[1][i];
        }
    }

    // number of 1 in [0,r), O(1)
    int rank(bool val, int r) const { return val? popcount(r): r-popcount(r);}
    int rank(bool val, int l, int r) const { return rank(val,r)-rank(val,l);}

    // index of i th val; 0-indexed, O(log N)
    int select(bool val, int i) {
        if(i >= sum[val].back() or i < 0) return -1;
        int j = lower_bound(begin(sum[val]),end(sum[val]),++i)-begin(sum[val])-1;
        i -= sum[val][j];
        return _select(val?bs[j]:~bs[j],i)+j*64;
    }
    int select(bool val, int i, int l) { return select(val,i+rank(val,l));}
    bool operator[](const int &i) { return bs[i/64]&(1ULL<<(i%64));}
};

// T is a kind of integer
template <class T> class wavelet
{
    typedef unsigned long long ull;
    int N, D; // length, depth
    T M; // max value
    vector<T> seq;
    vector<int> zeros;
    vector<fidict> B;

    void build(vector<T> f) {
        vector<T> l, r;
        for (int d = 0; d < D; d++) {
            vector<bool> b;
            for(auto &e: f) {
                bool k = (e>>(D-d-1))&1;
                if(k) r.push_back(e);
                else l.push_back(e);
                b.push_back(k);
            }
            B.push_back(fidict(b));
            zeros.push_back(l.size());
            swap(l,f);
            f.insert(end(f),begin(r),end(r));
            l.clear(); r.clear();
        }
    }
    // structure topk_node is for topk
    struct topk_node {
        T val;
        int l, r, d;
        topk_node(T val, int l, int r, int d)
            : val(val), l(l), r(r), d(d) {}
        bool operator<(const topk_node &v) const { return r-l < v.r-v.l;}
    };
    // rec for range_maxk
    void rmk_rec(int l, int r, int d, int &k, T val, vector<T> &vs) {
        if(l==r) return;
        if(d == D) {
            while(l++ < r and k > 0) vs.push_back(val), k--;
            return;
        }
        int lc = B[d].rank(1,l), rc = B[d].rank(1,r);
        if(vs.size()) {
            rmk_rec(lc+zeros[d],rc+zeros[d],d+1,k,val|(1ULL<<(D-d-1)),vs);
            rmk_rec(l-lc,r-rc,d+1,k,val,vs);
        }
        else {
            if(rc-lc > 0) rmk_rec(lc+zeros[d],rc+zeros[d],d+1,k,val|(1ULL<<(D-d-1)),vs);
            if(vs.size() and k > 0) rmk_rec(l-lc,r-rc,d+1,k,val,vs);
        }
    }
    // rec for range_freq
    int rf_rec(int l, int r, int d, T val, T lb, T ub) {
        if(l==r) return 0;
        if(d == D) return (lb<=val and val<ub? r-l: 0);
        T nv = val|(1LL<<(D-d-1)), nnv = nv|(((1LL<<(D-d-1))-1));
        if(ub <= val or nnv < lb) return 0;
        if(lb <= val and nnv < ub) return r-l;
        int lc = B[d].rank(1,l), rc = B[d].rank(1,r);
        return rf_rec(l-lc,r-rc,d+1,val,lb,ub)+rf_rec(lc+zeros[d],rc+zeros[d],d+1,nv,lb,ub);
    }
    // rec for range_list
    void rl_rec(int l, int r, int d, T val, T lb, T ub, vector<pair<T,int>> &vs) {
        if(l==r) return;
        if(d == D) {
            if(val < lb or ub <= val) return;
            if(r-l) vs.push_back(make_pair(val,r-l));
            return;
        }
        T nv = val|(1LL<<(D-d-1)), nnv = nv|(((1LL<<(D-d-1))-1));
        if(nnv < lb or ub <= val) return;
        int lc = B[d].rank(1,l), rc = B[d].rank(1,r);
        rl_rec(l-lc,r-rc,d+1,val,lb,ub,vs);
        rl_rec(lc+zeros[d],rc+zeros[d],d+1,nv,lb,ub,vs);
    }

    // rec for range_exist
    bool re_rec(int l, int r, int d, T val, T lb, T ub) {
        if(l==r) return 0;
        if(d == D) return (lb<=val and val<ub? r-l: 0);
        T nv = val|(1LL<<(D-d-1)), nnv = nv|(((1LL<<(D-d-1))-1));
        if(nnv < lb or ub <= val) return 0;
        if(lb <= val and nnv < ub) return 1;
        int lc = B[d].rank(1,l), rc = B[d].rank(1,r);
        return re_rec(l-lc,r-rc,d+1,val,lb,ub) || re_rec(lc+zeros[d],rc+zeros[d],d+1,nv,lb,ub);
    }

public:
    wavelet(const vector<T> &f) {
        N = f.size();
        M = *max_element(begin(f),end(f));
        D = 64-__builtin_clzll(M);
        seq = f;
        build(f);
    }

    // number of val, O(D)
    int rank(T val, int l, int r) {
        for (int d = 0; d < D; d++) {
            bool b = (val>>(D-d-1))&1;
            l = B[d].rank(b,l)+b*zeros[d];
            r = B[d].rank(b,r)+b*zeros[d];
        }
        return r-l;
    }
    int rank(T val, int r) { return rank(val,0,r);}

    // index of val, O(D log D)
    int select(T val, int i) {
        int ls[64], rs[64], l = 0, r = N;
        for (int d = 0; d < D; d++) {
            ls[d] = l; rs[d] = r;
            bool b = (val>>(D-d-1))&1;
            l = B[d].rank(b,l)+b*zeros[d];
            r = B[d].rank(b,r)+b*zeros[d];
        }
        for (int d = D-1; d >= 0; d--) {
            bool b = (val>>(D-d-1))&1;
            i = B[d].select(b,i,ls[d]);
            if(i >= rs[d] or i < 0) return -1;
            i -= ls[d];
        }
        return i;
    }
    int select(T val, int i, int l) { return select(val,i+rank(val,l));}

    T access(int i) { return seq[i];}
    T operator[](int i) { return seq[i];}
    
    // ith large val in [l,r), O(D)
    T quantile(int i, int l, int r) {
        T ret = 0;
        for (int d = 0; d < D; d++) {
            int lc = B[d].rank(1,l), rc = B[d].rank(1,r);
            if(rc-lc >= i) {
                l = lc+zeros[d];
                r = rc+zeros[d];
                ret |= 1ULL<<(D-d-1);
            }
            else {
                i -= rc-lc;
                l -= lc;
                r -= rc;
            }
        }
        return ret;
    }
    T maximum(int l, int r) { return quantile(0,l,r);}
    T minimum(int l, int r) { return quantile(r-l-1,l,r);}

    // freq top k in [l,r), O(D^3)?
    vector<T> topk(int l, int r, int k) {
        priority_queue<topk_node> q; // (freq,((l,r),d))
        vector<T> ret;
        q.push(topk_node(0,l,r,0));
        while(!q.empty()) {
            topk_node v = q.top(); q.pop();
            if(v.d == D) {
                ret.push_back(v.val);
                if(!--k) break;
            }
            int lc = B[v.d].rank(1,lc), rc = B[v.d].rank(1,rc);
            q.push(topk_node(v.val|(1ULL<<v.d), lc+zeros[v.d], rc+zeros[v.d], v.d+1));
            q.push(topk_node(v.val, l-lc, r-rc, v.d+1));
        }
        return ret;
    }

    // k most large vals
    vector<T> range_maxk(int l, int r, int k) {
        vector<T> ret;
        rmk_rec(l,r,0,k,0,ret);
        return ret;
    }

    // number of [lb,ub) elements in [l,r), O(DK) K = freq
    int range_freq(int l, int r, T lb, T ub) { return rf_rec(l,r,0,0,lb,ub);}

    // list of elements and freq in [lb,ub)  in [l,r) O(DK) size of list(<= r-l)
    vector<pair<T,int>> range_list(int l, int r, T lb, T ub) {
        vector<pair<T,int>> ret;
        rl_rec(l,r,0,0,lb,ub,ret);
        return ret;
    }

    // list of elements in rectangle [(l,lb),(r,ub)), O(DK log D) K = size of list(<= r-l)
    // selectを使わなくてもできる？
    vector<pair<int,T>> range_rect(int l, int r, T lb, T ub) {
        vector<pair<int,T>> ret;
        vector<pair<T,int>> vs = range_list(l,r,lb,ub);
        for(auto &p: vs)
            for (int i = 0; i < p.second; i++)
                ret.push_back(make_pair(select(p.first,i,l,r),p.first));
        return ret;
    }

    bool range_exist(int l, int r, T lb, T ub) {
        return re_rec(l,r,0,0,lb,ub);
    }
};
