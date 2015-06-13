#include "geometry.cpp"

namespace std {
    bool operator <(const point& a, const point& b) {
        return ne(real(a), real(b)) ? lt(real(a), real(b)) : lt(imag(a), imag(b));
    }
}

polygon convex_hull(vector<point> v) {
    const int n = v.size();
    sort(all(v));
    polygon ret(2 * n);
    int k = 0;
    for (int i = 0; i < n; ret[k++] = v[i++]) {
        while (k >= 2 and ccw(ret[k - 2], ret[k - 1], v[i]) <= 0) --k;
    }
    for (int i = n - 2, t = k + 1; i >= 0; ret[k++] = v[i--]) {
        while (k >= t and ccw(ret[k - 2], ret[k - 1], v[i]) <= 0) --k;
    }
    ret.resize(k - 1);
    return ret;
}
