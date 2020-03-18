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
typedef unordered_map<int, Line> LineIdMap;
typedef unordered_map<LineKey, LineIdMap, line_key_hash, line_key_equal> LineMap;
typedef unordered_map<int, Circle> CircleIdMap;
typedef unordered_set<Circle, circle_hash, circle_equal> CircleSet;


class GeometryFactory{
private:
	RationalPointMap rational_points;
	UnRationalPointMap unrational_points;
	LineMap lines;
	CircleSet circles;
	LineIdMap line_ids;
	CircleIdMap circle_ids;
	int line_counter = 1;
	int circle_counter = 0;
	void line_line_intersect(Line &l1, Line &l2);
	void line_circle_intersect(Line &l1, Circle &c1);
	void circle_circle_intersect(Circle &c1, Circle &c2);
	inline void increase_rational_point(RationalPoint* p);
	inline void increase_unrational_point(UnRationalPoint* p);
	inline void decrease_rational_point(RationalPoint* p);
	inline void decrease_unrational_point(UnRationalPoint* p);
	inline bool rational_point_in_line_range(RationalPoint* p, Line &l);
	inline bool unrational_point_in_line_range(UnRationalPoint* p, Line &l);
	inline bool rational_point_on_circle(RationalPoint* p, Circle &c);
	inline bool unrational_point_on_circle(UnRationalPoint* p, Circle &c);
	void removeLine(Line &l);
	void removeCircle(Circle &c);
public:
	GeometryFactory();
	int addLine(int type, int x1, int x2, int y1, int y2); // exception handle
	int addCircle(int x, int y, int r); // exception handle
	Line getLine(int id);
	Circle getCircle(int id);
	void remove(int id);
	vector<Point> getPoints();
	int getPointsCount();
};
