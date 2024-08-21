#include<bits/stdc++.h>
using namespace std;

struct DEHeap{
    vector<int> H;
    vector<int> L;
    int s = 0;
    int sh = 0;
    int sl = 0;
    DE_Heap(){
        H.resize(1,-1);
    }

    // DE_Heap(vector<int>& in_H){
    //     build(in_H);
    // }

    static bool L_func(int a, int b){ return a < b; }
    static bool H_func(int a, int b){ return a > b; }

    void insert(int key){
        s++;
        if(s == 1){
            sh++;
            H.push_back(key);
            return;
        }

        if(L.size() == H.size()){
            sh++;
            H.push_back(key);
            if(H[sh] < L[sh/2]){
                swap(H[sh],L[sh/2]);
                move_up(L, sh/2, L_func);
            } else{
                move_up(H, sh, H_func);
            }
        } else {
            sl++;
            L.push_back(key);
            if(L[sl] > H[sl]){
                swap(L[sl], H[sl]);
                move_up(H, sl, H_func);
            } else {
                move_up(L, sl, L_func);
            }
        }
    }
    
    void delete_min(){
        if(s == 0) return;
        if(s == 1){
            sh--;
            s--;
            H.pop_back();
            return;
        }

        s--;
        if(sh > sl){
            swap(L[1],H[sh]);
            H.pop_back();
            sh--;
        } else {
            swap(L[1],L[sl]);
            L.pop_back();
            sl--;
        }
        

    }

    // void delete_top(){
    //     if(s == 0) return;
    //     swap(H[1],H[s]);
    //     H.pop_back();
    //     s--;
    //     if(s) move_down(1);
    // }

    // int get_min(){
    //     if(s == 0) return -1;
    //     return H[1];
    // }

    // void build(vector<int>& in_H){
    //     H.resize(in_H.size() + 1);
    //     H[0] = -1;
    //     for(int i = 0; i < in_H.size(); i++) H[i + 1] = in_H[i];
    //     s = H.size() - 1;
    //     for(int i = s/2; i > 0; i--)
    //         move_down(i);
    // }

    // private

    

    void move_up(vector<int>& A, int idx, bool (*cmp)(int, int)){
        while(idx > 1 && cmp(A[idx],A[idx/2])){
            swap(A[idx],A[idx/2]);
            idx /= 2;
        }
    }

    int move_down(vector<int>& A, int idx, bool (*cmp)(int, int)){
        int mini_idx = 0;
        while(idx <= s){
            mini_idx = idx; 
            if(idx << 1 <= s && A[mini_idx] > A[idx << 1]) mini_idx = idx << 1;
            if(idx << 1 <  s && H[mini_idx] > H[idx << 1 + 1]) mini_idx = idx << 1 + 1;
            if(mini_idx == idx) break;
            swap(H[idx],H[mini_idx]);
            idx = mini_idx;
        }
    }
};

int main(){

    return 0;
}