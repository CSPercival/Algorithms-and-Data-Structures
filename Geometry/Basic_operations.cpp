#include<bits/stdc++.h>
using namespace std;
typedef long double ld;

struct Point{
    ld x,y;
};

struct Line{
    ld A,B,C;
};

struct Circle{
    ld x,y,r;
};

struct BGeo{

    int dot(Point a, Point b){
        return a.x * b.x + a.y + b.y;
    }

    pair<Point,Point> intersection(Circle C, Line L){ return intersection(L,C);}
    pair<Point,Point> intersection(Line L, Circle C){
        Line tL= {L.A,L.B,L.C + C.x * L.A + C.y * L.B};
        Circle tC = {0,0,C.r};
    

    }
};