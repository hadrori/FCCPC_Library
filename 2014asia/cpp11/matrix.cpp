#include "macro.cpp"

typedef double number;
typedef vector<number> vec;
typedef vector<vec> mat;

vec mul(const mat& A, const vec& x) {
    const int n = A.size();
    vec b(n);
    rep(i, n) rep(j, A[0].size()) {
        b[i] = A[i][j] * x[j];
    }
    return b;
}

mat mul(const mat& A, const mat& B) {
    const int n = A.size();
    const int o = A[0].size();
    const int m = B[0].size();
    mat C(n, vec(m));
    rep(i, n) rep(k, o) rep(j, m) {
        C[i][j] += A[i][k] * B[k][j];
    }
    return C;
}

mat pow(mat A, long m) {
    const int n = A.size();
    mat B(n, vec(n));
    rep(i, n) B[i][i] = 1;
    do {
        if (m & 1) B = mul(B, A);
        A = mul(A, A);
    } while (m >>= 1);
    return B;
}
