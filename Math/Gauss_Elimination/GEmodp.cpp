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

int mod = 998244353;
int infi = 2;

int fpow(ll x, ll k){
    ll ans = 1;
    for(int i = (1 << 30); i > 0; i >>= 1){
        ans = (ans * ans) % mod; 
        if(k & i)
            ans = (ans * x) % mod;
    }
    return ans;
}

int mod_inv(int x){
    return fpow(x, mod - 2);
}


// Ax = b, b = last column of a, A = rest of a
// returns number of free_var or -1 if there is no solution
int solve_equations(vector<vector<int>> &a, vector<int> &ans, vector<int> &where_ans, vector<int> &free_var){
    int n = a.size();
    int m = a[0].size();
    int div;
    ans.assign(m - 1, 0);
    where_ans.assign(m - 1, -1);
    for(int row = 0, col = 0; row < n && col < m - 1; col++){
        if(a[row][col] == 0){
            for(int i = row + 1; i < n; i++){
                if(a[i][col]){
                    swap(a[row], a[i]);
                    break;
                }
            }
        }
        if(a[row][col] == 0) continue;
        // if(a[row][col] < 0) a[row][col] += mod;
        div = mod_inv(a[row][col]);
        //cout << "div " << div << "\n";
        for(int j = col; j < m; j++){
            a[row][j] = ((ll)a[row][j] * div) % mod;
        }

        // cout << "one row mult-------------------\n";
        // for(int i = 0; i < n; i++){
        //     for(int j = 0; j < m; j++){
        //         cout << a[i][j] << " ";
        //     }
        //     cout << "\n";
        // }
        // cout << "\n";

        for(int i = 0; i < n; i ++){
            if(i == row) continue;
            div = ((ll)mod_inv(a[row][col]) * a[i][col]) % mod;
            for(int j = col; j < m; j++){
                a[i][j] = (a[i][j] - ((ll)a[row][j] * div)) % mod;
            }
        }

        // cout << "all row sub-------------------\n";
        // for(int i = 0; i < n; i++){
        //     for(int j = 0; j < m; j++){
        //         cout << a[i][j] << " ";
        //     }
        //     cout << "\n";
        // }
        // cout << "\n";

        row++;
    }
    int no_free_var = 0;
    int max_col = 0;
    for(int col = 0, row = 0; col < m - 1 && row < n; col++, max_col++){
        if(!a[row][col]){ 
            // nos = 0;
            // assert(false);
            no_free_var++;
            free_var.push_back(col); 
            continue;
        }
        // no_free_var--;
        // cout << col << " " << row << " " << a[row][m - 1] << " alalala\n";
        ans[col] = a[row][m - 1];
        where_ans[col] = row;
        row++;
    }
    for(int col = max_col; col < m -1; col++){
        free_var.push_back(col);
        no_free_var++;
    }
    int sum;
    for(int row = 0; row < n; row++){
        sum = 0;
        for(int col = 0; col < m - 1;  col++){
            sum = (sum + (ll)a[row][col] * ans[col]) % mod;
        }
        if(sum < 0) sum += mod;
        if(a[row][m - 1] < 0) a[row][m - 1] += mod;
        if(sum != a[row][m - 1]) return -1;
    }

    // cout << "-------------------\n";
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < m; j++){
    //         cout << a[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";

    return no_free_var;
}

int modplus(int x){
    if(x < 0) x += mod;
    return x;
}

int32_t main(){
    // cout << fpow(2, 11) << "\n";
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m + 1));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    for(int i = 0; i < n; i++){
        cin >> a[i][m];
    }
    vector<int> ans;
    vector<int> where_ans;
    vector<int> free_vars;
    int rank = 0;
    rank = solve_equations(a, ans, where_ans, free_vars);
    if(rank == -1){
        cout << rank << "\n";
        return 0;
    }
    cout << rank << "\n";
    for(int i = 0; i < m; i++){
        cout << modplus(ans[i]) << " ";
    }
    cout << "\n";
    // for(int i = 0; i < m; i++){
    //     cout << where_ans[i] << " ";
    // }
    // cout << "\n";
    vector<vector<int>> base(rank, vector<int>(m, 0));
    for(int i = 0; i < free_vars.size(); i++){
        for(int col = 0; col < m; col++){
            // cout << "deb " << i << ' ' << free_vars[i] << " " << col << "\n";
            if(col == free_vars[i]){
                base[i][col] = 1;
                continue;
            } 
            if(where_ans[col] == -1) continue;
            base[i][col] =  -a[where_ans[col]][free_vars[i]];
        }
    }
    for(int i = 0; i < free_vars.size(); i++){
        for(int col = 0; col < m; col++){
            cout << modplus(base[i][col]) << " ";
        }
        cout << "\n";
    }
}