#include "stdafx.h"
#include "GeometryShape.h"
#include "Constant.h"

Line::Line(int x1, int y1, int x2, int y2, int type) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->type = type;
	if (x1 == x2) {
		this->k = LineKey((double) INT32_MAX, (double) x1);
	}
	else {
		double k0 = double(y1 - y2) / double(x1 - x2);
		double b = double(x1 * y2 - x2 * y1) / double(x1 - x2);
		this->k = LineKey(k0, b);
	}
	switch (type)
	{
	case DOUBLE_INFINITE_LINE:
		x_min = MIN_RANGE;
		x_max = MAX_RANGE;
		y_min = MIN_RANGE;
		y_max = MAX_RANGE;
		break;
	case SINGLE_INFINITE_LINE:
		if (x1 != x2) {
			if (x2 > x1) {
				x_max = MAX_RANGE;
				x_min = x1;
			}
			else {
				x_max = x1;
				x_min = MIN_RANGE;
			}
		}
		else {
			if (y2 > y1) {
				y_max = MAX_RANGE;
				y_min = y1;
			}
			else {
				y_max = y1;
				y_min = MIN_RANGE;
			}
		}
		break;
	case LIMITED_LINE:
		if (x1 != x2) {
			if (x1 > x2) {
				x_max = x1;
				x_min = x2;
			}
			else {
				x_max = x2;
				x_min = x1;
			}
		}
		else {
			if (y1 > y2) {
				y_max = y1;
				y_min = y2;
			}
			else {
				y_max = y2;
				y_min = y1;
			}
		}
		break;
	default:
		break;
	}
}

Line::Line() {}

Circle::Circle() {}

Circle::Circle(int aa, int bb, int cc) {
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
	long long k1 = (long long)floor(a.k*1e10);
	long long b1 = (long long)floor(a.b*1e10);
	size_t h1 = hash<long long>{}(k1);
	size_t h2 = hash<long long>{}(b1);
	return h1 ^ (h2 << 1u);
}

bool line_key_equal::operator()(LineKey const& a, LineKey const& b) const {
	return fabs(a.k - b.k) < 1e-10 && fabs(a.b - b.b) < 1e-10;
}

/*
size_t line_hash::operator()(Line const& a) const {
	line_key_hash hashcode;
	size_t h = hashcode.operator()(a.k);
	size_t h2 = hash<int>{}(a.type);
	return (h << 5u) ^ h2;
}
*/

/*
bool line_equal::operator()(Line const& a, Line const& b) const {
	line_key_equal key_equal;
	return key_equal.operator()(a.k, b.k) && a.type == b.type;
}
*/

size_t circle_hash::operator()(Circle const & a) const
{
	size_t h1 = hash<int>{}(a.a);
	size_t h2 = hash<int>{}(a.b);
	size_t h3 = hash<int>{}(a.r);
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
		int low_max = (l1.y_min > l2.y_min) ? l1.y_min : l2.y_min;
		int high_min = (l1.y_max > l2.y_max) ? l2.y_max : l1.y_max;
		return low_max < high_min;
	}
	else {
		int left_max = (l1.x_min > l2.x_min) ? l1.x_min : l2.x_min;
		int right_min = (l1.x_max > l2.x_max) ? l2.x_max : l1.x_max;
		return left_max < right_min;
	}
}
