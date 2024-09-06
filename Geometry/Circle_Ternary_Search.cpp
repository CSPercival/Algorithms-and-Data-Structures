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

struct Circle{
    Point c;
    ld r;
    void print(){cout << "[Circle: " << c.x << " " << c.y << " " << r << "]\n";}
};

struct BGeo{

    ld len(Point a){ return sqrt(a.x * a.x + a.y * a.y); }
    ld dist(Point a, Point b){ return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }

    Point arc_mid(Circle C, Point A, Point B){
        // if AB forms diameter it will cause error
        // Do not know what happens if arc AB takes more than half of a circle
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
};

struct CTS{
    ld EPS = 1e-9;
    Point A,B;
    Circle C;
    ld (*costf)(Point);
    BGeo calc;

    CTS(Point p1, Point p2, Circle c1, ld (*in_costf)(Point)){
        A = p1; B = p2; C = c1; costf = in_costf;
    }

    Point find_best(int mode){ // mode 0 -> /-\, mode 1 -> \_/
        Point lmid, rmid;
        while(calc.dist(A,B) > EPS){
            lmid = calc.arc_near_third(C,A,B);
            rmid = calc.arc_near_third(C,B,A);
            if((int)(costf(lmid) < costf(rmid)) ^ mode){
                A = lmid;
            } else {
                B = rmid;
            }
        }
        return calc.arc_mid(C,A,B);
    }

};

int main(){

}