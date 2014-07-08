struct PMA{
    PMA* next[256];    //0 is failure link 
    vi matched;
    PMA(){memset(next, 0, sizeof(next));}
    ~PMA(){rep(i,256) if(next[i]) delete next[i];}
};
vi set_union(const vi &a,const vi &b){
    vi res;
    set_union(all(a), all(b), back_inserter(res));
    return res;
}
// patternからパターンマッチングオートマトンの生成
PMA *buildPMA(vector<string> pattern){
    PMA *root = new PMA, *now;
    root->next[0] = root;
    rep(i, patter.size()){
        now = root;
        rep(j, pattern[i].size()){
            if(now->next[(int)pattern[i][j]] == 0)
                now->next[(int)pattern[i][j]] = new PMA;
            now = now->next[(int)pattern[i][j]];
        }
        now->matched.push_back(i);
    }
    queue<PMA*> que;
    repi(i,1,256){
        if(!root->next[i]) root->next[i] = root;
        else {
            root->next[i]->next[0] = root;
            que.push(root->next[i]);
        }
    }
    while(!que.empty()){
        now = que.front(); que.pop();
        repi(i,1,256){
            if(now->next[i]){
                PMA *next = now->next[0];
                while(!next->next[i]) next = next->next[0];
                now->next[i]->next[0] = next->next[i];
                now->next[i]->matched = set_union(now->next[i]->matched, next->next[i]->matched);
                que.push(now->next[i]);
            }
        }
    }
    return root;
}
void match(PMA* &pma, const string s, vi &res){
    rep(i,s.size()){
        int c = s[i];
        while(!pma->next[c])
            pma = pma->next[0];
        pma = pma->next[c];
        rep(j,pma->matched.size())
            res[pma->matched[j]] = 1;
    }
}
