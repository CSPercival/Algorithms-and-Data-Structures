#include"includes.hpp"
/*
#############################################
#                                           #
#           Quality Certificate             #
#                I class                    #
#                                           #
#   Tasks:                                  #
#       - C - And again the maze            #
#           (CF Gym CCRC 2025)              #
#                                           #
#############################################
*/
//88db86
void lowdfs(int u, int p, vi &vis, vi &low, vector<vi> &g){
    static int prectr = 0;
    low[u] = ++prectr;
    vis[u] = prectr;
    for(int v : g[u]){
        if(v == p) continue;
        if(vis[v])
            low[u] = min(low[u], vis[v]);
        else {
            lowdfs(v, u, vis, low, g);
            low[u] = min(low[u], low[v]);
        }
    }
}