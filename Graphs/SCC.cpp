/*
#########################################################
#                                                       #
#                   Quality Certificate                 #
#                       II class                        #
#                                                       #
#   Tasks:                                              #
#       - Strongly Connected Components                 #
#           (Yosupo Library Checker)                    #
#       - Obliviate, Then Reincarnate                   #
#           (2024 ICPC Asia Shenyang Regional Contest)  #
#                                                       #
#########################################################
*/

#include<bits/stdc++.h>
using namespace std;

// Everything is 0-indexed
int findSCC(vector<vector<int>> &g, vector<vector<int>> &rg, vector<vector<int>> &SCC, vector<int> &SCCid){
    int n = g.size();
    vector<int> order;
    vector<int> vis(n, -1);
    SCCid.assign(n, -1);
    SCC.assign(n, vector<int>());
    auto sccdfs = [](auto self, int idx, int color, vector<vector<int>> &graph,vector<int> &visited, vector<int> &vstack) -> void {
        visited[idx] = color;
        for(int i : graph[idx]){
            if(visited[i] == -1){
                self(self, i, color, graph, visited, vstack);
            }
        }
        vstack.push_back(idx);
    };
    for(int i = 0; i < n; i++)
        if(vis[i] == -1) sccdfs(sccdfs, i, i, g, vis, order);
    
    int scc_ctr = 0;
    for(int i = n - 1; i >= 0; i--){
        if(SCCid[order[i]] == -1){ 
            sccdfs(sccdfs, order[i], scc_ctr, rg, SCCid, SCC[scc_ctr]);
            scc_ctr++;
        }
    }
    return scc_ctr;
}

int main(){
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n, vector<int>());
    vector<vector<int>> rg(n, vector<int>());
    int a,b;
    for(int i = 0; i < m; i++){
        cin >> a >> b;
        // a--;
        // b--;
        g[a].push_back(b);
        rg[b].push_back(a);
    }
    vector<vector<int>> SCC(n + 1, vector<int>());
    vector<int> SCCid(n + 1);

    int noSCC = findSCC(g,rg,SCC,SCCid);

    cout << noSCC << "\n";
    for(int i = 0; i < noSCC; i++){
        cout << SCC[i].size() << " ";
        for(int j : SCC[i]){
            cout << j << " ";
        }
        cout << "\n";
    }
}