#pragma once
#include "stdafx.h"
#include <unordered_set>
#include <string>
#include <map>

using namespace std;


class Point {
public:
	double x;
	double y;
	Point();
	Point(double a, double b);
	bool equals(const Point &b) const;
	string toString();
};


struct point_hash {
	size_t operator()(Point* const& a) const;
};

struct point_equal {
	bool operator()(Point* const& a, Point* const& b) const;
};

