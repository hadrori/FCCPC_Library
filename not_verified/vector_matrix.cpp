/*
 from Spaghetti Source
 行列演算(vector)
 not verified
*/

typedef double number;
const number eps = 1e-8;
typedef vector<number> array;
typedef vector<array> matrix;


//単位行列 O( n )
matrix identity(int n) {
    matrix A(n, array(n));
    rep(i,n) A[i][i] = 1;
    return A;
}

//内積 O( n )
number inner_product(const array &a, const array &b) {
    number ans = 0;
    rep(i,a.size()) ans += a[i] * b[i];
    return ans;
}

//積 O( n^2 )
array mul(const matrix &A, const array &x) {
    array y(A.size());
    rep(i,A.size()) rep(j,A[0].size())
        y[i] = A[i][j] * x[j];
    return y;
}

//積 O( n^3 )
matrix mul(matrix &A, matrix &B) {
    matrix C(A.size(), array(B[0].size()));
    rep(i,C.size()) rep(j,C.size()) rep(k,A.size())
        C[i][j] += A[i][k] * B[k][j];
    return C;
}

//累乗 O( n^3 log e )
matrix pow(matrix &A, int e) {
    return e == 0 ? identity(A.size())  :
    e % 2 == 0 ? pow(mul(A, A), e/2) : mul(A, pow(A, e-1));
}

//行列式 O( n^3 )
number det(matrix A) {
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
            repd(k,n-1,i)
                A[j][k] -= A[i][k] * A[j][i] / A[i][i];
    }
    return D;
}

//トレース O(n)
number trace(const matrix &A) {
    number ans = 0;
    rep(i,A.size()) ans += A[i][i];
    return ans;
}

//ランク O( n^3 )
int rank(matrix A) {
    int n = A.size(), m = A[0].size(), r = 0;
    rep(i,min(n,m)){
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

/*
  Givens消去法/
  ピボット選択ありのGauss消去法よりは少し遅いが実装が楽
  http://www.slideshare.net/tmaehara/ss-18244588
*/

#define mkrot(x,y,c,s) {double r = sqrt(x*x+y*y); c = x/r; s = y/r;}
#define rot(x,y,c,s) {double u = c*x+s*y; double v = -s*x+c*y; x = u; y = v;}
array givens(matrix A, array b){
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
