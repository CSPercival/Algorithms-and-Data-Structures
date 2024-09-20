#include<bits/stdc++.h>
#define st first
#define nd second
using namespace std;
typedef long double ld;

struct Point{
    ld x,y;
    Point operator+(const Point& a){ return {x + a.x, y + a.y}; }
    Point operator-(const Point& a){ return {x - a.x, y - a.y}; }
    Point operator*(const ld d){ return {x * d, y * d}; }
    Point operator/(const ld d){ return {x / d, y / d}; }
    bool operator==(const Point& a){ return ((x == a.x) && (y == a.y));}
    bool operator!=(const Point& a){ return ((x != a.x) || (y != a.y));}

    void print(){cout << "[Point: " << x << " " << y << "]\n";}
};

struct Line{
    ld A,B,C;
    Line(ld a,ld b,ld c){A = a; B = b; C = c;}
    Line(Point p1, Point p2){
        A = p1.y - p2.y;
        B = p2.x - p1.x;
        C = ((-1) * A * p1.x) - (B * p1.y);
    }
    void move(Point v){ C -= (v.x * A) + (v.y * B); }
    void print(){cout << "[Line: " << A << " " << B << " " << C << "]\n";}
};

struct Circle{
    Point c;
    ld r;
    void print(){cout << "[Circle: " << c.x << " " << c.y << " " << r << "]\n";}
};

struct BGeo{

    ld dot(Point a, Point b){ return (a.x * b.x) + (a.y * b.y); }
    ld cross(Point a, Point b){ return (a.x * b.y) - (a.y * b.x); }
    ld len(Point a){ return sqrtl((a.x * a.x) + (a.y * a.y)); }
    ld dist2(Point a, Point b){ return len(a - b); }
    ld norm(Point a){ return dot(a,a); }
    bool clockwise(Point a, Point b, Point c){ return (cross(b - a, c - b) < 0);}

    Point projection(Point A, Circle C){ return projection(C,A);}
    Point projection(Circle C, Point A){
        Point tA = A - C.c;
        return (tA * C.r) / len(tA) + C.c;
    }

    pair<Point,Point> intersection(Circle C, Line L){ return intersection(L,C);}
    pair<Point,Point> intersection(Line L, Circle C){
        Line tL = L; tL.move(C.c * -1);

        Point v1 = {tL.B * (-1), tL.A};
        v1 = v1 / len(v1);

        Point proj = {((-1)* tL.C * tL.A) / ((tL.A * tL.A) + (tL.B * tL.B)), ((-1) * tL.C * tL.B) / ((tL.A * tL.A) + (tL.B * tL.B))};
        ld h = sqrtl((C.r * C.r) - dot(proj,proj));
        return {proj + (v1 * h) + C.c, proj - (v1 * h) + C.c};
    }

    pair<Point,Point> intersection(Circle C1, Circle C2){
        Circle tC1 = {0,0,C1.r};
        Circle tC2 = {C2.c - C1.c, C2.r};
        Line l1((-2) * tC2.c.x, (-2) * tC2.c.y, (tC2.c.x * tC2.c.x) + (tC2.c.y * tC2.c.y) + (tC1.r * tC1.r) - (tC2.r * tC2.r));
        pair<Point,Point> ans = intersection(tC1,l1);
        return {ans.st + C1.c, ans.nd + C1.c};
    }

    Point arc_mid(Circle C, Point A, Point B){
        // assert(abs(dist2(A,B) - (2 * C.r)) > EPS);
        return projection(C, (B + A)/2.0);
    }

    Point arc_near_third(Circle C, Point A, Point B){
        Point mid = arc_mid(C,A,B);
        return arc_mid(C,arc_mid(C,A,mid),mid);
    }
};

int main(){
    BGeo algos;
    Point p1 = {2.5, -1.0};
    Point p2 = {-3.0, -2.0};
    Point p3 = (p1 + p2) * 2;
    cout << p3.x << " " << p3.y << endl;

    Point p4,p5;
    Circle c1 = {-3,2,2};
    Line l1(4,5,7);
    p4 = algos.intersection(c1,l1).first;
    p5 = algos.intersection(c1,l1).second;
    cout << p4.x << " " << p4.y << " " << p5.x << " " << p5.y << endl;
    Point p6 = algos.arc_near_third(c1,p5,p4);
    p6.print();
}