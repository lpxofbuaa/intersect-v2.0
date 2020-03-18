#include "stdafx.h"
#include "Point.h"
#include <iostream>

using namespace std;


RationalPoint::RationalPoint(RationalNumber &x, RationalNumber &y) {
	this->x = x;
	this->y = y;
	this->hashcode = x.hashcode() ^ (y.hashcode() << 1);
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

bool UnRationalPoint::equals(const UnRationalPoint & b) const
{
	double_equal equals;
	return equals(x, b.x) && equals(y, b.y);
}

size_t unrational_point_hash::operator()(UnRationalPoint* const& a) const {
	long long x1 = (long long) floor(a->x * 1e10);
	long long y1 = (long long) floor(a->y * 1e10);
	size_t a_hash = hash<long long>{}(x1);
	size_t b_hash = hash<long long>{}(y1);
	return a_hash ^ (b_hash << 1u);
}

/*
 * 浮点数涉及精度问题，需要选择epsilon范围。
 * todo：epsilon大小的选取，若整数范围的数据很大，则小数点后的精度要求过高。（相同的大整数，但在1e-10层级的小数值可能不同)。
*/
bool unrational_point_equal::operator()(UnRationalPoint* const& a, UnRationalPoint* const& b) const {
	return fabs(a->x - b->x) < 1e-10 && fabs(a->y - b->y) < 1e-10;
}

size_t double_hash::operator()(double const& a) const {
	long long x = (long long)floor(a*1e10);
	return hash<long long>{}(x);
}

bool double_equal::operator()(double const& a, double const& b) const {
	return fabs(a - b) < 1e-10;
}

Point::Point(){}

Point::Point(double a, double b)
{
	x = a;
	y = b;
}