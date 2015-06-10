unsigned xorshift() {
    static unsigned x = 123456789;
    static unsigned y = 362436069;
    static unsigned z = 521288629;
    static unsigned w = 88675123;
    unsigned t;
    t = x ˆ (x << 11);
    x = y; y = z; z = w;
    return w = (w ˆ (w >> 19)) ˆ (t ˆ (t >> 8));
}
