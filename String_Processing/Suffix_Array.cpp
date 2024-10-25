#include<bits/stdc++.h>
using namespace std;

template <typename T> struct tag:reference_wrapper <T>{ using reference_wrapper <T>::reference_wrapper; };
template <typename T1, typename T2> static inline tag <ostream> operator<<(tag <ostream> os, pair<T1, T2> const& p){ return os.get()<<"{"<<p.first<<", "<<p.second<<"}", os;}
template <typename Other> static inline tag <ostream> operator<<(tag <ostream> os, Other const& o){ os.get()<<o; return os; }
template <typename T> static inline tag <ostream> operator <<(tag <ostream> os, vector <T> const& v){ os.get()<<"["; for (int i=0; i<v.size(); i++) if (i!=v.size()-1) os.get()<<v[i]<<", "; else os.get()<<v[i]; return os.get()<<"]", os; }
template <typename T> static inline tag <ostream> operator <<(tag <ostream> os, set <T> const& s){ vector <T> v; for (auto i: s) v.push_back(i); os.get()<<"["; for (int i=0; i<v.size(); i++) if (i!=v.size()-1) os.get()<<v[i]<<", "; else os.get()<<v[i]; return os.get()<<"]", os; }


struct SuffixArray{
    int n;
    string text;

    vector<int> p;
    vector<int> c;

    SuffixArray(string in_text){
        text = in_text + "$";
        n = text.size();
        p.assign(n,0);
        c.assign(n,0);
        compute();
    }

    void compute(){
        vector<int> alfa(256,0);
        for(int i = 0; i < n; i++){
            alfa[text[i]]++;
        }
        for(int i = 1; i < 256; i++){
            alfa[i] += alfa[i - 1];
        }
        for(int i = 0; i < n; i++){
            // p[i] = --alfa[text[i]];
            p[--alfa[text[i]]] = i;
        }
        int equivalence_class = 0;
        c[p[0]] = 0;
        for(int i = 1; i < n; i++){
            c[p[i]] = c[p[i - 1]];
            if(text[p[i]] != text[p[i - 1]]) c[p[i]]++;
        }
        // cout << p << "\n";
        // cout << c << "\n";
        int step = 1;
        vector<vector<int>> tmp(n);  
        while(step < n){
            for(int i = 0; i < n; i++){
                tmp[i] = {c[i], c[(i + step) % n], i};
            }
            RadixSort(&tmp);
            equivalence_class = 0;
            c[tmp[0][2]] = equivalence_class;
            for(int i = 1; i < n; i++){
                if(tmp[i][0] != tmp[i - 1][0] || tmp[i][1] != tmp[i - 1][1]) equivalence_class++;
                c[tmp[i][2]] = equivalence_class;
            }
            // cout << c << "\n";
            step <<= 1;
        }
        for(int i = 0; i < n; i++){
            p[c[i]] = i;
        }
    }

    void RadixSort(vector<vector<int>> *tmp){
        sort((*tmp).begin(), (*tmp).end(),[](const vector<int> &a,const vector<int> &b){
            for(int i = 0; i < a.size(); i++){
                if(a[i] != b[i]) return a[i] < b[i];
            }
            return true;
        });
    }

    //private

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