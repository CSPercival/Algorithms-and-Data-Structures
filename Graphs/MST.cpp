/*
#############################################
#                                           #
#           Quality Certificate             #
#                NULL class                 #
#                                           #
#   Tasks:                                  #
#                                           #
#############################################
*/

#include<bits/stdc++.h>
using namespace std;

struct Edge{ int u,v,w; };

struct UnionFind{
    int n;
    vector<int> leader;
    
    UnionFind(int in_n){
        n = in_n;
        leader.resize(n + 1);
        for(int i = 1; i <= n; i++) leader[i] = i;
    }

    int Find(int a){
        if(leader[a] == a) return a;
        leader[a] = Find(leader[a]);
        return leader[a];
    }

    void Union(int a, int b){
        leader[Find(b)] = Find(a);
    }
};

struct MST{
    int n;
    vector<Edge> e;
    vector<Edge> *ans;

    MST(int in_n, vector<Edge> *in_e, vector<Edge> *in_ans){
        n = in_n;
        e = (*in_e);
        ans = in_ans;
        go();
    }

    void go(){
        UnionFind uf(n);
        sort(e.begin(), e.end(), [](const Edge &a, const Edge &b){
            if(a.w != b.w) return a.w < b.w;
            if(a.u != b.u) return a.u < b.u;
            return a.v < b.v;
        });

        for(auto edge : e){
            if(uf.Find(edge.u) != uf.Find(edge.v)){
                (*ans).push_back(edge);
                uf.Union(edge.u, edge.v);
            }
        }        
    }
};

int main(){
    int n, m; cin >> n >> m;
    int u, v, w;
    vector<Edge> e(m);
    for(int i = 0; i < m; i++){
        cin >> u >> v >> w;
        e.push_back({u,v,w});
    }

    vector<Edge> ans;
    MST mst(n,&e,&ans);
    for(auto edge : ans){
        cout << edge.u << " " << edge.v << " " << edge.w << "\n";
    }
}