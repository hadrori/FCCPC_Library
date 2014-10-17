#include "macro.cpp"

// Givens elimination; O(n^3)

typedef double number;
typedef vector<vector<number> > matrix;

inline double my_hypot(double x, double y) { return sqrt(x * x + y * y); }
inline void givens_rotate(number& x, number& y, number c, number s) {
    number u = c * x + s * y, v = -s * x + c * y;
    x = u, y = v;
}
vector<number> givens(matrix A, vector<number> b) {
    const int n = b.size();
    rep(i, n) repi(j, i + 1, n) {
        const number r = my_hypot(A[i][i], A[j][i]);
        const number c = A[i][i] / r, s = A[j][i] / r;
        givens_rotate(b[i], b[j], c, s);
        repi(k, i, n) givens_rotate(A[i][k], A[j][k], c, s);
    }
    for (int i = n - 1; i >= 0; --i) {
        repi(j, i + 1, n) b[i] -= A[i][j] * b[j];
        b[i] /= A[i][i];
    }
    return b;
}
