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
    for (int i = 0; i < n; ++i) A[i][i] = 1;
    return A;
}

//内積 O( n )
number inner_product(const array &a, const array &b) {
    number ans = 0;
    for (int i = 0; i < a.size(); ++i)
        ans += a[i] * b[i];
    return ans;
}

//積 O( n^2 )
array mul(const matrix &A, const array &x) {
    array y(A.size());
    for (int i = 0; i < A.size(); ++i)
        for (int j = 0; j < A[0].size(); ++j)
            y[i] = A[i][j] * x[j];
    return y;
}

//積 O( n^3 )
matrix mul(const matrix &A, const matrix &B) {
    matrix C(A.size(), array(B[0].size()));
    for (int i = 0; i < C.size(); ++i)
        for (int j = 0; j < C[i].size(); ++j)
            for (int k = 0; k < A[i].size(); ++k)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

//累乗 O( n^3 log e )
matrix pow(const matrix &A, int e) {
    return e == 0 ? identity(A.size())  :
    e % 2 == 0 ? pow(mul(A, A), e/2) : mul(A, pow(A, e-1));
}

//行列式 O( n^3 )
number det(matrix A) {
    const int n = A.size();
    number D = 1;
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i+1; j < n; ++j)
            if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
        swap(A[pivot], A[i]);
        D *= A[i][i] * (i != pivot ? -1 : 1);
        if (abs(A[i][i]) < eps) break;
        for(int j = i+1; j < n; ++j)
            for(int k = n-1; k >= i; --k)
                A[j][k] -= A[i][k] * A[j][i] / A[i][i];
    }
    return D;
}

//トレース O(n)
number trace(const matrix &A) {
    number ans = 0;
    for (int i = 0; i < A.size(); ++i)
        ans += A[i][i];
    return ans;
}

//ランク O( n^3 )
int rank(matrix A) {
    const int n = A.size(), m = A[0].size();
    int r = 0;
    for (int i = 0; r < n && i < m; ++i) {
        int pivot = r;
        for (int j = r+1; j < n; ++j)
            if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
        swap(A[pivot], A[r]);
        if (abs(A[r][i]) < eps) continue;
        for (int k = m-1; k >= i; --k)
            A[r][k] /= A[r][i];
        for(int j = r+1; j < n; ++j)
            for(int k = i; k < m; ++k)
                A[j][k] -= A[r][k] * A[j][i];
        ++r;
    }
    return r;
}

//Gauss消去法
//pivot選択なしなので精度悪いっぽい(未確認)
array gauss(matrix &A, array &b){
    int n = b.size();
    matrix B(n,array(n+1));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) B[i][j] = A[i][j];
    for(int i = 0; i < n; i++) B[i][n] = b[i];
    
    for(int k = 0; k < n-1; ++k){
        for(int i = k + 1; i < n; ++i){
            double a = B[i][k] / B[k][k];
            for(int j = k + 1; j < n+1; ++j){
                B[i][j] = B[i][j]-a*B[k][j];
            }
        }
    }
    B[n-1][n] = B[n-1][n]/B[n-1][n-1];
    for(int i = n-2; i >= 0; --i){
        double ax = 0.0;
        for(int j = i + 1; j < n; ++j){
            ax += B[i][j]*B[j][n];
        }
        B[i][n] = (B[i][n]-ax)/B[i][i];
    }
    array x(n);
    for(int i = 0; i < n; i++) x[i] = B[i][n];
    return x;
}

//Gauss-Jordan消去法(pivot選択あり)
//遅い Gauss消去法の1.5倍ぐらいになることも
array gauss_jordan(matrix &A, array &b){
    int n = b.size();
    matrix B(n,array(n+1));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) B[i][j] = A[i][j];
    for(int i = 0; i < n; i++) B[i][n] = b[i];
    for(int i = 0; i < n; i++){
        int pivot = i;
        for(int j = i; j < n; j++){
            if(abs(B[j][i]) > abs(B[pivot][i])) pivot = j;
        }
        swap(B[i],B[pivot]);
        //解がないか一意でない
        if(abs(B[i][i]) < EPS){
            array x;
            return x;
        }
        
        for(int j = i + 1; j <= n; j++) B[i][j] /= B[i][i];
        for(int j = 0; j < n; j++){
            if(i!=j){
                for(int k = i + 1; k <= n; k++) B[j][k] -= B[j][i]*B[i][k];
            }
        }
    }
    array x(n);
    for(int i = 0; i < n; i++) x[i] = B[i][n];
    return x;
}

//Givens消去法
//ピボット選択ありのGauss消去法よりは少し遅いが実装が楽
#define MAKEROT(x,y,c,s) {double r = sqrt(x*x+y*y); c = x/r; s = y/r;}
#define ROT(x,y,c,s) {double u = c*x+s*y; double v = -s*x+c*y; x = u; y = v;}
array givens(matrix A, array b){
    int n = b.size();
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            double c, s;
            MAKEROT(A[i][i], A[j][i], c, s);
            ROT(b[i], b[j], c, s);
            for (int k = i; k < n; k++)
                ROT(A[i][k],A[j][k],c,s);
        }
    }
    for (int i = n - 1; i >= 0; i--){
        for(int j = i + 1; j < n; j++)
            b[i] = b[i] - A[i][j] * b[j];
        b[i] = b[i] / A[i][i];
    }
    return b;
}