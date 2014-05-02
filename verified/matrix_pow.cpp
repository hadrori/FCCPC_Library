/*
  累乗 O( n^3 log e )
  verified AOJ 1327
*/
mat pow(mat &A, int e) {
    return e == 0 ? identity(A.size())  :
    e % 2 == 0 ? pow(mul(A, A), e/2) : mul(A, pow(A, e-1));
}

