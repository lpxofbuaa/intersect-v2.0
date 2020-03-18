#pragma once
#include "Point.h"
#include "stdafx.h"

class LineKey {
public:
	double k, b;
	LineKey();
	LineKey(double k, double b);
};

class Line {
private:
	int x_min, x_max, y_min, y_max;
public:
	int x1, y1, x2, y2;
	int type;
	LineKey k;
	Line();
	Line(int x1, int y1, int x2, int y2, int type);
	friend bool line_coincident(Line &l1, Line &l2);
};

class Circle {
public:
	int a, b, r;
	Circle();
	Circle(int aa, int bb, int cc);
};

struct line_key_hash {
	size_t operator()(LineKey const& a) const;
};

/*判断k和b是否相等*/
struct line_key_equal {
	bool operator()(LineKey const& a, LineKey const& b) const;
};


struct line_hash {
	size_t operator()(Line const& a) const;
};

/*判断直线相等*/
struct line_equal {
	bool operator()(Line const& a, Line const& b) const;
};

struct circle_hash {
	size_t operator()(Circle const& a) const;
};

struct circle_equal {
	bool operator()(Circle const& a, Circle const& b) const;
};