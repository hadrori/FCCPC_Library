enum { OUT, ON, IN };
int contains(const polygon& P, const point& p) {
    bool in = false;
    for (int i = 0; i < (int)P.size(); ++i) {
        point a = P[i] - p, b = P[(i+1)%P.size()] - p;
        if (imag(a) > imag(b)) swap(a, b);
        if (imag(a) <= 0 && 0 < imag(b) && cross(a, b) < 0) in = !in;
        if (cross(a, b) == 0 && dot(a, b) <= 0) return ON;
    }
    return in ? IN : OUT;
}
