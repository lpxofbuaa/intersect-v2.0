#pragma once
#include "RationalNumber.h"
#include "stdafx.h"
#include <unordered_set>
#include <string>
#include <map>

using namespace std;

class RationalPoint {
public:
	RationalNumber x;
	RationalNumber y;
	size_t hashcode;
	RationalPoint();
	RationalPoint(RationalNumber &x, RationalNumber &y);
	bool equals(const RationalPoint &b) const;
	string toString() const;
};

class UnRationalPoint {
public:
	double x;
	double y;
	UnRationalPoint();
	UnRationalPoint(double a, double b);
	bool equals(const UnRationalPoint &b) const;
};

// 核心模块交点的对外对象。
class Point {
public:
	double x, y;
	Point();
	Point(double a, double b);
};

struct rational_point_hash {
	size_t operator()(RationalPoint* const& a) const;
};

struct rational_point_equal {
	bool operator()(RationalPoint* const& a, RationalPoint* const& b) const;
};

struct unrational_point_hash {
	size_t operator()(UnRationalPoint* const& a) const;
};

struct unrational_point_equal {
	bool operator()(UnRationalPoint* const& a, UnRationalPoint* const& b) const;
};

struct double_hash {
	size_t operator()(double const& a) const;
};

struct double_equal {
	bool operator()(double const& a, double const& b) const;
};