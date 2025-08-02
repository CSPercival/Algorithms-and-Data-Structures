/*
#####################################################
#                                                   #
#               Quality Certificate                 #
#                   I class                         #
#                                                   #
#   Tasks:                                          #
#       - Gorgeous Summation                        #
#           (2024 ICPC Belarus Regional Contest)    #
#                                                   #
#####################################################
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Hashing{
    int p, mod;
    string s;
    vector<ll> h;
    vector<ll> pk;
    Hashing(int ip, int imod, string &is){
        p = ip; mod = imod; s = "#" + is;
        h.resize(s.size());
        pk.resize(s.size());
        h[0] = 0;
        pk[0] = 1;
        for(int i = 1; i < s.size(); i++){
            h[i] = (h[i - 1] * p + s[i] - 'a' + 1) % mod;
            pk[i] = (pk[i - 1] * p) % mod;
        }
    }

    ll gethash(int l, int r){
        //if 0 based
        l++;r++;
        ll ans = (h[r] - h[l - 1] * pk[r - l + 1]) % mod;
        if(ans < 0) ans += mod;
        return ans;
    }

};

int main(){
    string s; cin >> s;
    Hashing h1(31, 1e9 + 7, s);
    int l1,r1,l2,r2;
    while(1){
        cin >> l1 >> r1 >> l2 >> r2;
        if(h1.gethash(l1,r1) == h1.gethash(l2,r2)){
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}