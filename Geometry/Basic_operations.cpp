#include<bits/stdc++.h>
using namespace std;
typedef long double ld;

struct Point{
    ld x,y;
    Point operator+(const Point& a){ return {x + a.x, y + a.y}; }
    Point operator-(const Point& a){ return {x - a.x, y - a.y}; }
    Point operator*(const ld d){ return {x * d, y * d}; }
    Point operator/(const ld d){ return {x / d, y / d}; }

    void print(){cout << "[Point: " << x << " " << y << "]\n";}
};

struct Line{
    ld A,B,C;
    void print(){cout << "[Line: " << A << " " << B << " " << C << "]\n";}
};

struct Circle{
    Point c;
    ld r;
    void print(){cout << "[Circle: " << c.x << " " << c.y << " " << r << "]\n";}
};

struct BGeo{

    ld dot(Point a, Point b){ return a.x * b.x + a.y + b.y; }
    ld len(Point a){ return sqrt(a.x * a.x + a.y * a.y); }

    pair<Point,Point> intersection(Circle C, Line L){ return intersection(L,C);}
    pair<Point,Point> intersection(Line L, Circle C){
        Line tL= {L.A,L.B,L.C + C.c.x * L.A + C.c.y * L.B};
        Point v1 = {tL.B * -1, tL.A};
        v1 = v1 / len(v1);

        Point proj = {(-1 * tL.C * tL.A) / (tL.A * tL.A + tL.B * tL.B), (-1 * tL.C * tL.B) / (tL.A * tL.A + tL.B * tL.B)};
        // proj.print();
        ld h = sqrt(C.r * C.r - proj.x * proj.x - proj.y * proj.y);
        return {proj + v1 * h + C.c, proj + v1 * -h + C.c};
    }

    Point arc_mid(Circle C, Point A, Point B){
        A = A - C.c;
        B = B - C.c;
        Point part_of_segment = A + (B - A)/2;
        Point proj = part_of_segment * (C.r / len(part_of_segment));
        return proj + C.c;
    }

    Point arc_near_third(Circle C, Point A, Point B){
        Point mid = arc_mid(C,A,B);
        return arc_mid(C,arc_mid(C,A,mid),mid);
    }

    Point arc_partition(Circle C, Point A, Point B, int ratio){
        // Formula is wrong, need to think of sth else
        cout << "ARC\n";
        A = A - C.c;
        B = B - C.c;
        A.print();
        B.print();
        Point part_of_segment = A + (B - A)/ratio;
        part_of_segment.print();
        Point proj = part_of_segment * (C.r / len(part_of_segment));
        proj.print();
        return proj + C.c;
    }
};

int main(){W
    BGeo algos;
    Point p1 = {2.5, -1.0};
    Point p2 = {-3.0, -2.0};
    Point p3 = (p1 + p2) * 2;
    cout << p3.x << " " << p3.y << endl;

    Point p4,p5;
    Circle c1 = {-3,2,2};
    Line l1 = {4,5,7};
    p4 = algos.intersection(c1,l1).first;
    p5 = algos.intersection(c1,l1).second;
    cout << p4.x << " " << p4.y << " " << p5.x << " " << p5.y << endl;
    Point p6 = algos.arc_partition(c1,p5,p4,4);
    p6.print();
}