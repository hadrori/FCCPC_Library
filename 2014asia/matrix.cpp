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

const number eps = 1e-4;

// determinant; O(n^3)
number det(mat A) {
    int n = A.size();
    number D = 1;
    rep(i,n){
        int pivot = i;
        repi(j,i+1,n)
            if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
        swap(A[pivot], A[i]);
        D *= A[i][i] * (i != pivot ? -1 : 1);
        if (abs(A[i][i]) < eps) break;
        repi(j,i+1,n)
            for(int k=n-1;k>=i;--k)
                A[j][k] -= A[i][k] * A[j][i] / A[i][i];
    }
    return D;
}

// rank; O(n^3)
int rank(mat A) {
    int n = A.size(), m = A[0].size(), r = 0;
    for(int i = 0; i < m and r < n; i++){
        int pivot = r;
        repi(j,r+1,n)
            if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
        swap(A[pivot], A[r]);
        if (abs(A[r][i]) < eps) continue;
        for(int k=m-1;k>=i;--k)
            A[r][k] /= A[r][i];
        repi(j,r+1,n) repi(k,i,m)
            A[j][k] -= A[r][k] * A[j][i];
        ++r;
    }
    return r;
}
