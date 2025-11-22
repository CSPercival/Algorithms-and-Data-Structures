/*
#############################################
#                                           #
#           Quality Certificate             #
#                III class                  #
#                                           #
#   Tasks:                                  #
#       - ORDERSET - Order statistic set    #
#           (SPOJ Classical)                #
#       - ADAAPHID - Ada and Aphids         #
#           (SPOJ Classical)                #
#       - 911G. Mass Change Queries         #
#           (Codeforces 35 Edu)             #
#                                           #
#############################################
*/

#include<btis/stdc++.h>
using namespace std;

struct Node{
    int k, p;
    int s;
    Node *l;
    Node *r;
    Node(int ik) : k(ik), p(rand()), s(1), l(NULL), r(NULL) {}

    void update(){
        s = 1;
        if(l) s += l->s;
        if(r) s += r->s;
    }
};


int siz(Node *t){
    return t ? t->s : 0;
}

Node* find(Node *t, int k){
    if(!t || t->k == k) return t;
    return find(k < t->k ? t->l : t->r, k);
}

void split(Node *t, Node *&lt, Node *&rt, int split_key){
    if(!t){
        lt = NULL;
        rt = NULL;
    } else if(t->k <= split_key){
        split(t->r, t->r, rt, split_key);
        lt = t;
        lt->update();
    } else {
        split(t->l, lt, t->l, split_key);
        rt = t;
        rt->update();
    }
}

void merge(Node *&t, Node *lt, Node *rt){
    if(!lt) {t = rt; return;}
    if(!rt) {t = lt; return;}
    if(lt->p > rt->p){
        merge(lt->r, lt->r, rt);
        t = lt;
    } else {
        merge(rt->l, lt, rt->l);
        t = rt;
    }
    t->update();
}

void insert(Node *&t, Node *item){
    if(!t) {t = item; return;}
    if(t->p > item->p){
        if(item->k < t->k){
            insert(t->l, item);
        } else {
            insert(t->r, item);
        }
    } else {
        split(t, item->l, item->r, item->k);
        t = item;
    }
    t->update();
}

void erase(Node *&t, int key){
    if(!t) return;
    if(key == t->k){
        auto tt = t;
        merge(t, t->l, t->r);
        delete tt;
    } else {
        erase(key < t->k ? t->l : t->r, key);
    }
    if(t) t->update();
}

// void insert(Node *&t, Node *item){
//     Node *l, *r; 
//     split(t, l, r, item->k);
//     merge(l, l, item);
//     merge(t, l, r);
// }

// void erase(Node *&t, int key){
//     Node *l, *r; 
//     split(t, l, r, key);
//     split(l, l, t, key - 1);
//     merge(t, l, r);
// }

void Union(Node *&t, Node *lt, Node *rt){
    if(!lt){ t = rt; return;}
    if(!rt){ t = lt; return;}
    Node *tmpl, *tmpr;
    if(lt->p > rt->p){
        split(rt, tmpl, tmpr, lt->k);
        Union(lt->l, lt->l, tmpl);
        Union(lt->r, lt->r, tmpr);
        t = lt;
    } else {
        split(lt, tmpl, tmpr, rt->k);
        Union(rt->l, tmpl, rt->l);
        Union(rt->r, tmpr, rt->r);
        t = rt;
    }
    // update(t);
}

int kth(Node *t, int k){
    assert(t->s >= k);
    if(k <= siz(t->l)){
        return kth(t->l , k);
    }
    k -= siz(t->l);
    if(k == 1) return t->k;
    return kth(t->r, k - 1);
}

int count(Node *t, int k){
    if(!t) return 0;
    if(t->k <= k){
        return siz(t->l) + (t->k != k) + count(t->r, k);
    } else {
        return count(t->l, k);
    }
}

void print_node(Node *t, int shift){
    for(int i = 0; i < shift; i++){
        cout << "    ";
    }
    if(!t){ cout << "NULL\n"; return; }
    cout << "( " << t->k << ", " << t->p << " ) - s: " << t->s << "\n";
}

void print_treap(Node *t, int shift){
    if(!t){
        print_node(t, shift);
        return;
    }
    print_treap(t->r, shift + 1);
    print_node(t, shift);
    print_treap(t->l, shift + 1);
}


int main(){

}