#ifndef INTERSECTEXAMPLE_H
#define INTERSECTEXAMPLE_H

#include<iostream>
#include<vector>

using namespace std;

struct LineKey;
class Line;
class Circle;
class Point;

class IntersectExample{
public:
    Line getLine(int id);
    Circle getCircle(int id);
    vector<Point> getPoints();
    int getPointsCount();
};

struct LineKey{
    double k,b;
};

class Line{
public:
    LineKey key;
    int type;
    long long x1, x2, y1, y2;
    Line(double k, double b, int type, int64_t x1, int64_t y1, int64_t x2, int64_t y2):
        key(LineKey{k,b}), type(type), x1(x1), x2(x2), y1(y1), y2(y2){};
};

class Circle{
public:
    long long a, b, r;
    Circle(long long a, long long b, long long r): a(a), b(b), r(r){};
};

class Point{
public:
    double x, y;
    Point(double x, double y): x(x), y(y){};
};

#endif // INTERSECTEXAMPLE_H
