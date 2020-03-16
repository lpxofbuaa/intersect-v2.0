#pragma once
#include "stdafx.h"
#include "Point.h"
#include "GeometryShape.h"

#include <vector>

class GeometryFactory{
private:
	unordered_set<RationalPoint*, my_hash, my_equal> *rational_points;
	unordered_set<UnRationalPoint*, double_hash, double_equal> *unrational_points;
	map<int, Line> lines;
	map<int, Circle> circles;
	void line_line_intersect(Line &l1, Line &l2);
	void line_circle_intersect(Line &l1, Circle &c1);
	void circle_circle_intersect(Circle &c1, Circle &c2);
	int counter();
public:
	GeometryFactory();
	int addLine(int type, int x1, int x2, int y1, int y2); // exception handle
	int addCircle(int x, int y, int r); // exception handle
	int remove(int id);
	vector<Point> solve();
	Line getLine(int id);
	Circle getCircle(int id);


	void feed(Line &l);
	void feed(Circle &c);
	
	int getPointCount();
	bool containsPoint(RationalPoint *a);
};
