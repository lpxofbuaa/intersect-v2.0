#include "stdafx.h"
#include "GeometryShape.h"
#include "Constant.h"
#

Line::Line(long long x1, long long y1, long long x2, long long y2, int type) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->type = type;
	if (x1 == x2) {
		this->k = LineKey((double) K_INFINITE, (double) x1);
	}
	else {
		double k0 = double(y1 - y2) / double(x1 - x2);
		double b0 = double(x1 * y2 - x2 * y1) / double(x1 - x2);
		this->k = LineKey(k0, b0);
	}
	this->a = y2 - y1;
	this->b = x1 - x2;
	this->c = x2 * y1 - x1 * y2;
	get_coincident_check_bounding();
}

void Line::get_coincident_check_bounding()
{
	x_min = std::min(x1, x2);
	x_max = std::max(x1, x2);
	y_min = std::min(y1, y2);
	y_max = std::max(y1, y2);
	switch (type)
	{
	case DOUBLE_INFINITE_LINE:
		if (x_min != x_max) {
			x_min = MIN_RANGE;
			x_max = MAX_RANGE;
		}
		if (y_min != y_max) {
			y_min = MIN_RANGE;
			y_max = MAX_RANGE;
		}
		break;
	case SINGLE_INFINITE_LINE:
		if (x_min != x_max) {
			x_min = (x1 < x2) ? x_min : MIN_RANGE;
			x_max = (x1 > x2) ? x_max : MAX_RANGE;
		}
		if (y_min != y_max) {
			y_min = (y1 < y2) ? y_min : MIN_RANGE;
			y_max = (y1 > y2) ? y_max : MAX_RANGE;
		}
		break;
	case LIMITED_LINE:
		break;
	default:
		break;
	}
}

Line::Line() {}

Circle::Circle() {}

Circle::Circle(long long aa, long long bb, long long cc) {
	a = aa;
	b = bb;
	r = cc;
}

LineKey::LineKey() {}

LineKey::LineKey(double k, double b) {
	this->k = k;
	this->b = b;
}

size_t line_key_hash::operator()(LineKey const& a) const {
	size_t h1 = Double::hash(a.k);
	size_t h2 = Double::hash(a.b);
	return h1 ^ (h2 << 1u);
}

bool line_key_equal::operator()(LineKey const& a, LineKey const& b) const {
	return Double::equal(a.k, b.k) && Double::equal(a.b, b.b);
}

size_t circle_hash::operator()(Circle const & a) const
{
	size_t h1 = hash<long long>{}(a.a);
	size_t h2 = hash<long long>{}(a.b);
	size_t h3 = hash<long long>{}(a.r);
	return ((h1 ^ (h2 << 2u)) << 5u) ^ h3;
}

bool circle_equal::operator()(Circle const & a, Circle const & b) const
{
	return a.a == b.a && a.b == b.b && a.r == b.r;
}

/*
 * 判断两条Line对象是否出现了冲突（重合的线段部分）
 * Method: 将线段投影在坐标轴上（默认X轴），使用线段重合算法进行判断。
 */
bool line_coincident(Line & l1, Line & l2)
{
	line_key_equal key_equal;
	if (not key_equal.operator()(l1.k, l2.k)) {
		return false;
	}
	if (l1.x1 == l1.x2) {
		long long low_max = (l1.y_min > l2.y_min) ? l1.y_min : l2.y_min;
		long long high_min = (l1.y_max > l2.y_max) ? l2.y_max : l1.y_max;
		return low_max < high_min;
	}
	else {
		long long left_max = (l1.x_min > l2.x_min) ? l1.x_min : l2.x_min;
		long long right_min = (l1.x_max > l2.x_max) ? l2.x_max : l1.x_max;
		return left_max < right_min;
	}
}
