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
	size_t hashcode;

	Point();
	Point(double x, double y);
	bool equals(const Point &b) const;
	string toString() const;
};

/* ------------------------------  */
/* 判断两个点是否相同。 */
struct point_hash{
	size_t operator()(Point* const& a) const{
		return a->hashcode;
	}
};

struct point_equal{
	bool operator()(Point* const& a, Point* const& b) const{
		return a->equals(*b);
	}
};