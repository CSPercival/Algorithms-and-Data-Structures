#include<bits/stdc++.h>
using namespace std;

void Renumber(vector<int> &oriv, vector<int> &newv){
    vector<int> tmpv = oriv;
    sort(tmpv.begin(), tmpv.end());
    for(int i = 0; i < oriv.size(); i++){
        newv[i] = upper_bound(tmpv.begin(), tmpv.end(), oriv[i]) - tmpv.begin();
    }
}

struct SegTree{
    vector<pair<int,int>> t;
    int shift = 1;
    SegTree(int n){
        while(shift < n) shift <<= 1;
        t.assign(shift * 2, {0,0});
        for(int i = 0; i < n; i++) t[i + shift] = {0, -1};
        for(int i = shift - 1; i > 0; i--) t[i] = max(t[i * 2], t[i * 2 + 1]);
    }

    void update(int idx, pair<int,int> val){
        idx += shift;
        t[idx] = val;
        while(idx > 1){
            idx >>= 1;
            t[idx] = max(t[idx * 2], t[idx * 2 + 1]);
        }
    }

    pair<int,int> query_(int currl, int currr, int ql, int qr, int idx){
        // cout << ql << " " << currl << " " << currr << " " << qr << " " << idx << "\n";
        pair<int,int> ans1 = {0, -1}, ans2;
        if(currr < ql || qr < currl) return ans1;
        if(ql <= currl && currr <= qr) return t[idx];

        ans1 = query_(currl, (currl + currr)/2, ql, qr, idx * 2);
        ans2 = query_((currl + currr)/2 + 1, currr, ql, qr, idx * 2 + 1);
        if(ans1.first < ans2.first) ans1 = ans2;
        return ans1;
    }

    pair<int,int> query(int l, int r){
        return query_(0, shift - 1, l, r, 1);
    }
};

void Calculate_lis(vector<int> &a, vector<int> &ans){
    int n = a.size();
    vector<int> newa(n);
    Renumber(a, newa);

    // for(int i = 0; i < n; i++){
    //     cout << newa[i] << " ";
    // }
    // cout << "\n";

    vector<pair<int,int>> dp(n);
    SegTree seg(n + 1);
    int maxlis = 0, maxidx;
    for(int i = 0; i < n; i++){
        // cout << i << ": seg\n";
        dp[i] = seg.query(0, newa[i] - 1);
        dp[i].first++;
        seg.update(newa[i], {dp[i].first, i});
        if(dp[i].first > maxlis){
            maxlis = dp[i].first;
            maxidx = i;
        }
    }
    // for(int i = 0; i < n; i++){
    //     cout << i << ": " << dp[i].first << " " << dp[i].second << "\n";
    // }

    while(maxidx != -1){
        ans.push_back(maxidx);
        maxidx = dp[maxidx].second;
    }
    reverse(ans.begin(),ans.end());
}

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<int> ans;
    Calculate_lis(a, ans);

    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
}
