pair<point,point> closest_pair(vector<point> p) {
    int n = p.size(), s = 0, t = 1, m = 2, S[n];
    S[0] = 0, S[1] = 1;
    sort(all(p)); // "p < q" <=> "p.x < q.x"
    double d = norm(p[s]-p[t]);
    for (int i = 2; i < n; S[m++] = i++) rep(j, m) {
            if (norm(p[S[j]]-p[i])<d) d = norm(p[s = S[j]]-p[t = i]);
            if (real(p[S[j]]) < real(p[i]) - d) S[j--] = S[--m];
        }
    return make_pair(p[s], p[t]);
}
