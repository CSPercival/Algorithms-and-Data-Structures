/*
First biconnected component is always [1]. Need to fix that later
*/
#include<bits/stdc++.h>
using namespace std;

template <typename T> struct tag:reference_wrapper <T>{ using reference_wrapper <T>::reference_wrapper; };
template <typename T1, typename T2> static inline tag <ostream> operator<<(tag <ostream> os, pair<T1, T2> const& p){ return os.get()<<"{"<<p.first<<", "<<p.second<<"}", os;}
template <typename Other> static inline tag <ostream> operator<<(tag <ostream> os, Other const& o){ os.get()<<o; return os; }
template <typename T> static inline tag <ostream> operator <<(tag <ostream> os, vector <T> const& v){ os.get()<<"["; for (int i=0; i<v.size(); i++) if (i!=v.size()-1) os.get()<<v[i]<<", "; else os.get()<<v[i]; return os.get()<<"]", os; }
template <typename T> static inline tag <ostream> operator <<(tag <ostream> os, set <T> const& s){ vector <T> v; for (auto i: s) v.push_back(i); os.get()<<"["; for (int i=0; i<v.size(); i++) if (i!=v.size()-1) os.get()<<v[i]<<", "; else os.get()<<v[i]; return os.get()<<"]", os; }

struct Low{
    vector<vector<int>>* graph;
    vector<int> *low;
    vector<int> vis;
    int n;
    int preorder = 0;

    Low(int in_n, vector<vector<int>>* in_graph, vector<int> *ans){
        n = in_n; graph = in_graph; low = ans;
        vis.assign(n + 1,0);
        low->assign(n + 1,0);
        dfs(1,0);
    }

    void dfs(int idx, int par){
        (*low)[idx] = ++preorder;
        vis[idx] = preorder;
        for(int i : (*graph)[idx]){
            if(i == par) continue;
            if(vis[i]) (*low)[idx] = min((*low)[idx], vis[i]);
            else {
                dfs(i,idx);
                (*low)[idx] = min((*low)[idx],(*low)[i]);
            }
        }
    }
};

struct BCC{
    vector<vector<int>> *ans;
    vector<vector<int>> *graph;
    vector<int> bcc_stack;
    int n;
    vector<int> vis;
    vector<int> low;
    vector<int> *preorder;
    int bcc_ctr = 0;

    BCC(int in_n, vector<vector<int>> *in_graph, vector<vector<int>> *in_ans){
        n = in_n; graph = in_graph; ans = in_ans;
        vis.assign(n + 1, 0);
        Low algo(n,graph,&low);
        preorder = (&algo.vis);
        ans->emplace_back();
        bcc_stack.push_back(0);
        dfs(1);
    }

    void dfs(int idx){
        vis[idx] = 1;
        (*ans)[bcc_stack.back()].push_back(idx);
        for(int i : (*graph)[idx]){
            if(vis[i]) continue;
            if(low[i] >= (*preorder)[idx]){
                bcc_stack.push_back(++bcc_ctr);
                ans->emplace_back();
                (*ans)[bcc_stack.back()].push_back(idx);
            }
            dfs(i);
            if(low[i] >= (*preorder)[idx]){
                bcc_stack.pop_back();
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
    
    vector<vector<int>> bcc;
    BCC algo(n,&g,&bcc);
    for(auto i : bcc){
        for(int j : i){
            cout << j << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}
/*
9 11
1 2
2 3
3 4
4 1
3 5
5 6
6 3
3 7
7 8
8 9
9 3
*/