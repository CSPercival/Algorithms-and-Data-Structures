/*
#############################################
#                                           #
#           Quality Certificate             #
#                I class                    #
#                                           #
#   Tasks:                                  #
#       - Digital Village (Easy Version)    #
#           (CF 977 Div. 2 Round)           #
#                                           #
#############################################
*/

#include<bits/stdc++.h>
using namespace std;

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

int main(){
    int n; cin >> n;
    UnionFind uf(n);

    int q; cin >> q;
    for(int i = 0; i < q; i++){
        int u, v; cin >> u >> v;
        cout << uf.Find(u) << " " << uf.Find(v) << "\n";
        uf.Union(u,v);
    }
}