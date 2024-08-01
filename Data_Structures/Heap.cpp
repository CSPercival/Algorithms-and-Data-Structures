#include<bits/stdc++.h>
using namespace std;

struct Heap{
    vector<int> H;
    int s = 0;
    Heap(){
        H.resize(1,-1);
    }

    Heap(vector<int>& in_H){
        build(in_H);
    }

    void insert(int key){
        H.push_back(key);
        s++;
        move_up(s);
    }
    
    void delete_top(){
        if(s == 0) return;
        swap(H[1],H[s]);
        H.pop_back();
        s--;
        if(s) move_down(1);
    }

    int get_min(){
        if(s == 0) return -1;
        return H[1];
    }

    void build(vector<int>& in_H){
        H.resize(in_H.size() + 1);
        H[0] = -1;
        for(int i = 0; i < in_H.size(); i++) H[i + 1] = in_H[i];
        s = H.size() - 1;
        for(int i = s/2; i > 0; i--)
            move_down(i);
    }

    // private

    void move_up(int idx){
        while(idx > 1 && H[idx] < H[idx/2]){
            swap(H[idx],H[idx/2]);
            idx /= 2;
        }
    }

    void move_down(int idx){
        int mini_idx = 0;
        while(idx <= s){
            mini_idx = idx;
            if(idx << 1 <= s && H[mini_idx] > H[idx << 1]) mini_idx = idx << 1;
            if(idx << 1 <  s && H[mini_idx] > H[idx << 1 + 1]) mini_idx = idx << 1 + 1;
            if(mini_idx == idx) break;
            swap(H[idx],H[mini_idx]);
            idx = mini_idx;
        }
    }
};