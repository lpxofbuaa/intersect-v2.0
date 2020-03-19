#pragma once
#include <cmath>
#include "Point.h"
#include "DoubleUtils.h"
#include "Constant.h"
#include "stdafx.h"

class LineKey {
public:
	double k, b;
	LineKey();
	LineKey(double k, double b);
};

class Line {
public:
	long long x1, x2, y1, y2;
	long long a, b, c;			// Ax + By + C = 0 ：求解交点、判断是否不存在斜率（b=0）
	long long x_min, x_max, y_min, y_max;
	LineKey k;					// y = kx + b (if k not exist, choose inf) 仅用于STL容器的组织索引，不参与任何交点性的运算（包括不参与判断线的垂直）
	int type;
	Line();
	Line(int x1, int y1, int x2, int y2, int type);
	friend bool line_coincident(Line &l1, Line &l2);
private:
	void get_coincident_check_bounding()		// 被构造函数调用，将各类的Line对象都放缩到线段级别，构造冲突检查用的框区域（精准）。
	// 函数经过检查后粘贴到cpp文件中。
	{	
		x_min = std::min(x1, x2);
		x_max = std::max(x1, x2);
		y_min = std::min(y1, y2);
		y_max = std::max(y1, y2);
		if(type == DOUBLE_INFINITE_LINE){
			if(x_min != x_max){
				x_min = MIN_RANGE;
				x_max = MAX_RANGE;
			}
			if(y_min != y_max){
				y_min = MIN_RANGE;
				y_max = MAX_RANGE;
			}
		}
		else if(type == SINGLE_INFINITE_LINE){
			if(x_min != x_max){
				x_min = (x1 < x2) ? x_min : MIN_RANGE;
				x_max = (x1 > x2) ? x_max : MAX_RANGE;
			}
			if(y_min != y_max){
				y_min = (y1 < y2) ? y_min : MIN_RANGE;
				y_max = (y1 > y2) ? y_max : MAX_RANGE;
			}
		}
	}
};

class Circle {
public:
	long long a, b, r;
	Circle();
	Circle(int aa, int bb, int cc);
};

/* ------------------------------  */
/* 用于判断Line类型是否处在同一个直线上 */
struct line_key_hash {
	size_t operator()(LineKey const& a) const{
		size_t h1 = Double::hash(a.k);
		size_t h2 = Double::hash(a.b);
		return h1 ^ (h2 << 1u);
	}
};

struct line_key_equal {
	bool operator()(LineKey const& a, LineKey const& b) const{
		return Double::equal(a.k, b.k) && Double::equal(a.b, b.b);
	}
};

struct circle_hash {
	size_t operator()(Circle const& a) const{
		size_t h1 = hash<long long>{}(a.a);
		size_t h2 = hash<long long>{}(a.b);
		size_t h3 = hash<long long>{}(a.r);
		return ((h1 ^ (h2 << 2u)) << 5u) ^ h3;
	}
};

struct circle_equal {
	bool operator()(Circle const& a, Circle const& b) const{
		return a.a == b.a && a.b == b.b && a.r == b.r;
	}
};