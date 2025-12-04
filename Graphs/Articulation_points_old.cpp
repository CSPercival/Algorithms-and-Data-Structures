#include<bits/stdc++.h>
using namespace std;

struct ArticulationPoints{
    vector<vector<int>> *graph;
    vector<int> low;
    vector<int> vis;
    vector<int> *ans;
    int n;
    int preorder = 0;

    ArticulationPoints(int in_n, vector<vector<int>> *in_graph, vector<int> *in_ans){
        n = in_n;
        graph = in_graph;
        ans = in_ans;
        vis.assign(n + 1,0);
        low.assign(n + 1,0);
        dfs(1,0);
    }

    void dfs(int idx, int par){
        low[idx] = ++preorder;
        vis[idx] = preorder;
        int children = 0;
        int max_children_low = 0;
        for(int i : (*graph)[idx]){
            if(i == par) continue;
            if(vis[i]) low[idx] = min(low[idx], vis[i]);
            else {
                children++;
                dfs(i,idx);
                low[idx] = min(low[idx],low[i]);
                max_children_low = max(max_children_low, low[i]);
            }
        }
        if(idx == 1 && children > 1) ans->push_back(idx);
        if(idx != 1 && max_children_low >= vis[idx]) ans->push_back(idx);
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
    
    vector<int> art;
    ArticulationPoints algo(n,&g,&art);
    for(int i : art){
        cout << i << " ";
    }
    cout << "\n";
}