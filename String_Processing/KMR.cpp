#include<bits/stdc++.h>
using namespace std;

template <typename T> struct tag:reference_wrapper <T>{ using reference_wrapper <T>::reference_wrapper; };
template <typename T1, typename T2> static inline tag <ostream> operator<<(tag <ostream> os, pair<T1, T2> const& p){ return os.get()<<"{"<<p.first<<", "<<p.second<<"}", os;}
template <typename Other> static inline tag <ostream> operator<<(tag <ostream> os, Other const& o){ os.get()<<o; return os; }
template <typename T> static inline tag <ostream> operator <<(tag <ostream> os, vector <T> const& v){ os.get()<<"["; for (int i=0; i<v.size(); i++) if (i!=v.size()-1) os.get()<<v[i]<<", "; else os.get()<<v[i]; return os.get()<<"]", os; }
template <typename T> static inline tag <ostream> operator <<(tag <ostream> os, set <T> const& s){ vector <T> v; for (auto i: s) v.push_back(i); os.get()<<"["; for (int i=0; i<v.size(); i++) if (i!=v.size()-1) os.get()<<v[i]<<", "; else os.get()<<v[i]; return os.get()<<"]", os; }
 



struct KMR{
    struct SE{
        pair<int,int> k;
        int idx;

        bool operator < (const SE& a){
            return k < a.k;
        }
    };

    int N;
    string text;

    vector<int> calc_len;   // store lenghts that are caluclated
    vector<int> curr_num[21];
    vector<int> ans;
    vector<SE> sort_arr; 


    KMR(string& in_text){
        text = in_text;
        N = text.size();
        for(int i = 0; i <= 20; i++)
            curr_num[i].resize(N + 1);
        ans.resize(N + 1);
        sort_arr.resize(N + 1);
    }

    void compute(int m){
        while(calc_len.empty() || calc_len.back() * 2 <= m){
            compute_next(calc_len.size() - 1, m, curr_num[calc_len.size()]);
        }

        int ptr = 0;
        while(calc_len[ptr] * 2 <= m) ptr++;

        if(calc_len[ptr] == m){
            for(int i = 0; i < N - m + 1; i++){
                ans[i] = curr_num[ptr][i];
            }
            return;
        }

        compute_next(ptr, m, ans);
        return;
    }

    //private

    void compute_next(int in_idx, int m, vector<int>& out_vec){
        if(calc_len.empty()){
            sort_arr.resize(N);
            for(int i = 0; i < N; i++){
                sort_arr[i] = {{text[i],text[i]},i};
            }
            calc_len.push_back(1);
        } else {
            if(calc_len[in_idx] * 2 <= m){
                m = calc_len[in_idx] * 2;
                calc_len.push_back(m);
            }
            sort_arr.resize(N - m + 1);
            for(int i = 0; i < N - m + 1; i++){
                sort_arr[i] = {{curr_num[in_idx][i], curr_num[in_idx][i + m - calc_len[in_idx]]},i};
            }
        }
        
        linear_sort();
        int ctr = 1;
        out_vec[sort_arr[0].idx] = ctr;
        for(int i = 1; i < sort_arr.size(); i++){
            if(sort_arr[i].k != sort_arr[i - 1].k) ctr++;
            out_vec[sort_arr[i].idx] = ctr;
        }
    }

    void linear_sort(){
        sort(sort_arr.begin(), sort_arr.end());
    }
};

int main(){

    string text;
    int m;
    cin >> text >> m;

    KMR algo(text);
    algo.compute(m);

    for(int i : algo.ans){
        cout << i << " ";
    }
    cout << "\n";
    return 0;
}