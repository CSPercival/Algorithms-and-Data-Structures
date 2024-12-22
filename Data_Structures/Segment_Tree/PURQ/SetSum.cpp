/*
#############################################
#                                           #
#           Quality Certificate             #
#                I class                    #
#                                           #
#   Tasks:                                  #
#       - Segment Tree for the Sum          #
#           (Codeforeces EDU course)        #
#                                           #
#############################################
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// Sum, Point Update Range Query
struct ST_SetSum{
    vector<ll> t;
    int shift = 1;
    int n;
    ST_SetSum(int in_n, vector<int> &a){
        n = in_n;
        while(shift < n) shift <<= 1;
        t.assign(2 * shift, 0);
        for(int i = 0; i < n; i++) t[i + shift] = a[i];
        for(int i = shift - 1; i > 0; i--) t[i] = t[i << 1] + t[(i << 1) + 1];
    }
    void update(int idx, int val){
        for(idx += shift, t[idx] = val ;idx > 1; idx >>= 1) t[idx >> 1] = t[idx] + t[idx^1];
    }

    ll query(int l_idx, int r_idx){
        ll ans = 0;
        for(l_idx += shift, r_idx += shift; l_idx < r_idx; l_idx >>= 1, r_idx >>= 1){
            if(l_idx & 1) ans += t[l_idx++];
            if(r_idx & 1) ans += t[--r_idx];
        }
        return ans;
    }
};