/*
#############################################
#                                           #
#           Quality Certificate             #
#                I class                    #
#                                           #
#   Tasks:                                  #
#       - Bromance                          #
#           (ICPC Training Camp 2024)       #
#                                           #
#############################################
*/

#include<bits/stdc++.h>
using namespace std;

struct Low{
    vector<vector<int>> graph;
    vector<int> *low;
    vector<int> vis;
    int n;
    int preorder = 0;

    Low(int in_n, vector<vector<int>>& in_graph, vector<int> *ans){
        n = in_n;
        graph = in_graph;
        low = ans;
        vis.assign(n + 1,0);
        low->assign(n + 1,0);
        dfs(1,0);
    }

    void dfs(int idx, int par){
        (*low)[idx] = ++preorder;
        vis[idx] = preorder;
        for(int i : graph[idx]){
            if(i == par) continue;
            if(vis[i]) (*low)[idx] = min((*low)[idx], vis[i]);
            else {
                dfs(i,idx);
                (*low)[idx] = min((*low)[idx],(*low)[i]);
            }
        }
    }
};

int main(){
    int n,m; cin >> n >> m;
    int u, v;
    vector<vector<int>> g(n + 1);
    for(int i = 0; i < m; i++){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    vector<int> low;
    Low algo(n,g,&low);
    cout << low.size() << endl;
    for(int i = 0; i <= n; i++){
        cout << low[i] << " ";
    }
    cout << "\n";
}