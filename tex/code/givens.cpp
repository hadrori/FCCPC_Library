#define mkrot(x,y,c,s) {double r = sqrt(x*x+y*y); c = x/r; s = y/r;}
#define rot(x,y,c,s) {double u = c*x+s*y; double v = -s*x+c*y; x = u; y = v;}
arr givens(mat A, arr b){
    int n = b.size();
    rep(i,n) repi(j,i+1,n){
        double c, s;
        mkrot(A[i][i], A[j][i], c, s);
        rot(b[i], b[j], c, s);
        repi(k,i,n) rot(A[i][k],A[j][k],c,s);
    }
    repd(i,n-1,0){
        repi(j,i+1,n)
            b[i] -= A[i][j] * b[j];
        b[i] /= A[i][i];
    }
    return b;
}
