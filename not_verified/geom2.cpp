#include <bits/stdc++.h>

using namespace std;
const double eps = 1e-8;
const double pi = acos(-1.0);
const int inf = int(1e9);
typedef complex<double> point;
double cross(point a, point b) { return imag(conj(a)*b);}
double dot(point a, point b) { return real(conj(a)*b);}
int ccw(point a, point b, point c){
    b -= a; c -= a;
    if(cross(b,c) > eps) return 1;        // ccw
    if(cross(b,c) < -eps) return -1;      // cw
    if(dot(b,c) < -eps) return 2;         // line c--a--b
    if(norm(b) + eps < norm(c)) return -2;// line a--b--c
    return 0;
}

struct line{
    point a, b;
    line(){}
    line(point a, point b):a(a),b(b){}
    point projection(point p){ return a+dot(p-a, a-b)/norm(a-b)*(a-b);}
    point reflection(point p) { return p+2.0*(projection(p)-p);}
    bool intersect(point p){ return abs(cross(b-p, a-p)) < eps;}
    bool intersect(line l){ return abs(cross(b-a, l.b-l.a) < eps) or abs(cross(b-a,l.a-l.a) < eps);}
    double distance(point p){ return abs(p-projection(p));}
    double distance(line l){ return intersect(l)? 0: distance(l.a);}
    // crosspointはintersectをしてからやること
    point crosspoint(line l){
        double A = cross(b-a, l.b-l.a), B = cross(b-a, b-l.a);
        if(abs(A) < eps and abs(B) < eps) return l.a; // 重なってる
        if(abs(A) < eps) return point(inf,inf); // 並行
        return l.a+B/A*(l.b-l.a);
    }
};

struct segment{
    point a, b;
    segment(){}
    segment(point a, point b):a(a),b(b){}
    point projection(point p){ return a+dot(p-a, a-b)/norm(a-b)*(a-b);}
    point reflection(point p) { return p+2.0*(projection(p)-p);}
    bool intersect(point p){ return abs(a-p)+abs(b-p) < abs(b-a)+eps;}
    bool intersect(line l){ return cross(l.b-l.a,a-l.a) * cross(l.b-l.a, b-l.a) < eps;}
    bool intersect(segment s){ return ccw(a,b,s.a)*ccw(a,b,s.b) <= 0 and
                                      ccw(s.a,s.b,a)*ccw(s.a,s.b,b) <= 0;}
    double distance(point p){
        point r = projection(p);
        if(intersect(r)) return abs(r-p);
        return min(abs(a-p), abs(b-p));
    }
    double distance(line l){ return intersect(l)? 0: min(distance(a), distance(b));}
    double distance(segment s){
        if(intersect(s)) return 0;
        return min(min(distance(s.a), distance(s.b)),
                   min(s.distance(a), s.distance(b)));
    }
};

struct circle{
    point p; double r;
    circle(){}
    circle(point p, double r):p(p),r(r){}
    double area(){ return pi*r*r;}
    bool intersect(line l){ return norm(l.projection(p) - p) < r*r+eps;}
    int intersect(segment s){ // 交点数
        if(norm(s.projection(p)-p) > r*r+eps) return 0;
        double d1= abs(p-s.a), d2 = abs(p-s.b);
        if(d1 < r+eps and d2 < r+eps) return 0;
        if(d1+eps < r and d2 < r+eps or
           d1 < r+eps and d2+eps < r)  return 1;
        point h = s.projection(p);
        if(dot(s.a-h,s.b-h) < -eps) return 2;
        return 0;
    }
    bool intersect(circle c){ return norm(p-c.p) < (r+c.r)*(r+c.r)+eps and
                                      norm(p-c.p) > (r-c.r)*(r-c.r)-eps;}
    line crosspoint(line l){
        point hp = l.projection(p);
        point h = hp - p;
        point v = sqrt(r*r-norm(h))*(l.b-l.a)/abs(l.a-l.b);
        return line(hp-v, hp+v);
    }
    line crosspoint(segment s){
        line l(s.a,s.b);
        line ret = crosspoint(l);
        // 交点1つの場合は両方同じ点
        if(intersect(s) == 2) return ret;
        else if(dot(s.a-ret.a,s.b-ret.a) < -eps) ret.b = ret.a;
        else ret.a = ret.b;
        return ret;
    }
    line crosspoint(circle c){ // 重なっているとnan
        double d = abs(p-c.p);
        double x = (r*r-c.r*c.r+d*d)/(2.*d);
        point v = sqrt(r*r-x*x)*(p-c.p)/abs(p-c.p)*point(0,1);
        point h = p+x*(c.p-p)/abs(c.p-p);
        return line(h-v, h+v);
    }

};


int main(){
    
}
