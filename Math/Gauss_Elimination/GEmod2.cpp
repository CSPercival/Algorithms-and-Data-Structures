/*
#########################################################
#                                                       #
#                   Quality Certificate                 #
#                       I class                         #
#                                                       #
#   Tasks:                                              #
#       - System of Linear Equations                    #
#           (Yosupo Library Checker)                    #
#                                                       #
#########################################################
*/


#include<bits/stdc++.h>
using namespace std;
// #define int long long

typedef long long ll;

const int M = 1024;

// Ax = b, b = last column of a, A = rest of a
// returns number of free_var or -1 if there is no solution
int solve_equations(vector<bitset<M>> &a, int n, int m, bitset<M> &ans, vector<int> &where_ans){
    where_ans.assign(m - 1, -1);
    for(int row = 0, col = 0; row < n && col < m - 1; col++){
        if(!a[row][col]){
            for(int i = row + 1; i < n; i++){
                if(a[i][col]){
                    swap(a[row], a[i]);
                    break;
                }
            }
        }
        if(!a[row][col]) continue;

        for(int i = 0; i < n; i ++){
            if(i == row || !a[row][col]) continue;
            a[i] ^= a[row];
        }
        row++;
    }
    int no_free_var = M;
    int max_col = 0;
    for(int col = 0, row = 0; col < m - 1 && row < n; col++, max_col++){
        if(!a[row][col]){ 
            continue;
        }
        no_free_var--;
        ans[col] = a[row][m - 1];
        where_ans[col] = row;
        row++;
    }
    int sum;
    for(int row = 0; row < n; row++){
        sum = 0;
        sum = (a[row] & ans).count();
        if(sum != a[row][m - 1]) return -1;
    }

    return no_free_var;
}


int32_t main(){
    int n, m; cin >> n >> m;
    vector<bitset<M>> a(n);
    char val;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> val;
            a[i][j] = val - '0';
        }
    }
    for(int i = 0; i < n; i++){
        cin >> val;
        a[i][m] = val - '0';
    }
    bitset<M> ans;
    vector<int> where_ans;
    int rank = 0;
    rank = solve_equations(a, n, m, ans, where_ans);
    if(rank == -1){
        cout << rank << "\n";
        return 0;
    }
    cout << rank << "\n";
    for(int i = 0; i < m; i++){
        cout << ans[i];
    }
    cout << "\n";
    // vector<bitset<M>> base(rank);
    // for(int i = 0; i < m; i++){
    //     if(where_ans[i] != -1) continue; 
    //     for(int col = 0; col < m; col++){
    //         // cout << "deb " << i << ' ' << free_vars[i] << " " << col << "\n";
    //         if(col == free_vars[i]){
    //             base[i][col] = 1;
    //             continue;
    //         } 
    //         if(where_ans[col] == -1) continue;
    //         base[i][col] =  -a[where_ans[col]][free_vars[i]];
    //     }
    // }
    // for(int i = 0; i < free_vars.size(); i++){
    //     for(int col = 0; col < m; col++){
    //         cout << modplus(base[i][col]) << " ";
    //     }
    //     cout << "\n";
    // }
}