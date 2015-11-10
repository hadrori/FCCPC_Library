vector<int> manacher(const string &s) {
    int n = s.size()*2;
    vector<int> rad(n,0);
    for (int i = 0, j = 0, k; i < n; i += k, j = max(j-k, 0)) {
        while (i-j >= 0 && i+j+1 < n && s[(i-j)/2] == s[(i+j+1)/2]) ++j;
        rad[i] = j;
        for (k = 1; i-k >= 0 && rad[i]-k >= 0 && rad[i-k] != rad[i]-k; ++k)
            rad[i+k] = min(rad[i-k], rad[i]-k);
    }
    return rad;
}
