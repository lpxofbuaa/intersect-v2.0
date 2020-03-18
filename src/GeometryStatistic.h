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
	RationalPointMap rational_points;							// 交点集合<有理数点，点存在于多少几何对象上> 
	UnRationalPointMap unrational_points;						// 交点集合<无理数点，点存在于多少几何对象上>
	LineMap lines;												// <k&b, <ID, Lines>>
	CircleSet circles;											// <Circles>
	LineIdMap line_ids;											// <ID, Line>
	CircleIdMap circle_ids;										// <ID, Circle>
	int line_counter = 1;										// Line ID 累加器
	int circle_counter = 0;										// Circle ID 累加器
	void line_line_intersect(Line &l1, Line &l2);				// 线线交点
	void line_circle_intersect(Line &l1, Circle &c1);			// 线圆交点
	void circle_circle_intersect(Circle &c1, Circle &c2);		// 圆圆交点
	inline void increase_rational_point(RationalPoint* p);		// 维护交点集合
	inline void increase_unrational_point(UnRationalPoint* p);	//  ..
	inline void decrease_rational_point(RationalPoint* p);		//  ..
	inline void decrease_unrational_point(UnRationalPoint* p);	//  ..
	void removeLine(Line &l);									// 移除Line对象
	void removeCircle(Circle &c);								// 移除Circle对象

	inline bool rational_point_in_line_range(RationalPoint* p, Line &l);
	inline bool unrational_point_in_line_range(UnRationalPoint* p, Line &l);
public:
	GeometryFactory();
	int addLine(int type, int x1, int x2, int y1, int y2);		// exception handle
	int addCircle(int x, int y, int r);							// exception handle
	Line getLine(int id);										// Update
	Circle getCircle(int id);									// For Update
	void remove(int id);										// For Remove Operation
	vector<Point> getPoints();									// 
	int getPointsCount();										// Update
};
