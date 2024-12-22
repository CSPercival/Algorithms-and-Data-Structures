#include<bits/stdc++.h>
using namespace std;

template <typename T> struct tag:reference_wrapper <T>{ using reference_wrapper <T>::reference_wrapper; };
template <typename T1, typename T2> static inline tag <ostream> operator<<(tag <ostream> os, pair<T1, T2> const& p){ return os.get()<<"{"<<p.first<<", "<<p.second<<"}", os;}
template <typename Other> static inline tag <ostream> operator<<(tag <ostream> os, Other const& o){ os.get()<<o; return os; }
template <typename T> static inline tag <ostream> operator <<(tag <ostream> os, vector <T> const& v){ os.get()<<"["; for (int i=0; i<v.size(); i++) if (i!=v.size()-1) os.get()<<v[i]<<", "; else os.get()<<v[i]; return os.get()<<"]", os; }
template <typename T> static inline tag <ostream> operator <<(tag <ostream> os, set <T> const& s){ vector <T> v; for (auto i: s) v.push_back(i); os.get()<<"["; for (int i=0; i<v.size(); i++) if (i!=v.size()-1) os.get()<<v[i]<<", "; else os.get()<<v[i]; return os.get()<<"]", os; }


vector<char> alphabet;
int ciconv[256];
int alphabet_size;

void init_alphabet(){
    // for(char i = '0'; i <= '9'; i++){
    //     ciconv[i] = alphabet.size();
    //     alphabet.push_back(i);
    // }
    // for(char i = 'A'; i <= 'Z'; i++){
    //     ciconv[i] = alphabet.size();
    //     alphabet.push_back(i);
    // }
    for(char i = 'a'; i <= 'c'; i++){
        ciconv[i] = alphabet.size();
        alphabet.push_back(i);
    }
    alphabet_size = alphabet.size();
}

struct Trie{

    struct Node{
        char c;
        int terminal = 0;
        int link = -1;
        int parent = -1;
        vector<int> next;
        Node(char in_c){
            c = in_c;
            next.assign(alphabet_size,-1);
        }
        void print(){
            cout << "parent: " << parent << "\n";
            cout << "char: " << c << "\n";
            cout << "suffix link: " << link << "\n";
            cout << "number of terminals: " << terminal << "\n";
            for(int i = 0; i < alphabet_size; i++){
                cout << "next[ " << alphabet[i] << " ] = " << next[i] << "\n";
            }
        }
    };

    vector<Node> t;
    Trie(){
        t.push_back({'#'});
    }

    void add(string *pattern){
        // cout << (*pattern) << endl;
        int ptr = 0;
        for(auto i : (*pattern)){
            // cout << ptr << " " << i << endl;
            if(t[ptr].next[ciconv[i]] == -1){
                t[ptr].next[ciconv[i]] = t.size();
                t.push_back({i});
                t[t[ptr].next[ciconv[i]]].parent = ptr;
            }
            // cout << "ok1" << endl;
            ptr = t[ptr].next[ciconv[i]];
        }
        t[ptr].terminal++;
    }
};

struct AhoCorasick{
    int n; // liczba patternow
    Trie data;
    string *text;
    vector<string> *patterns;

    AhoCorasick(vector<string> *in_patterns, string *in_text){
        n = (*in_patterns).size();
        text = in_text;
        patterns = in_patterns;
        for(int i = 0; i < n ; i++){
            data.add((&((*patterns)[i])));
        }
        compute_automaton();
    }

    //private

    void compute_automaton(){
        cout << "START COMPUTING AUTOMATON" << endl;
        print();
        queue<int> states;
        states.push(0);
        data.t[0].link = 0;
        for(int i = 0; i < alphabet_size; i++){
            if(data.t[0].next[i] != -1)
                data.t[data.t[0].next[i]].link = 0;
        }
        int ptr, ptr2;
        while(!states.empty()){
            ptr = states.front();
            states.pop();
            cout << "queue: " << ptr << endl;
            if(data.t[ptr].link == -1){
                cout << "ok2" << endl;
                // data.t[ptr].link = data.t[data.t[ptr].parent].link;
                ptr2 = data.t[data.t[ptr].parent].link;
                int idx_c = ciconv[data.t[ptr].c];
                while(ptr2 > 0 && data.t[ptr2].next[idx_c] == -1){
                    ptr2 = data.t[ptr2].link;
                    cout << "while: " << ptr2 << endl;
                }
                data.t[ptr].link = 0;
                if(data.t[ptr2].next[idx_c] != -1){
                    cout << "ok3" << endl;
                    data.t[ptr].link = data.t[ptr2].next[idx_c];
                }
            }
            for(int i = 0; i < alphabet_size; i++){
                if(data.t[ptr].next[i] == -1){
                    data.t[ptr].next[i] = max(0,data.t[data.t[ptr].link].next[i]);
                } else {
                    states.push(data.t[ptr].next[i]);
                }
            }
            cout << "nodzik: " << ptr << endl;
            data.t[ptr].print();
            cout << endl << endl;
        }
    }

    void print(){
        for(int i = 0; i < data.t.size(); i++){
            cout << "NODE " << i << " {\n";
            data.t[i].print();
            cout << "}\n";
        }
    }

};

int main(){
    init_alphabet();
    int n; cin >> n;
    vector<string> patterns(n);
    string text;
    for(int i = 0; i < n; i++){
        cin >> patterns[i];
    }
    cin >> text;
    AhoCorasick algo(&patterns,&text);
    cout << "DONE" << endl;
    algo.print();
    return 0;
}