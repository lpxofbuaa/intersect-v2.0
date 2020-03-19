#include "stdafx.h"
#include "DoubleUtils.h"

using namespace std;

size_t Double::hash(double const & value)
{
	double_hash a;
	return a(value);
}

bool Double::equal(double const & a, double const & b)
{
	double delta = fabs(a - b);
	//return delta < 1e-7;
	return delta < max(1.0, min(fabs(a) ,fabs(b))) * DOUBLE_EPSILON;
}

bool Double::greater(double const & a, double const & b)
{
	return a - b > max(1.0, min(fabs(a), fabs(b))) * DOUBLE_EPSILON;
}

bool Double::less(double const & a, double const & b)
{
	return b - a > max(1.0, min(fabs(a), fabs(b))) * DOUBLE_EPSILON;
}

size_t double_hash::operator()(double const& a) const {
	return hash<long long>{}((long long)round(a * DOUBLE_HASH_EPS));
}

bool double_equal::operator()(double const& a, double const& b) const {
	return Double::equal(a, b);
}


