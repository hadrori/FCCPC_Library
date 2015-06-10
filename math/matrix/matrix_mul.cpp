number inner_product(const arr &a, const arr &b) {
    number ans = 0;
    rep(i,a.size()) ans += a[i] * b[i];
    return ans;
}

arr mul(const mat &A, const arr &x) {
    arr y(A.size());
    rep(i,A.size()) rep(j,A[0].size())
        y[i] += A[i][j] * x[j];
    return y;
}

mat mul(const mat &A, const mat &B) {
    mat C(A.size(), arr(B[0].size()));
    rep(i,C.size()) rep(j,C[i].size()) rep(k,A[i].size())
        C[i][j] += A[i][k] * B[k][j];
    return C;
}

