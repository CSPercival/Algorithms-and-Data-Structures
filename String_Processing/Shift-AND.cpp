#include<bits/stdc++.h>
using namespace std;

struct ShiftAND{
    vector<char> alphabet;

    string text;
    string pattern; // must be under 64 letters
    vector<long long> C;    // charachteristic vector of prefixes that are suffixes of text[0..i]. First bit is always 1
    vector<long long> ACV;  // charachteristic vector of pattern for every letter of the alphabet. ACV[k][3] = 1 iff pattern[2] = k;    

    ShiftAND(string& in_pattern, string& in_text){
        pattern = in_pattern;
        text = in_text;
        // alphabet = in_alphabet;
        C.resize(text.size() + 1);

        compute_ACV();
    }

    void compute(){
        C[0] = 1;
        for(int i = 0; i < text.size(); i++){
            C[i + 1] = ((C[i] << 1) & ACV[text[i]]) | 1;
        }
    }

    //private

    void compute_ACV(){
        ACV.resize(130);
        for(int i = 0; i < pattern.size(); i++){
            ACV[pattern[i]] |= (1 << (i + 1));
        }
    }

    void print_in_binary(long long cv){
        for(int i = 0; i <= pattern.size(); i++){
            if(cv & (1 << i)) cout << '1';
            else cout << '0';
        }
        cout << "\n";
    }
};

int main(){
    string p,t;
    cin >> t >> p;

    ShiftAND algo(p,t);
    algo.compute();

    for(int i = 0; i <= t.size(); i++){
        algo.print_in_binary(algo.C[i]);
    }
    return 0;
}