#include <bits/stdc++.h>

using namespace std;

// constants and eps-considered operators

const double eps = 1e-8; // choose carefully!
const double pi = acos(-1.0);

inline bool lt(double a, double b) { return a < b - eps; }
inline bool gt(double a, double b) { return lt(b, a); }
inline bool le(double a, double b) { return !lt(b, a); }
inline bool ge(double a, double b) { return !lt(a, b); }
inline bool ne(double a, double b) { return lt(a, b) or lt(b, a); }
inline bool eq(double a, double b) { return !ne(a, b); }

// points and lines

typedef complex<double> point;

inline double dot(point a, point b)   { return real(conj(a) * b); }
inline double cross(point a, point b) { return imag(conj(a) * b); }

struct line {
    point a, b;
    line(point a, point b) : a(a), b(b) {}
};

/*
 *  Here is what ccw(a, b, c) returns:
 *
 *          1
 *  ------------------
 *    2 |a  0  b| -2
 *  ------------------
 *         -1
 *
 *  Note: we can implement intersectPS(p, s) as !ccw(s.a, s.b, p).
 */
int ccw(point a, point b, point c) {
    b -= a, c -= a;
    if (gt(cross(b, c), 0.0)) return +1;
    if (lt(cross(b, c), 0.0)) return -1;
    if (lt(dot(b, c), 0.0))   return +2; // c -- a -- b
    if (lt(norm(b), norm(c))) return -2; // a -- b -- c
    return 0;
}
bool intersectLS(line &l, line &s) {
    return ccw(l.a, l.b, s.a) * ccw(l.a, l.b, s.b) <= 0;
}
bool intersectSS(line &s, line &t) {
    return intersectLS(s, t) and intersectLS(t, s);
}
bool intersectLL(line &l, line &m) {
    return ne(cross(l.b - l.a, m.b - m.a), 0.0)  // not parallel
        or eq(cross(l.b - l.a, m.a - l.a), 0.0); // overlap
}
point crosspointLL(line &l, line &m) {
    double p = cross(l.b - l.a, m.b - m.a);
    double q = cross(l.b - l.a, m.a - l.a);
    if (eq(p, 0.0) and eq(q, 0.0)) return m.a; // overlap
    assert(ne(p, 0.0));                        // parallel
    return m.a - q / p * (m.b - m.a);
}
point proj(line &l, point p) {
    double t = dot(l.b - l.a, p - l.a) / norm(l.b - l.a);
    return l.a + t * (l.b - l.a);
}
point reflection(line &l, point p) { return 2.0 * proj(l, p) - p; }

// distances (for shortest path)

double distanceLP(line &l, point p) { return abs(proj(l, p) - p); }
double distanceLL(line &l, line &m) {
    return intersectLL(l, m) ? 0.0 : distanceLP(l, m.a);
}
double distanceLS(line &l, line &s) {
    return intersectLS(l, s) ? 0.0 : min(distanceLP(l, s.a), distanceLP(l, s.b));
}
double distancePS(point p, line &s) {
    point h = proj(s, p);
    return ccw(s.a, s.b, h) ? min(abs(s.a - p), abs(s.b - p)) : abs(h - p);
}
double distanceSS(line &s, line &t) {
    return intersectSS(s, t) ? 0.0 :
        min({distancePS(s.a, t), distancePS(s.b, t), distancePS(t.a, s), distancePS(t.b, s)});
}

// circles

struct circle {
    point o; double r;
    circle() {}
    circle(point o, double r) : o(o), r(r) {}
};

bool intersectCL(circle &c, line &l) {
    return le(norm(proj(l, c.o) - c.o), c.r * c.r);
}
