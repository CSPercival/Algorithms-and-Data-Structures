#include "includes.hpp"
/*
#########################################################
#                                                       #
#                   Quality Certificate                 #
#                       NULL class                      #
#                                                       #
#   Tasks:                                              #
#                                                       #
#########################################################
*/


//78c838
void sccdfs(int u, int c, vi &vis, vi &vstck, vector<vi> &g){
    vis[u] = c;
    for(int v : g[u])
        if(!vis[v])
            sccdfs(v, c, vis, vstck, g);
    vstck.push_back(u);
}
// everything is 1-indexed
// graph, reverse graph, list of vertices in every SCC, in what SCC is given vertex
int findSCC(int n, vector<vi> &g, vector<vi> &rg, vector<vi> &SCC, vi &SCCid){
    vi order;
    vi vis(n + 1, 0);
    for(int i = 1; i <= n; i++)
        if(!vis[i]) 
            sccdfs(i, i + 1, vis, order, g);
    for(int i = n; i >= 1; i--){
        if(!SCCid[order[i]]){
            SCC.emplace_back(); 
            sccdfs(order[i], SCC.size(), SCCid, SCC.back(), rg);
        }
    }
    return SCC.size();
}