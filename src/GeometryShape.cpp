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
		this->k = LineKey(INT32_MAX, x1);
	}
	else {
		this->k = LineKey((y1 - y2) / (x1 - x2), (x1*y2 - x2 * y1) / (x1 - x2));
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

size_t line_hash::operator()(Line const& a) const {
	line_key_hash hashcode;
	size_t h = hashcode.operator()(a.k);
	size_t h2 = hash<int>{}(a.type);
	return (h << 5u) ^ h2;
}

bool line_equal::operator()(Line const& a, Line const& b) const {
	line_key_equal key_equal;
	if (key_equal.operator()(a.k, b.k)) {
		// a and b are infinite line
		if (a.type == DOUBLE_INFINITE_LINE || b.type == DOUBLE_INFINITE_LINE) {
			return true;
		}

		switch (a.type)
		{
		case SINGLE_INFINITE_LINE:
			switch (b.type)
			{
			case SINGLE_INFINITE_LINE:

			case LIMITED_LINE:

			default:
				break;
			}
		case LIMITED_LINE:
			switch (b.type)
			{
			case SINGLE_INFINITE_LINE:

			case LIMITED_LINE:
				
			default:
				break;
			}
		default:
			break;
		}
	}
	return false;
}

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
