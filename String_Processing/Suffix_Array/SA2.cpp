#include<bits/stdc++.h>
#define st first
#define nd second
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
            p[--alfa[text[i]]] = i;
        }
        int equivalence_class = 0;
        c[p[0]] = 0;
        for(int i = 1; i < n; i++){
            if(text[p[i]] != text[p[i - 1]]) equivalence_class++;
            c[p[i]] = equivalence_class;
        }
        int step = 1;
        vector<pair<long long, int>> tmp(n);
        long long shift = 1e6;
        while(step < n){
            for(int i = 0; i < n; i++){
                tmp[i] = {shift * c[i] + c[(i + step) % n], i};
            }
            // cout << tmp << "\n";
            // RadixSort(&tmp);
            sort(tmp.begin(), tmp.end());
            // cout << tmp << "\n\n";
            equivalence_class = 0;
            c[tmp[0].nd] = 0;
            for(int i = 1; i < n; i++){
                if(tmp[i].st != tmp[i - 1].st) equivalence_class++;
                c[tmp[i].nd] = equivalence_class;
            }
            step <<= 1;
        }
        for(int i = 0; i < n; i++){
            p[c[i]] = i;
        }
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string text;
    cin >> text;

    SuffixArray algo(text);
    for(int i = 0; i < algo.p.size(); i++){
        cout << algo.p[i] << " ";
    }
    cout << "\n";
    return 0;
}