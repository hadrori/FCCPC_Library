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

