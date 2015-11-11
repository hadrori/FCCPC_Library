vector<int> lcp0(const string& s) {
    const int n = s.length();
    vector<int> ret(n);
    ret[0] = n;
    int i = 1, j = 0;
    while (i < n) {
        while (i+j < n and s[i+j] == s[j]) ++j;
        ret[i] = j;
        if (j == 0) { ++i; continue; }
        int k = 1;
        while (i+k < n and k+ret[k] < j) ret[i+k] = ret[k], ++k;
        i += k, j -= k;
    }
    return ret;
}
