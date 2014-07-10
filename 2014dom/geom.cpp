#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

using namespace std;

#define rep(i,n) repi(i,0,n)
#define repi(i,a,b) for(int i=int(a);i<int(b);++i)

#define pb push_back
#define mp make_pair

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

inline double dot(point a, point b) { return real(conj(a) * b); }
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
    if (cross(b, c) > eps)    return +1;
    if (cross(b, c) < eps)    return -1;
    if (dot(b, c) < eps)      return +2; // c -- a -- b
    if (lt(norm(b), norm(c))) return -2; // a -- b -- c
    return 0;
}
bool intersectLS(const line& l, const line& s) {
    return ccw(l.a, l.b, s.a) * ccw(l.a, l.b, s.b) <= 0;
}
bool intersectSS(const line& s, const line& t) {
    return intersectLS(s, t) and intersectLS(t, s);
}
bool intersectLL(const line& l, const line& m) {
    return ne(cross(l.b - l.a, m.b - m.a), 0.0)  // not parallel
        or eq(cross(l.b - l.a, m.a - l.a), 0.0); // overlap
}
point crosspointLL(const line& l, const line& m) {
    double p = cross(l.b - l.a, m.b - m.a);
    double q = cross(l.b - l.a, m.a - l.a);
    if (eq(p, 0.0) and eq(q, 0.0)) return m.a; // overlap
    assert(ne(p, 0.0));                        // parallel
    return m.a - q / p * (m.b - m.a);
}
point proj(const line& l, point p) {
    double t = dot(l.b - l.a, p - l.a) / norm(l.b - l.a);
    return l.a + t * (l.b - l.a);
}
point reflection(const line& l, point p) { return 2.0 * proj(l, p) - p; }

// distances (for shortest path)

double distanceLP(const line& l, point p) { return abs(proj(l, p) - p); }
double distanceLL(const line& l, const line& m) {
    return intersectLL(l, m) ? 0.0 : distanceLP(l, m.a);
}
double distanceLS(const line& l, const line& s) {
    return intersectLS(l, s) ? 0.0 : min(distanceLP(l, s.a), distanceLP(l, s.b));
}
double distancePS(point p, const line& s) {
    point h = proj(s, p);
    return ccw(s.a, s.b, h) ? min(abs(s.a - p), abs(s.b - p)) : abs(h - p);
}
double distanceSS(const line& s, const line& t) {
    double st = min(distancePS(s.a, t), distancePS(s.b, t));
    double ts = min(distancePS(t.a, s), distancePS(t.b, s));
    return intersectSS(s, t) ? 0.0 : min(st, ts);
}

// circles

struct circle {
    point o; double r;
    circle() {}
    circle(point o, double r) : o(o), r(r) {}
};

bool intersectCL(const circle& c, const line& l) {
    return le(norm(proj(l, c.o) - c.o), c.r * c.r);
}
int intersectCS(const circle& c, const line& s) {
    if (not intersectCL(c, s)) return 0;
    double da = abs(s.a - c.o);
    double db = abs(s.b - c.o);
    if (lt(da, c.r) and lt(db, c.r)) return 0;
    if (lt(da, c.r) xor lt(db, c.r)) return 1;
    return ccw(s.a, s.b, proj(s, c.o)) ? 0 : 2;
}
bool intersectCC(const circle& c, const circle& d) {
    double dist = abs(d.o - c.o);
    return le(abs(c.r - d.r), dist) and le(dist, c.r + d.r);
}
line crosspointCL(const circle& c, const line& l) {
    point h = proj(l, c.o);
    double a = sqrt(c.r * c.r - norm(h - c.o));
    point p = a * (l.b - l.a) / abs(l.b - l.a);
    return line(h - p, h + p);
}
line crosspointCC(const circle& c, const circle& d) {
    double dist = abs(d.o - c.o), th = arg(d.o - c.o);
    double dth = acos((c.r * c.r + dist * dist - d.r * d.r) / (2.0 * c.r * dist));
    return line(c.o + polar(c.r, th - dth), c.o + polar(c.r, th + dth));
}

line tangent(const circle& c, double th) {
    point h = c.o + polar(c.r, th);
    point p = polar(c.r, th) * point(0, 1);
    return line(h - p, h + p);
}
vector<line> common_tangents(const circle& c, const circle& d) {
    vector<line> ret;
    double dist = abs(d.o - c.o), th = arg(d.o - c.o);
    if (abs(c.r - d.r) < dist) { // outer
        double dth = acos((c.r - d.r) / dist);
        ret.pb(tangent(c, th - dth));
        ret.pb(tangent(c, th + dth));
    }
    if (abs(c.r + d.r) < dist) {
        double dth = acos((c.r + d.r) / dist);
        ret.pb(tangent(c, th - dth));
        ret.pb(tangent(c, th + dth));
    }
    return ret;
}
pair<circle, circle> tangent_circles(const line& l, const line& m, double r) {
    point p = crosspointLL(l, m);
    double th = arg(m.b - m.a) - arg(l.b - l.a);
    double phi = (arg(m.b - m.a) + arg(l.b - l.a)) / 2.0;
    point d = polar(r / sin(th / 2.0), phi);
    return mp(circle(p - d, r), circle(p + d, r));
}
line bisector(point a, point b);
circle circum_circle(point a, point b, point c) {
    point o = crosspointLL(bisector(a, b), bisector(a, c));
    return circle(o, abs(a - o));
}

// polygons

typedef vector<point> form;

double area(const form& f) {
    double ret = 0.0;
    int p = f.size() - 1;
    rep(i, f.size()) {
        ret += cross(f[p], f[i]) / 2.0, p = i;
    }
    return ret;
}
point centroid(const form& f) {
    if (f.size() == 1) return f[0];
    if (f.size() == 2) return (f[0] + f[1]) / 2.0;
    point ret = 0.0;
    int p = f.size() - 1;
    rep(i, f.size()) {
        ret += cross(f[p], f[i]) * (f[p] + f[i]), p = i;
    }
    return ret / area(f) / 6.0;
}
line bisector(point a, point b) {
    point m = (a + b) / 2.0;
    return line(m, m + (b - a) * point(0, 1));
}
form convex_cut(const form& f, const line& l) {
    form ret;
    rep(i, f.size()) {
        point a = f[i], b = f[(i + 1) % f.size()];
        if (ccw(l.a, l.b, a) != -1) ret.pb(a);
        if (intersectLS(l, line(a, b))) ret.pb(crosspointLL(l, line(a, b)));
    }
    return ret;
}
form voronoi_cell(form f, vector<point> v, int k) {
    rep(i, v.size()) if (i != k) {
        f = convex_cut(f, bisector(v[i], v[k]));
    }
    return f;
}

int main() {
    form f;
    f.pb(point(0.0, 0.0));
    f.pb(point(1.0, 0.0));
    f.pb(point(0.0, 1.0));
    cerr << centroid(f) << endl;
}
