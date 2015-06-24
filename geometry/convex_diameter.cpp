inline double diff(const vector<point> &P, const int &i) { return (P[(i+1)%P.size()] - P[i]);}
number convex_diameter(const polygon &pt) {
    const int n = pt.size();
    int is = 0, js = 0;
    for (int i = 1; i < n; ++i) {
        if (imag(pt[i]) > imag(pt[is])) is = i;
        if (imag(pt[i]) < imag(pt[js])) js = i;
    }
    number maxd = norm(pt[is]-pt[js]);

    int i, maxi, j, maxj;
    i = maxi = is;
    j = maxj = js;
    do {
        if (cross(diff(pt,i), diff(pt,j)) >= 0) j = (j+1) % n;
        else i = (i+1) % n;
        if (norm(pt[i]-pt[j]) > maxd) {
            maxd = norm(pt[i]-pt[j]);
            maxi = i; maxj = j;
        }
    } while (i != is || j != js);
    return maxd; /* farthest pair is (maxi, maxj). */
}
