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

