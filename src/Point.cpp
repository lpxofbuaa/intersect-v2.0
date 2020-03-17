#include "stdafx.h"
#include "Point.h"
#include <iostream>

using namespace std;


RationalPoint::RationalPoint(RationalNumber &x, RationalNumber &y) {
	this->x = x;
	this->y = y;
	this->hashcode = hash<string>{}(this->toString());
	//cout << toString() << endl;
}

RationalPoint::RationalPoint() {}

bool RationalPoint::equals(const RationalPoint &a) const {
	return x.equals(a.x) && y.equals(a.y);
}

string RationalPoint::toString() const {
	return x.toString() + "," + y.toString();
}

size_t rational_point_hash::operator()(RationalPoint* const& a) const {
	return a->hashcode;
}

bool rational_point_equal::operator()(RationalPoint* const& a, RationalPoint* const& b) const {
	return a->equals(*b);
}

UnRationalPoint::UnRationalPoint() {}

UnRationalPoint::UnRationalPoint(double a, double b) {
	x = a;
	y = b;
}

size_t unrational_point_hash::operator()(UnRationalPoint* const& a) const {
	long long x1 = (long long) floor(a->x * 1e10);
	long long y1 = (long long) floor(a->y * 1e10);
	size_t a_hash = hash<long long>{}(x1);
	size_t b_hash = hash<long long>{}(y1);
	return a_hash * b_hash;
}

bool unrational_point_equal::operator()(UnRationalPoint* const& a, UnRationalPoint* const& b) const {
	return fabs(a->x - b->x) < 1e-10 && fabs(a->y - b->y) < 1e-10;
}

size_t double_hash::operator()(double const& a) const {
	long long x = (long long)floor(a*1e8);
	return hash<double>{}(x);
}

bool double_equal::operator()(double const& a, double const& b) const {
	return fabs(a - b) < 1e-8;
}



