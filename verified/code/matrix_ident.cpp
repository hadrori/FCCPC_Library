/*
  単位行列 O( n )
  verified AOJ 1327
*/
mat identity(int n) {
    mat A(n, arr(n));
    rep(i,n) A[i][i] = 1;
    return A;
}
