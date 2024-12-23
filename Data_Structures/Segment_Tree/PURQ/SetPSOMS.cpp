/*
#############################################
#                                           #
#           Quality Certificate             #
#                I class                    #
#                                           #
#   Tasks:                                  #
#       - PSOMS 2                           #
#           (Solve)                         #
#                                           #
#############################################
*/

#include<bits/stdc++.h>
#define BOOST ios_base::sync_with_stdio(0);cin.tie(0)
using namespace std;
typedef long long ll;

struct Node{
    ll best, pref, suf, all;
};
Node Nzero = {0LL,0LL,0LL,0LL};

struct ST_SetPSOMS{
    int n, shift = 1;
    vector<Node> t;
    ST_SetPSOMS(int in_n, vector<int> &a){
        n = in_n;
        while(shift < n) shift <<= 1;
        t.assign(2 * shift, Nzero);
        for(int i = 0; i < n; i++){
            t[i + shift] = create(a[i]);
        }
        for(int  i = shift - 1; i > 0; i--){
            t[i] = merge(t[i << 1], t[(i << 1) + 1]);
        }
    }

    void update(int idx, int val){
        idx += shift;
        t[idx] = create(val);
        for(idx >>= 1; idx > 0; idx >>= 1){
            t[idx] = merge(t[idx << 1], t[(idx << 1) + 1]);
        }
    }

    ll query(int l, int r){
        Node ansl = Nzero;
        Node ansr = Nzero;
        for(l += shift, r += shift; l < r; l >>= 1, r >>= 1){
            if(l & 1) ansl = merge(ansl, t[l++]);
            if(r & 1) ansr = merge(t[--r], ansr);
        }
        Node ans = merge(ansl, ansr);
        return ans.best;
    }

    Node create(int val){
        Node ans = {max(val, 0), max(val, 0), max(val, 0), val};
        return ans;
    }

    Node merge(Node a, Node b){
        Node ans;
        ans.all = a.all + b.all;
        ans.best = max({a.best, b.best, a.suf + b.pref, 0LL});
        ans.pref = max({a.pref, a.all + b.pref, 0LL});
        ans.suf = max({b.suf, a.suf + b.all, 0LL});
        return ans;
    }
};