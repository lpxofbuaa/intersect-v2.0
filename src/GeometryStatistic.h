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

typedef unordered_map<Point*, int, point_hash, point_equal> PointMap;
typedef unordered_map<int, Line> IdLineMap;
typedef unordered_map<LineKey, vector<Line>, line_key_hash, line_key_equal> LineMap;
typedef unordered_map<int, Circle> IdCircleMap;
typedef unordered_set<Circle, circle_hash, circle_equal> CircleSet;


class GeometryFactory{
private:
	PointMap intersects;										// 记录交点
	LineMap lines;												// 归类处在同条直线上的Line类
	CircleSet circles;											// 圆集合
	IdLineMap id_lines;											// <id, line> 映射
	IdCircleMap id_circle;										// <id, circle> 映射
	int line_counter = 1;
	int circle_counter = 0;
	void line_line_intersect(Line &l1, Line &l2);
	void line_circle_intersect(Line &l1, Circle &c1);
	void circle_circle_intersect(Circle &c1, Circle &c2);
	inline void increase_point(Point* p);
	inline void decrease_point(Point* p);
	void removeLine(Line &l);
	void removeCircle(Circle &c);

public:
	GeometryFactory();
	/* Modification */
	int addLine(int type, int x1, int x2, int y1, int y2); 		// exception handle
	int addCircle(int x, int y, int r); 						// exception handle
	void remove(int id);
	/* Query */
	Line getLine(int id);
	Circle getCircle(int id);
	vector<Point> getPoints();
	int getPointsCount();
};
