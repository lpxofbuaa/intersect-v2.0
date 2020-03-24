#pragma once
#include "Point.h"
#include "GeometryShape.h"
#include "Exception.h"
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <regex>

typedef unordered_map<Point*, int, point_hash, point_equal> PointMap;
typedef unordered_map<int, Line> IdLineMap;
typedef unordered_map<LineKey, IdLineMap, line_key_hash, line_key_equal> LineMap;
typedef unordered_map<int, Circle> IdCircleMap;
typedef unordered_set<Circle, circle_hash, circle_equal> CircleSet;

class GeometryFactory{
public:
	PointMap points;						// ���㼯��<�������㣬������ڶ��ټ��ζ�����>
	LineMap lines;												// <k&b, <ID, Lines>>
	CircleSet circles;											// <Circles>
	IdLineMap line_ids;											// <ID, Line>
	IdCircleMap circle_ids;										// <ID, Circle>
	int line_counter = 1;										// Line ID �ۼ���
	int circle_counter = 0;										// Circle ID �ۼ���
	void line_line_intersect(Line &l1, Line &l2, bool increase=true);				// ���߽���
	void line_circle_intersect(Line &l1, Circle &c1, bool increase=true);			// ��Բ����
	void circle_circle_intersect(Circle &c1, Circle &c2, bool increase=true);		// ԲԲ����
	inline void increase_point(Point* p);	//  ..
	inline void decrease_point(Point* p);	//  ..
	void removeLine(Line &l);									// �Ƴ�Line����
	void removeCircle(Circle &c);								// �Ƴ�Circle����
	bool point_on_line(Point *p, Line &l);
	bool point_on_circle(Point *p, Circle &c);
	bool point_in_line_range(double x, double y, Line &l);
public:
	GeometryFactory();
	/* Modification */
	int addLine(int type, long long x1, long long x2, long long y1, long long y2);		// exception handle
	int addCircle(long long x, long long y, long long r);							// exception handle
	void remove(int id);										// For Remove Operation
	/* Query */
	Line getLine(int id);										// Update
	Circle getCircle(int id);									// For Update
	void getPoints(double *px, double *py, int count);									// 
	int getPointsCount();										// Update
	int addObjectFromFile(const char* message);							// Input File name point
};
