/*
#############################################
#                                           #
#           Quality Certificate             #
#                II class                   #
#                                           #
#   Tasks:                                  #
#       - Euler Trail (Undirected)          #
#           (Yosupo)                        #
#       - 2110E Melody                      #
#           (Codeforces)                    #
#                                           #
#############################################
*/

#include<bits/stdc++.h>
#define st first 
#define nd second
using namespace std;

// number of verticies, number of edges,
// g[i] = {j,k} => there is an edge from i to j with label k, 
// vector with final answer, ansv for vertex, anse for edges
bool EulerPath(int n, int m, vector<vector<pair<int,int>>> g, vector<int> &ansv, vector<int> &anse){
    int currv = 0;
    int noodd = 0;
    for(int i = 0; i <= n; i++){
        if(g[i].size() && currv == 0) currv = i;
        if(g[i].size()&1){
            noodd++;
            currv = i;
        }
    }
    if(noodd > 2){
        return false;
    }
    vector<pair<int,int>> estack;
    vector<int> dead(m + 1, 0);
    while(true){
        while(g[currv].size() && dead[g[currv].back().nd]){
            g[currv].pop_back();
        }
        if(g[currv].size()){
            dead[g[currv].back().nd] = 1;
            estack.push_back({currv, g[currv].back().nd});
            currv = g[currv].back().st;
        } else {
            ansv.push_back(currv);
            if(estack.empty()) break;
            currv = estack.back().st;
            anse.push_back(estack.back().nd);
            estack.pop_back();
        }
    }
    if(ansv.size() != m + 1) return false;
    return true;
}

void solve(){
    int n, m; cin >> n >> m;
    vector<vector<pair<int,int>>> g(n + 1);
    vector<int> ansv;
    vector<int> anse;

    int u, v;
    for(int i = 0; i < m; i++){
        cin >> u >> v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }

    if(EulerPath(n,m,g,ansv,anse)){
        cout << "Yes\n";
        for(int i = 0; i < ansv.size(); i++){
            cout << ansv[i] << " ";
        }
        cout << "\n";
        for(int i = 0; i < anse.size(); i++){
            cout << anse[i] << " ";
        }
        cout << "\n";
    } else {
        cout << "No\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int q; cin >> q;
    while(q--){
        solve();
    }
}