#include "intersectexample.h"

Line IntersectExample::getLine(int id){

    Line a(0.5, 0, 1, 0, 0, 5, 5);
    Line b(0, 0.5, 2, -1, 1, 0, 1);
    Line c(-1, 1, 3, 1, 0, 0, 1);

    switch (id) {
        case 1:
            return a;
            break;
        case 2:
            return b;
            break;
        case 3:
            return c;
            break;
        default:
        return a;
    }
}

Circle IntersectExample::getCircle(int id){
    return Circle(1, 1, 1);
}

vector<Point> IntersectExample::getPoints(){
    vector<Point> list;
    list.push_back(Point(0.5, 0.5));
    return list;
}
