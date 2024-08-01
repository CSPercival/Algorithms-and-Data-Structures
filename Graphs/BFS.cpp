#include<bits/stdc++.h>
using namespace std;

int infi = 1e9;

struct BFS{
    int n;                  // n - number of vertices
    vector<vector<int>> G;  // adjacency list
    vector<int> dist;       // distance from source array
    BFS(int in_n, vector<vector<int>>& in_G){
        n = in_n;
        G = in_G;
        dist.resize(n + 1,infi);
    }

    void traverse(int start){
        dist[start] = 0;
        queue<int> que;
        que.push(start);
        int v;
        while(!que.empty()){
            v = que.front();
            que.pop();
            for(int u : G[v]){
                if(dist[v] + 1 < dist[u]){
                    dist[u] = dist[v] + 1;
                    que.push(u);
                }
            }
        }
    }
};