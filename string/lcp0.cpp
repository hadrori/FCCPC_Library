vector<int> lcp0(const string& s) {
    const int n = s.length();
    vector<int> ret(n);
    ret[0] = n;
    for (int i = 1, j = 0, k; i < n; ) {
        while (i+j < n and s[i+j] == s[j]) ++j;
        ret[i] = j;
        if (j == 0) { ++i; continue; }
        for (k = 1; i+k < n and k+ret[k] < j; ++k) {
            ret[i+k] = ret[k];
        }
        i += k, j -= k;
    }
    return ret;
}
