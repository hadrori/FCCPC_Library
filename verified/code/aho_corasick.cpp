struct PMA{
    PMA* next[256];     //失敗時に0を利用
    vector<int> matched;//sort済みを仮定
    PMA(){memset(next, 0, sizeof(next));}
    ~PMA(){rep(i,256) if(next[i]) delete next[i];}
};

vector<int> set_union(const vector<int> &a,const vector<int> &b){
    vector<int> res;
    set_union(all(a), all(b), back_inserter(res));
    return res;
}

//パターンマッチングオートマトンの生成,生成元パターンをpattern, 個数をcountに代入して用いる
PMA *buildPMA(vector<string> pattern){
    PMA *root = new PMA, *now;
    root->next[0] = root;
    //Phase1.Trie木の生成
    rep(i,pattern.size()){
        now = root;
        rep(j,pattern[i].size()){
            if(now->next[(int)pattern[i][j]] == 0)
                now->next[(int)pattern[i][j]] = new PMA;
            now = now->next[(int)pattern[i][j]];
        }
        now->matched.push_back(i);
    }
    queue<PMA*> que;
    //Phase2.BFSによるオートマトンの生成
    repi(i,1,256){
        if(!root->next[i]) root->next[i] = root; //使われていない部分のnextをrootに
        else {
            root->next[i]->next[0] = root;      //失敗時はルートに戻る
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
                now->next[i]->matched = set_union(now->next[i]->matched,
                                                      next->next[i]->matched);
                que.push(now->next[i]);
            }
        }
    }
    return root;
}

void match(PMA* &pma, const string s, vector<int> &res){
    rep(i,s.size()){
        int c = s[i];
        while(!pma->next[c])
            pma = pma->next[0];
        pma = pma->next[c];
        rep(j,pma->matched.size())
            res[pma->matched[j]] = true;
    }
}
