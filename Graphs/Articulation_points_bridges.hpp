#include"includes.hpp"
/*
#########################################################
#                                                       #
#           Quality Certificate                         #
#                I class                                #
#                                                       #
#   Tasks:                                              #
#       - And again the maze (C)                        #
#           (2025 ICPC Central Russia Regional Contest) #
#                                                       #
#########################################################
*/
int root;
//b104e7
void lowdfs(int u, int p, vi &vis, vi &low, vector<vi> &g, vi &artp, vii &bridge){
    static int prectr = 0;
    int cctr = 0, maxlow = 0;   // Articultion point
    low[u] = ++prectr;
    vis[u] = prectr;
    for(int v : g[u]){
        if(v == p) continue;
        if(vis[v])
            low[u] = min(low[u], vis[v]);
        else {
            cctr++; // Articultion point
            lowdfs(v, u, vis, low, g, artp, bridge);
            low[u] = min(low[u], low[v]);
            maxlow = max(maxlow, low[v]); // Articultion point
            if(low[v] > vis[u]) bridge.push_back({u,v}); // Bridges
        }
    }
    if((u == root && cctr > 1) || (u != root && maxlow >= vis[u])) 
        artp.push_back(u); // Articultion point
}