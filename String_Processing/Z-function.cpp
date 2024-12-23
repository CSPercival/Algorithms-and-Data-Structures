/*
#############################################
#                                           #
#           Quality Certificate             #
#                II class                   #
#                                           #
#   Tasks:                                  #
#       - String Matching                   #
#           (CSES Problem Set)              #
#       - Z Algorithm                       #
#           (YOSUPO Library Checker)        #
#                                           #
#############################################
*/

#include<bits/stdc++.h>
using namespace std;

void ZFunction(string &s, vector<int> *z){
    (*z).assign(s.size(), 0);
    int rend = 0, lend = 0;
    int shift;
    for(int i = 1; i < (int)s.size(); i++){
        shift = 0;
        if(i < rend){
            shift = min(rend - i,(*z)[i - lend]);
        }
        while(i + shift >= rend && s[shift] == s[i + shift]) shift++;

        (*z)[i] = shift;
        if(shift != 0) shift--;
        if(i + shift > rend){
            rend = i + shift;
            lend = i;
        }
    }
}