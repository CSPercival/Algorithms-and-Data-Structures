/*
#############################################
#                                           #
#           Quality Certificate             #
#                II class                   #
#                                           #
#   Tasks:                                  #
#       - Segment Tree for the Sum          #
#           (Codeforeces EDU course)        #
#       - Segment Tree for the Minimum      #
#           (Codeforeces EDU course)        #
#                                           #
#############################################
*/

#include<bits/stdc++.h>
using namespace std;

template<class T, class G>
struct SegmentTreePURQ{
    int n, shift = 1;
    vector<T> t;
    T pzero;
    T (*merge)(T, T);
    T (*create)(T, G);
    SegmentTreePURQ(int in_n, vector<G> &a, T in_pzero, T (*in_merge)(T,T), T (*in_create)(T, G)){
        n = in_n;
        pzero = in_pzero;
        merge = in_merge;
        create = in_create;
        while(shift < n) shift <<= 1;
        t.assign(2 * shift, pzero);
        for(int i = 0; i < n; i++) t[i + shift] = create(t[i + shift], a[i]);
        for(int i = shift - 1; i > 0; i--) t[i] = merge(t[i << 1] , t[(i << 1) + 1]);
    }

    void update(int idx, G val){
        for(idx += shift, t[idx] = create(t[idx], val); idx > 1; idx >>= 1){
            t[idx >> 1] = merge(t[idx], t[idx ^ 1]);
        }
    }

    T query(int l, int r){
        T ans = pzero;
        for(l += shift, r += shift; l < r; l >>= 1, r >>= 1){
            if(l & 1) ans = merge(ans, t[l++]);
            if(r & 1) ans = merge(ans, t[--r]);
        }
        return ans;
    }
};

//SetSum - SegmentTreePURQ<ll,int> ds(n, a, 0LL, [](ll a, ll b){return a + b;}, [](ll a, int b){return (long long)b;});
//SetMin - SegmentTreePURQ<ll,int> ds(n, a, 0LL, [](ll a, ll b){return a + b;}, [](ll a, int b){return (long long)b;});