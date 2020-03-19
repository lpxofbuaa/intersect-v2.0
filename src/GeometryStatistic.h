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
typedef unordered_map<LineKey, IdLineMap, line_key_hash, line_key_equal> LineMap;
typedef unordered_map<int, Circle> IdCircleMap;
typedef unordered_set<Circle, circle_hash, circle_equal> CircleSet;

class GeometryFactory{
public:
	PointMap points;						// 交点集合<无理数点，点存在于多少几何对象上>
	LineMap lines;												// <k&b, <ID, Lines>>
	CircleSet circles;											// <Circles>
	IdLineMap line_ids;											// <ID, Line>
	IdCircleMap circle_ids;										// <ID, Circle>
	int line_counter = 1;										// Line ID 累加器
	int circle_counter = 0;										// Circle ID 累加器
	void line_line_intersect(Line &l1, Line &l2);				// 线线交点
	void line_circle_intersect(Line &l1, Circle &c1);			// 线圆交点
	void circle_circle_intersect(Circle &c1, Circle &c2);		// 圆圆交点
	inline void increase_point(Point* p);	//  ..
	inline void decrease_point(Point* p);	//  ..
	void removeLine(Line &l);									// 移除Line对象
	void removeCircle(Circle &c);								// 移除Circle对象
	inline bool point_on_line(Point *p, Line &l);
	inline bool point_on_circle(Point *p, Circle &c);
	inline bool point_in_line_range(Point* p, Line &l);
public:
	GeometryFactory();
	/* Modification */
	int addLine(int type, long long x1, long long x2, long long y1, long long y2);		// exception handle
	int addCircle(long long x, long long y, long long r);							// exception handle
	void remove(int id);										// For Remove Operation
	/* Query */
	Line getLine(int id);										// Update
	Circle getCircle(int id);									// For Update
	vector<Point> getPoints();									// 
	int getPointsCount();										// Update
};
