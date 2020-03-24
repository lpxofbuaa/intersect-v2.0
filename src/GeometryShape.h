#pragma once
#include "Point.h"
#include <cmath>
#include "DoubleUtils.h"
#include "Constant.h"

class LineKey {
public:
	double k, b;
	LineKey();
	LineKey(double k, double b);
};

class Line {
private:
	void get_coincident_check_bounding();
public:
	long long x_min, x_max, y_min, y_max;
	long long x1, y1, x2, y2;
	long long a, b, c;
	int type;
	LineKey k;
	Line();
	Line(long long x1, long long y1, long long x2, long long y2, int type);
	friend bool line_coincident(Line &l1, Line &l2);
};

class Circle {
public:
	long long a, b, r;
	Circle();
	Circle(long long aa, long long bb, long long cc);
};

/* 对于有相同的line_key，hash值相同。*/
struct line_key_hash {
	size_t operator()(LineKey const& a) const;
};

/* 判断line_key是否真的相同 */
struct line_key_equal {
	bool operator()(LineKey const& a, LineKey const& b) const;
};


/* 对于相同参数的圆，hash值相同。 */
struct circle_hash {
	size_t operator()(Circle const& a) const;
};

/* 判断是否是真的一个圆 */
struct circle_equal {
	bool operator()(Circle const& a, Circle const& b) const;
};