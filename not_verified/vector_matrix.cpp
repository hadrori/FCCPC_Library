/*
 from Spaghetti Source
 行列演算(vector)
 not verified
*/

typedef double number;
const number eps = 1e-8;
typedef vector<number> arr;
typedef vector<arr> mat;


//行列式 O( n^3 )
number det(mat A) {
    int n = A.size();
    number D = 1;
    rep(i,n){
        int pivot = i;
        repi(j,i+1,n)
            if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
        swap(A[pivot], A[i]);
        D *= A[i][i] * (i != pivot ? -1 : 1);
        if (abs(A[i][i]) < EPS) break;
        repi(j,i+1,n)
            repd(k,n-1,i)
                A[j][k] -= A[i][k] * A[j][i] / A[i][i];
    }
    return D;
}

//ランク O( n^3 )
int rank(mat A) {
    int n = A.size(), m = A[0].size(), r = 0;
    for(int i = 0; i < m and r < n; i++){
        int pivot = r;
        repi(j,r+1,n)
            if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
        swap(A[pivot], A[r]);
        if (abs(A[r][i]) < eps) continue;
        repd(k,m-1,i)
            A[r][k] /= A[r][i];
        repi(j,r+1,n) repi(k,i,m)
            A[j][k] -= A[r][k] * A[j][i];
        ++r;
    }
    return r;
}
