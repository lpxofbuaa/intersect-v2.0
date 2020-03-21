#include "stdafx.h"
#include "Point.h"
#include "DoubleUtils.h"
#include <iostream>

using namespace std;



Point::Point() {}

Point::Point(double a, double b) {
	x = a;
	y = b;
}

bool Point::point_equals(const Point & b) const
{
	return equals(this->x, b.x) && equals(this->y, b.y);
}

string Point::toString()
{
	return string(to_string(this->x) + "," + to_string(this->y));
}

size_t point_hash::operator()(Point* const& a) const {
	size_t a_hash = hashcode(a->x);
	size_t b_hash = hashcode(a->y);
	return a_hash ^ (b_hash << 1u);
}

/*
 * 浮点数涉及精度问题，需要选择epsilon范围。
 * todo：epsilon大小的选取，若整数范围的数据很大，则小数点后的精度要求过高。（相同的大整数，但在1e-10层级的小数值可能不同)。
*/
bool point_equal::operator()(Point* const& a, Point* const& b) const {
	return a->point_equals(*b);
}

