typedef vector<point> polygon;

double area(const polygon& g) {
    double ret = 0.0;
    int j = g.size() - 1;
    rep(i, g.size()) {
        ret += cross(g[j], g[i]), j = i;
    }
    return ret / 2.0;
}
point centroid(const polygon& g) {
    if (g.size() == 1) return g[0];
    if (g.size() == 2) return (g[0] + g[1]) / 2.0;
    point ret = 0.0;
    int j = g.size() - 1;
    rep(i, g.size()) {
        ret += cross(g[j], g[i]) * (g[j] + g[i]), j = i;
    }
    return ret / area(g) / 6.0;
}
line bisector(point a, point b) {
    point m = (a + b) / 2.0;
    return line(m, m + (b - a) * point(0, 1));
}
polygon convex_cut(const polygon& g, const line& l) {
    polygon ret;
    int j = g.size() - 1;
    rep(i, g.size()) {
        if (ccw(l.a, l.b, g[j]) != -1) ret.pb(g[j]);
        if (intersectLS(l, line(g[j], g[i]))) ret.pb(crosspointLL(l, line(g[j], g[i])));
        j = i;
    }
    return ret;
}
polygon voronoi_cell(polygon g, const vector<point>& v, int k) {
    rep(i, v.size()) if (i != k) {
        g = convex_cut(g, bisector(v[i], v[k]));
    }
    return g;
}
