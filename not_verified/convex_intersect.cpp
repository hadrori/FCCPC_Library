bool intersect_1pt(const point& a, const point& b,
                   const point& c, const point& d, point &r) {
    number D =  cross(b - a, d - c);
    if (eq(D,0)) return false;
    number t =  cross(c - a, d - c) / D;
    number s = -cross(a - c, b - a) / D;
    r = a + t * (b - a);
    return ge(t, 0) && le(t, 1) && ge(s, 0) && le(s, 1);
}
polygon convex_intersect(const polygon &P, const polygon &Q) {
    const int n = P.size(), m = Q.size();
    int a = 0, b = 0, aa = 0, ba = 0;
    enum { Pin, Qin, Unknown } in = Unknown;
    polygon R;
    do {
        int a1 = (a+n-1) % n, b1 = (b+m-1) % m;
        number C = cross(P[a] - P[a1], Q[b] - Q[b1]);
        number A = cross(P[a1] - Q[b], P[a] - Q[b]);
        number B = cross(Q[b1] - P[a], Q[b] - P[a]);
        point r;
        if (intersect_1pt(P[a1], P[a], Q[b1], Q[b], r)) {
            if (in == Unknown) aa = ba = 0;
            R.push_back( r );
            in = B > 0 ? Pin : A > 0 ? Qin : in;
        }
        if (C == 0 && B == 0 && A == 0) {
            if (in == Pin) { b = (b + 1) % m; ++ba; }
            else           { a = (a + 1) % m; ++aa; }
        } else if (C >= 0) {
            if (A > 0) { if (in == Pin) R.push_back(P[a]); a = (a+1)%n; ++aa; }
            else       { if (in == Qin) R.push_back(Q[b]); b = (b+1)%m; ++ba; }
        } else {
            if (B > 0) { if (in == Qin) R.push_back(Q[b]); b = (b+1)%m; ++ba; }
            else       { if (in == Pin) R.push_back(P[a]); a = (a+1)%n; ++aa; }
        }
    } while ( (aa < n || ba < m) && aa < 2*n && ba < 2*m );
    if (in == Unknown) {
        if (convex_contains(Q, P[0])) return P;
        if (convex_contains(P, Q[0])) return Q;
    }
    return R;
}
