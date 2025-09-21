#include<bits/stdc++.h>
using namespace std;

void Calculate_lis(vector<int> &a, vector<int> &ans){
    int n = a.size();
    vector<pair<int,int>> dp = {{-1, -1}};
    vector<int> par(n);

    auto binsearch = [&](int ai) -> int {
        int l = 0, r = dp.size(), m;
        while(l + 1 < r){
            m = (l + r) / 2;
            if(dp[m].first < ai){
                l = m;
            } else {
                r = m;
            }
        }
        return r;
    };

    for(int i = 0; i < n; i++){
        int modidx = binsearch(a[i]);
        if(modidx == dp.size()){
            dp.push_back({a[i], i});
        } else {
            dp[modidx] = {a[i], i};
        }
        par[i] = dp[modidx - 1].second;
    }
    int curridx = dp.back().second;
    while(curridx != -1){
        ans.push_back(curridx);
        curridx = par[curridx];
    }
    reverse(ans.begin(), ans.end());
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
