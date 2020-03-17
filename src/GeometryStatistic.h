#pragma once
#include "stdafx.h"
#include "Point.h"
#include "GeometryShape.h"
#include "Exception.h"
#include "GeometryCalculator.h"
#include <vector>
#include <set>
#include <map>
#include <unordered_map>

class GeometryFactory{
private:
	unordered_map<RationalPoint*, int, rational_point_hash, rational_point_equal> *rational_points;
	unordered_map<UnRationalPoint*, int, unrational_point_hash, unrational_point_equal> *unrational_points;
	unordered_set<Line, line_hash, line_equal> lines;
	unordered_set<Circle, circle_hash, circle_equal> circles;
	void line_line_intersect(Line &l1, Line &l2);
	void line_circle_intersect(Line &l1, Circle &c1);
	void circle_circle_intersect(Circle &c1, Circle &c2);
public:
	GeometryFactory();
	Line addLine(int type, int x1, int x2, int y1, int y2); // exception handle
	Circle addCircle(int x, int y, int r); // exception handle
	int removeLine(Line &l);
	int removeCircle(Circle &c);
	vector<Point> solve();
	Line getLine(int id);
	Circle getCircle(int id);


	void feed(Line &l);
	void feed(Circle &c);
	
	int getPointCount();
	bool containsPoint(RationalPoint *a);
};
