struct circle {
    point o; double r;
    circle(point o, double r) : o(o), r(r) {}
};

bool intersectCL(const circle& c, const line& l) {
    return le(norm(proj(l, c.o) - c.o), c.r * c.r);
}
int intersectCS(const circle& c, const line& s) {
    if (not intersectCL(c, s)) return 0;
    double a = abs(s.a - c.o);
    double b = abs(s.b - c.o);
    if (lt(a, c.r) and lt(b, c.r)) return 0;
    if (lt(a, c.r) or lt(b, c.r)) return 1;
    return ccw(s.a, s.b, proj(s, c.o)) ? 0 : 2;
}
bool intersectCC(const circle& c, const circle& d) {
    double dist = abs(d.o - c.o);
    return le(abs(c.r - d.r), dist) and le(dist, c.r + d.r);
}
line crosspointCL(const circle& c, const line& l) {
    point h = proj(l, c.o);
    double a = sqrt(c.r * c.r - norm(h - c.o));
    point d = a * (l.b - l.a) / abs(l.b - l.a);
    return line(h - d, h + d);
}
line crosspointCC(const circle& c, const circle& d) {
    double dist = abs(d.o - c.o), th = arg(d.o - c.o);
    double ph = acos((c.r * c.r + dist * dist - d.r * d.r) / (2.0 * c.r * dist));
    return line(c.o + polar(c.r, th - ph), c.o + polar(c.r, th + ph));
}

line tangent(const circle& c, double th) {
    point h = c.o + polar(c.r, th);
    point d = polar(c.r, th) * point(0, 1);
    return line(h - d, h + d);
}
vector<line> common_tangents(const circle& c, const circle& d) {
    vector<line> ret;
    double dist = abs(d.o - c.o), th = arg(d.o - c.o);
    if (abs(c.r - d.r) < dist) { // outer
        double ph = acos((c.r - d.r) / dist);
        ret.pb(tangent(c, th - ph));
        ret.pb(tangent(c, th + ph));
    }
    if (abs(c.r + d.r) < dist) { // inner
        double ph = acos((c.r + d.r) / dist);
        ret.pb(tangent(c, th - ph));
        ret.pb(tangent(c, th + ph));
    }
    return ret;
}
pair<circle, circle> tangent_circles(const line& l, const line& m, double r) {
    double th = arg(m.b - m.a) - arg(l.b - l.a);
    double ph = (arg(m.b - m.a) + arg(l.b - l.a)) / 2.0;
    point p = crosspointLL(l, m);
    point d = polar(r / sin(th / 2.0), ph);
    return mp(circle(p - d, r), circle(p + d, r));
}
line bisector(point a, point b);
circle circum_circle(point a, point b, point c) {
    point o = crosspointLL(bisector(a, b), bisector(a, c));
    return circle(o, abs(a - o));
}
