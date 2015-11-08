const int N = 200010;
const int K = 18;
int st[K][N];
void construct(int *a, int n) {
    copy_n(a, n, st[0]);
    repi(k, 1, K) {
        for (int i = 0; i+(1<<k) <= n; ++i) {
            st[k][i] = min(st[k-1][i], st[k-1][i+(1<<(k-1))]);
        }
    }
}
int query(int a, int b) {
    int k = 31-__builtin_clz(b-a);
    return min(st[k][a], st[k][b-(1<<k)]);
}
