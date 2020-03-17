#pragma once
#include "Point.h"
#include "stdafx.h"

class Line {
public:
	int x1, y1, x2, y2;
	int type;
	double k, b;
	Line();
	Line(int x1, int y1, int x2, int y2, int type);
};

class Circle {
public:
	int a, b, r;
	Circle();
	Circle(int aa, int bb, int cc);
};

struct line_hash {
	size_t operator()(Line const& a) const;
};

struct line_equal {
	bool operator()(Line const& a, Line const& b) const;
};

struct circle_hash {
	size_t operator()(Circle const& a) const;
};

struct circle_equal {
	bool operator()(Circle const& a, Circle const& b) const;
};