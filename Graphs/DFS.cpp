#include<bits/stdc++.h>
using namespace std;

struct DFS{
    int n;                  // n - number of vertices
    vector<vector<int>> G;  // adjacency list
    vector<int> vis;        // visited array
    DFS(int in_n, vector<vector<int>>& in_G){
        n = in_n;
        G = in_G;
        vis.resize(n + 1);
    }

    void traverse(int v){
        vis[v] = 1;
        for(int u : G[v]){
            if(vis[u] == 1) continue;
            traverse(u);
        }
    }
};