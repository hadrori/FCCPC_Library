bool incircle(point a, point b, point c, point p) {
    a -= p; b -= p; c -= p;
    return norm(a) * cross(b, c)
         + norm(b) * cross(c, a)
         + norm(c) * cross(a, b) >= 0;
    // < : inside, = cocircular, > outside
}
#define SET_TRIANGLE(i, j, r) \
    E[i].insert(j); em[i][j] = r; \
    E[j].insert(r); em[j][r] = i; \
    E[r].insert(i); em[r][i] = j; \
    S.push(pair<int,int>(i, j));
#define REMOVE_EDGE(i, j) \
    E[i].erase(j); em[i][j] = -1; \
    E[j].erase(i); em[j][i] = -1;
#define DECOMPOSE_ON(i,j,k,r) { \
        int m = em[j][i]; REMOVE_EDGE(j,i); \
        SET_TRIANGLE(i,m,r); SET_TRIANGLE(m,j,r); \
        SET_TRIANGLE(j,k,r); SET_TRIANGLE(k,i,r); }
#define DECOMPOSE_IN(i,j,k,r) { \
        SET_TRIANGLE(i,j,r); SET_TRIANGLE(j,k,r); \
        SET_TRIANGLE(k,i,r); }
#define FLIP_EDGE(i,j) { \
        int k = em[j][i]; REMOVE_EDGE(i,j); \
        SET_TRIANGLE(i,k,r); SET_TRIANGLE(k,j,r); }
#define IS_LEGAL(i, j) \
    (em[i][j] < 0 || em[j][i] < 0 || \
     !incircle(P[i],P[j],P[em[i][j]],P[em[j][i]]))
double Delaunay(vector<point> P) {
    const int n = P.size();
    P.push_back( point(-inf,-inf) );
    P.push_back( point(+inf,-inf) );
    P.push_back( point(  0 ,+inf) );
    int em[n+3][n+3]; memset(em, -1, sizeof(em));
    set<int> E[n+3];
    stack< pair<int,int> > S;
    SET_TRIANGLE(n+0, n+1, n+2);
    for (int r = 0; r < n; ++r) {
        int i = n, j = n+1, k;
        while (1) {
            k = em[i][j];
            if      (ccw(P[i], P[em[i][j]], P[r]) == +1) j = k;
            else if (ccw(P[j], P[em[i][j]], P[r]) == -1) i = k;
            else break;
        }
        if      (ccw(P[i], P[j], P[r]) != +1) { DECOMPOSE_ON(i,j,k,r); }
        else if (ccw(P[j], P[k], P[r]) != +1) { DECOMPOSE_ON(j,k,i,r); }
        else if (ccw(P[k], P[i], P[r]) != +1) { DECOMPOSE_ON(k,i,j,r); }
        else                                  { DECOMPOSE_IN(i,j,k,r); }
        while (!S.empty()) {
            int u = S.top().first, v = S.top().second; S.pop();
            if (!IS_LEGAL(u, v)) FLIP_EDGE(u, v);
        }
    }
    double minarg = 1e5;
    for (int a = 0; a < n; ++a) {
        for(auto &b: E[a]) {
            int c = em[a][b];
            if (b < n && c < n) {
                point p = P[a] - P[b], q = P[c] - P[b];
                minarg = min(minarg, acos(dot(p,q)/abs(p)/abs(q)));
            }
        }
    }
    return minarg;
}
