number trace(const mat &A) {
    number ans = 0;
    rep(i,A.size()) ans += A[i][i];
    return ans;
}
