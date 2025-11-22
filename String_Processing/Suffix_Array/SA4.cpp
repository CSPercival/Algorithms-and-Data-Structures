#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
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
    vector<int> text;
    vector<int> p;
    vector<int> c;
    vector<int> cnt;
    vector<int> lcp;

    SuffixArray(string in_text){
        text = vector<int>(all(in_text));
        text.push_back('$');
        n = text.size();
        p.resize(n);
        c.resize(n);
        lcp.resize(n);
        compute();
    }

    void compute(){
        CountingSort(text, p, 256,
            [](int val){return val;}, 
            [](int idx){return idx;});
        int equivalence_class = 0;
        c[p[0]] = 0;
        for(int i = 1; i < n; i++){
            if(text[p[i]] != text[p[i - 1]]) equivalence_class++;
            c[p[i]] = equivalence_class;
        }
        int step = 1;
        vector<pair<pair<int, int>, int>> tmp(n);
        vector<pair<pair<int, int>, int>> tmp2(n);
        // cout << c << "\n";
        
        while(step < n){
            for(int i = 0; i < n; i++){
                tmp[i] = {{c[i],c[(i + step) % n]}, i};
            }
            // cout << tmp << "\n";
            CountingSort(tmp, tmp2, equivalence_class,
                [](pair<pair<int, int>, int> val){return val.st.nd;}, 
                [&tmp](int idx){return tmp[idx];});
            // cout << tmp2 << "\n";
            CountingSort(tmp2, tmp, equivalence_class,
                [](pair<pair<int, int>, int> val){return val.st.st;}, 
                [&tmp2](int idx){return tmp2[idx];});
            // cout << tmp << "\n";

            equivalence_class = 0;
            c[tmp[0].nd] = 0;
            for(int i = 1; i < n; i++){
                if(tmp[i].st != tmp[i - 1].st) equivalence_class++;
                c[tmp[i].nd] = equivalence_class;
            }
            // cout << c << "\n";
            step <<= 1;
        }
        for(int i = 0; i < n; i++){
            p[c[i]] = i;
        }
        int k = 0;
        for(int i = 0; i < n - 1; i++){
            while(text[i + k] == text[p[c[i] - 1] + k]) k++;
            lcp[c[i]] = k;
            k = max(k - 1, 0);
        }
    }

    template <class T, class G, typename F1, typename F2>
    void CountingSort(vector<G> &oa, vector<T> &na, int lim, F1 get, F2 new_val){
        cnt.assign(lim + 2, 0);
        for(auto x : oa){
            cnt[get(x) + 1]++;
        }
        for(int i = 1; i <= lim; i++){
            cnt[i] += cnt[i - 1];
        }
        for(int i = 0; i < oa.size(); i++){
            na[cnt[get(oa[i])]++] = new_val(i);
        }
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string text;
    cin >> text;

    SuffixArray algo(text);
    for(int i = 1; i < algo.p.size(); i++){
        cout << algo.p[i] << " ";
    }
    cout << "\n";
    return 0;
}