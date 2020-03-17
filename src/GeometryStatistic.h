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

typedef unordered_map<RationalPoint*, int, rational_point_hash, rational_point_equal> RationalPointMap;
typedef unordered_map<UnRationalPoint*, int, unrational_point_hash, unrational_point_equal> UnRationalPointMap;
typedef unordered_set<Line, line_hash, line_equal> LineSet;
typedef unordered_map<LineKey, LineSet, line_key_hash, line_key_equal> LineMap;
typedef unordered_set<Circle, circle_hash, circle_equal> CircleSet;


class GeometryFactory{
private:
	RationalPointMap rational_points;
	UnRationalPointMap unrational_points;
	LineMap lines;
	CircleSet circles;
	void line_line_intersect(Line &l1, Line &l2);
	void line_circle_intersect(Line &l1, Circle &c1);
	void circle_circle_intersect(Circle &c1, Circle &c2);
	inline void increase_rational_point(RationalPoint* p);
	inline void increase_unrational_point(UnRationalPoint* p);
	inline void decrease_rational_point(RationalPoint* p);
	inline void decrease_unrational_point(UnRationalPoint* p);
public:
	GeometryFactory();
	Line addLine(int type, int x1, int x2, int y1, int y2); // exception handle
	Circle addCircle(int x, int y, int r); // exception handle
	int removeLine(Line &l);
	int removeCircle(Circle &c);
	vector<Point> getPoints();
};
