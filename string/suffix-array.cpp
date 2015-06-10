const int MAX_N = 1000000;
int n, k;
int rnk[MAX_N+1], tmp[MAX_N+1], sa[MAX_N+1], lcp[MAX_N+1];

bool compare_sa(int i, int j) {
  if(rnk[i] != rnk[j]) return rnk[i] < rnk[j];
  else {
    int ri = i + k <= n ? rnk[i+k] : -1;
    int rj = j + k <= n ? rnk[j+k] : -1;
    return ri < rj;
  }
}

void construct_sa(string S, int *sa) {
  n = S.length();
  for(int i = 0; i <= n; i++) {
    sa[i] = i;
    rnk[i] = i < n ? S[i] : -1;
  }
  for(k = 1; k <= n; k*=2) {
    sort(sa, sa+n+1, compare_sa);
    tmp[sa[0]] = 0;
    for(int i = 1; i <= n; i++) {
      tmp[sa[i]] = tmp[sa[i-1]] + (compare_sa(sa[i-1], sa[i]) ? 1 : 0);
    }
    for(int i = 0; i <= n; i++) {
      rnk[i] = tmp[i];
    }
  }
}

void construct_lcp(string S, int *sa, int *lcp) {
  int n = S.length();
  for(int i = 0; i <= n; i++) rnk[sa[i]] = i;
  int h = 0;
  lcp[0] = 0;
  for(int i = 0; i < n; i++) {
    int j = sa[rnk[i] - 1];
    if(h > 0) h--;
    for(; j + h < n && i + h < n; h++) {
      if(S[j+h] != S[i+h]) break;
    }
    lcp[rnk[i] - 1] = h;
  }
}

//============ 使用例 =============//
// 文字列検索(蟻本p338 改) O(|T|log|S|)
// S中にTが含まれないなら-1, 含まれるならその先頭
int find_string(string S, int *sa, string T) {
  int a = 0, b = S.length();
  while(b - a > 1) {
    int c = (a + b) / 2;
    if(S.compare(sa[c], T.length(), T) < 0) a = c;
    else b = c;
  }
  return (S.compare(sa[b], T.length(), T) == 0)?sa[b]:-1;
}

// 最長共通部分文字列(蟻本p341 改) construct_sa以外はO(|S+T|)
// (先頭, 長さ)を返す
pair<int, int> LCS(string S, string T) {
  int sl = S.length();
  S += '\0' + T;
  construct_sa(S, sa);
  construct_lcp(S, sa, lcp);
  int len = 0, pos = -1;
  for(int i = 0; i < S.length(); i++) {
    if(((sa[i] < sl) != (sa[i+1] < sl)) && (len < lcp[i])) {
      len = lcp[i];
      pos = sa[i];
    }
  }
  return make_pair(pos, len);
}
