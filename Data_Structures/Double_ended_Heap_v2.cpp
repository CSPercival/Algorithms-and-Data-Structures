#include<bits/stdc++.h>
using namespace std;

struct Heap{
    vector<int> H;
    int s = 0;
    bool (*cmp)(int,int) = [](int a, int b){ return a < b;};

    Heap() { H.resize(1,-1); }
    Heap(vector<int>& in_H) { build(in_H); }

    Heap(bool (*in_cmp)(int,int)) { H.resize(1,-1); cmp = in_cmp; }
    Heap(vector<int>& in_H, bool (*in_cmp)(int,int)) { build(in_H); cmp = in_cmp; }

    void insert(int key){
        H.push_back(key);
        s++;
        move_up(s);
    }
    
    int delete_top(){   // returns index from move_down function
        if(s == 0) return 0;
        swap(H[1],H[s]);
        H.pop_back();
        s--;
        if(s == 0) return 0;
        if(s) return move_down(1);
    }

    int get_top(){
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

    // auxiliary

    void move_up(int idx){
        while(idx > 1 && cmp(H[idx],H[idx/2])){
            swap(H[idx],H[idx/2]);
            idx /= 2;
        }
    }

    int move_down(int idx){
        int mini_idx = 0;
        while(idx <= s){
            mini_idx = idx;
            if(idx << 1 <= s && cmp(H[idx << 1],H[mini_idx])) mini_idx = idx << 1;
            if(idx << 1 <  s && cmp(H[idx << 1 + 1],H[mini_idx])) mini_idx = idx << 1 + 1;
            if(mini_idx == idx) break;
            swap(H[idx],H[mini_idx]);
            idx = mini_idx;
        }
        return idx;
    }

    int delete_last(){
        if(s == 0) return -1;
        int key = H.back();
        H.pop_back();
        s--;
        return key;
    }
};


struct DEHeap{
    Heap H;
    Heap L;
    int s;

    DEHeap()
        : H([](int a, int b) { return a > b; }),
          L([](int a, int b) { return a < b; })
    {}

    void insert(int key){
        s++;
        if(s == 1){
            H.insert(key);
            return;
        }
        if(H.s == L.s){
            if(key < L.H[(H.s + 1) / 2]){
                swap(key,L.H[(H.s + 1) / 2]);
                L.move_up((H.s + 1) / 2);
            }
            H.insert(key);
        } else {
            if(key > H.H.back()){
                swap(key, H.H.back());
                H.move_up(H.s);
            }
            L.insert(key);
        }
    }

    void delete_min(){
        if(s == 0) return;
        if(s == 1) H.delete_top(); return;

        if(L.s != H.s){
            L.insert(H.delete_last());
        }

        int tmp_idx = L.delete_top();
        if(tmp_idx <= L.s / 2) return;
        if(tmp_idx * 2 == H.s && L.H[tmp_idx] > H.H[tmp_idx * 2]){
            swap(L.H[tmp_idx],H.H[tmp_idx * 2]);
            H.move_up(tmp_idx * 2);
            return;
        }
        if(L.H[tmp_idx] > H.H[tmp_idx]){
            swap(L.H[tmp_idx], H.H[tmp_idx]);
            H.move_up(tmp_idx);
        }
    }

    void delete_max(){
        if(s == 0) return;
        if(s == 1) H.delete_top(); return;

        int tmp_idx;
        if(L.s == H.s){
            H.H[1] = L.delete_last();
            tmp_idx = H.move_down(1);
        } else {
            tmp_idx = H.delete_top();
        }

        if(tmp_idx <= H.s / 2) return;
        if(tmp_idx > L.s && H.H[tmp_idx] < L.H[tmp_idx / 2]){
            swap(H.H[tmp_idx], L.H[tmp_idx / 2]);
            L.move_up(tmp_idx / 2);
            return;
        }
        if(L.H[tmp_idx] > H.H[tmp_idx]){
            swap(L.H[tmp_idx], H.H[tmp_idx]);
            L.move_up(tmp_idx);
        }
    }

    int get_min(){
        if(L.s == 0) return -1;
        return L.H[1];
    }

    int get_max(){
        if(H.s == 0) return -1;
        return H.H[1];
    }
};

int main(){
    
    return 0;
}