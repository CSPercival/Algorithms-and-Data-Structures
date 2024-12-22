#include<bits/stdc++.h>
using namespace std;

template <typename T> struct tag:reference_wrapper <T>{ using reference_wrapper <T>::reference_wrapper; };
template <typename T1, typename T2> static inline tag <ostream> operator<<(tag <ostream> os, pair<T1, T2> const& p){ return os.get()<<"{"<<p.first<<", "<<p.second<<"}", os;}
template <typename Other> static inline tag <ostream> operator<<(tag <ostream> os, Other const& o){ os.get()<<o; return os; }
template <typename T> static inline tag <ostream> operator <<(tag <ostream> os, vector <T> const& v){ os.get()<<"["; for (int i=0; i<v.size(); i++) if (i!=v.size()-1) os.get()<<v[i]<<", "; else os.get()<<v[i]; return os.get()<<"]", os; }
template <typename T> static inline tag <ostream> operator <<(tag <ostream> os, set <T> const& s){ vector <T> v; for (auto i: s) v.push_back(i); os.get()<<"["; for (int i=0; i<v.size(); i++) if (i!=v.size()-1) os.get()<<v[i]<<", "; else os.get()<<v[i]; return os.get()<<"]", os; }


struct RadixSort{
    int max_val;
    vector<vector<int>> *arr;
    vector<vector<int>> arr2;

    SuffixArray(vector<vector<int>> *in_arr, int in_max_val){
        arr = in_arr;
        max_val = in_max_val;
        compute();
    }

    void compute(){
        vector<int> counting(max_val + 1);
        int mode = 0;
        for(int i = (*arr)[0].size() - 1; i >= 0; i--, mode ^= 0){
            counting.assign(max_val, 0);
            for(int j = 0; j < (*arr).size(); j++){
                if(mode) counting[arr2[j][i]]++;
                else counting[(*arr)[j][i]]++;
            }
            for(int j = 1; j <= max_val; j++) counting[j] += counting[j - 1];
            for(int j = n - 1; j >= 0; j--){
                if(mode){

                } else {
                    (*arr)[]
                }
            }
        }
    }
};

int main(){

    string text;
    cin >> text;

    SuffixArray algo(text);
    // cout << algo.p << "\n";
    // cout << algo.c << "\n";
    // cout << "\n";
    for(int i = 1; i < algo.p.size(); i++){
        cout << algo.p[i] << "\n";
    }
    return 0;
}